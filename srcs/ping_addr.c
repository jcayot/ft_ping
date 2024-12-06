//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int		get_socket_fd(const struct addrinfo *addrinfo)
{
	const struct addrinfo	*addrinfo_i;
	int						sfd;

	sfd = -1;
	addrinfo_i = addrinfo;
	while (addrinfo_i)
	{
		sfd = socket(addrinfo_i->ai_family, addrinfo_i->ai_socktype, addrinfo_i->ai_protocol);
		if (sfd != -1)
			break ;
		addrinfo_i = addrinfo_i->ai_next;
	}
	return (sfd);
}

int	handle_response(ssize_t received_len, void* response, t_ping_result *ping_result)
{
	if (received_len != -1)
	{
		if (check_icmp_packet_checksum(received_len, response))
		{
			ping_result->status = STATUS_OK;
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

t_ping_result	do_ping(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, uint16_t sequence)
{
	t_ping_result	ping_result = (t_ping_result) {STATUS_PROGRAM_ERROR, 0, sequence, 0, 0};
	u_long_long		start_time;
	void			*icmp_request;
	void			*response_buf;

	icmp_request = make_icmp_packet(cmd->size, sequence);
	if (!icmp_request)
		return (ping_result);
	response_buf = malloc(cmd->size + 8);
	if (response_buf)
	{
		start_time = get_ust();
		if (sendto(sfd, icmp_request, cmd->size + 8, 0, addrinfo->ai_addr, addrinfo->ai_addrlen) != -1)
		{
			ssize_t received_len = recvfrom(sfd, response_buf, cmd->size + 8, 0, NULL, NULL);
			ping_result.time = get_ust() - start_time;
			handle_response(received_len, response_buf, &ping_result);
		}
		free(response_buf);
	}
	free(icmp_request);
	return (ping_result);
}

int		ping_addr(const struct addrinfo *addrinfo, const t_parsed_cmd *cmd)
{
	t_ping_stats	ping_stats = (t_ping_stats) {get_ust(), 0, 0, 0, 0, 0, 0, 0, 0};
	int				sfd;
	uint16_t		sequence = 0;

	sfd = get_socket_fd(addrinfo);
	if (sfd == -1)
		return (ping_error("Error creating socket filedescriptor"));
	print_start(cmd->destination, "ip", cmd->size);
	while (cmd->count == 0 || sequence < cmd->count)
	{
		t_ping_result ping_result = do_ping(sfd, addrinfo, cmd, sequence);
		update_stats(&ping_result, &ping_stats);
		if (ping_result.status == STATUS_PROGRAM_ERROR)
			break ;
		print_result(&ping_result);
		if (sequence == UINT16_MAX)
			break ;
		sequence++;
		usleep(1000000);
	}
	ping_stats.end_time = get_ust();
	print_stats(cmd->destination, &ping_stats);
	close(sfd);
	return (ping_stats.result);
}
