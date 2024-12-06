//
// Created by jules on 19/11/2024.
// Made by Saku on today
//

#include <ft_ping.h>

int		open_socket_fd(const struct addrinfo *addrinfo)
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

int		ping_addr(const struct addrinfo *addrinfo, const t_parsed_cmd *cmd)
{
	t_ping_stats	ping_stats = (t_ping_stats) {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int				sfd;

	sfd = open_socket_fd(addrinfo);
	if (sfd == -1)
		return (ping_error("Error creating socket filedescriptor"));
	ping_stats.start_time = get_ust();
	if (cmd->preload == 0)
		do_ping(sfd, addrinfo, cmd, &ping_stats);
	else
		do_ping_proload(sfd, addrinfo, cmd, &ping_stats);
	ping_stats.end_time = get_ust();
	print_stats(cmd->destination, &ping_stats);
	close(sfd);
	return (ping_stats.result);
}

int ft_ping(int argc, const char *argv[])
{
	t_parsed_cmd	cmd;
	struct addrinfo	*dest_addr;
	int				result;

	result = parse_args(argc, argv, &cmd);
	if (result != 0)
		return (p_parsing_error(result));
	if (cmd.help)
		return (help_ft_ping());
	result = getaddrinfo(cmd.destination, NULL, &hints, &dest_addr);
	if (result == 0)
	{
		char	dest_ip[INET6_ADDRSTRLEN];
		ip_from_addrinfo(dest_addr->ai_addr, dest_addr->ai_family, dest_ip, INET6_ADDRSTRLEN);
		print_start(cmd.destination, dest_ip, cmd.size);
		result = ping_addr(dest_addr, &cmd);
		freeaddrinfo(dest_addr);
	}
	else
		ping_error(gai_strerror(result));
	return (result);
}

int main(int argc, const char *argv[])
{
	return (ft_ping(argc, argv));
}
