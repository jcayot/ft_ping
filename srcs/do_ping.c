//
// Created by jules on 06/12/2024.
//

#include <ft_ping.h>

int	handle_response(ssize_t received_len, void* response, t_ping_result *ping_result)
{
	if (received_len != -1)
	{
		if (check_icmp_packet_checksum(received_len, response))
		{
			ping_result->status = STATUS_OK;
			ping_result->seq = ((struct icmphdr*) response)->un.echo.sequence;
			ping_result->size = received_len;
			ping_result->ttl = ((struct iphdr*) response)->ttl;
		}
		else
			ping_result->status = STATUS_INVALID_ANSWER;
	}
	else
		ping_result->status = STATUS_NETWORK_ERROR;
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
	if (!response_buf)
		return (ping_result);
	ping_result.sender_addr_len = sizeof(struct sockaddr);
	ssize_t received_len = recvfrom(sfd, response_buf, size + 8, 0, &ping_result.sender_addr,
		&ping_result.sender_addr_len);
	handle_response(received_len, response_buf, &ping_result);
	free(response_buf);
	return (ping_result);
}

int	do_ping(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats)
{
	uint16_t		sequence = 0;

	while (cmd->count == 0 || sequence < cmd->count)
	{
		t_ping_result	result;
		u_long_long		start_time = get_ust();

		result.status = send_ping_request(sfd, addrinfo, cmd->size, sequence);
		if (result.status != STATUS_OK)
			return (result.status);
		result = receive_ping_response(sfd, cmd->size);
		result.time = get_ust() - start_time;
		update_stats(&result, stats);
		if (result.status == STATUS_PROGRAM_ERROR)
			return (result.status);
		if (cmd->audible)
			play_alert_sound();
		if (!cmd->quiet)
			print_result(&result);
		if (sequence == UINT16_MAX)
			return (result.status);
		sequence++;
		usleep(1000000);
	}
	return (STATUS_OK);
}

int	do_ping_proload(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats)
{
	(void) sfd;
	(void) addrinfo;
	(void) cmd;
	(void) stats;
	return (STATUS_OK);
}