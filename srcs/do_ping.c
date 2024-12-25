//
// Created by jules on 06/12/2024.
//

#include <ft_ping.h>

bool running = true;

int	handle_response(ssize_t received_len, void* response, t_ping_result *ping_result)
{
	if (received_len != -1)
	{
		if (check_received_icmp_packet(received_len, response))
		{
			struct iphdr *ip_header = response;
			struct icmphdr *icmp_header = response + sizeof(struct iphdr);

			ping_result->status = STATUS_OK;
			ping_result->seq = icmp_header->un.echo.sequence;
			ping_result->id = icmp_header->un.echo.id;
			ping_result->size = received_len;
			ping_result->ttl = ip_header->ttl;
		}
		else
			ping_result->status = STATUS_INVALID_ANSWER;
	}
	else
		ping_result->status = STATUS_NO_ANSWER;
	return (ping_result->status);
}

int	send_ping_request(int sfd, const struct addrinfo *addrinfo, int size, int sequence)
{
	void	*icmp_request = make_icmp_packet(size, sequence);
	int		result = STATUS_OK;

	if (!icmp_request)
		return (STATUS_PROGRAM_ERROR);
	if (sendto(sfd, icmp_request, size + 8, 0, addrinfo->ai_addr, addrinfo->ai_addrlen) == -1)
		result = STATUS_NETWORK_ERROR;
	free(icmp_request);
	return (result);
}

t_ping_result	receive_ping_response(int sfd, int size)
{
	t_ping_result	ping_result;
	void			*response_buf = calloc(1, size + 8);

	memset(&ping_result, 0, sizeof(ping_result));
	ping_result.status = STATUS_PROGRAM_ERROR;
	ping_result.sender_addr_len = sizeof(struct sockaddr);
	if (!response_buf)
		return (ping_result);

	ssize_t received_len = -1;
	while (running && received_len == -1)
	{
		received_len = recvfrom(sfd, response_buf, size + 8, MSG_DONTWAIT, &ping_result.sender_addr,
										&ping_result.sender_addr_len);
		int	error = errno;
		if (error != EAGAIN && error != EWOULDBLOCK)
			break ;
	}
	handle_response(received_len, response_buf, &ping_result);
	free(response_buf);
	return (ping_result);
}

int	do_ping(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats)
{
	signal(SIGINT, handle_sigint);
	uint16_t		sequence = 0;

	while (running && (cmd->count == 0 || sequence < cmd->count))
	{
		t_ping_result	result;
		struct timespec	start_time, end_time;
		if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1)
			return (STATUS_PROGRAM_ERROR);

		result.status = send_ping_request(sfd, addrinfo, cmd->size, sequence);
		if (result.status != STATUS_OK)
			return (result.status);
		result = receive_ping_response(sfd, cmd->size);

		if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1)
			return (STATUS_PROGRAM_ERROR);
		result.time = (end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_nsec - start_time.tv_nsec) / 1e3;
		update_stats(&result, stats);

		if (cmd->audible && result.status == STATUS_OK)
			play_alert_sound();
		print_result(&result, cmd->quiet, cmd->verbose);

		if (sequence == UINT16_MAX || result.status == STATUS_PROGRAM_ERROR)
			return (result.status);

		sequence++;
		usleep(1000000);
	}
	return (STATUS_OK);
}
