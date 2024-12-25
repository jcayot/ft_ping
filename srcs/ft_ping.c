//
// Created by jules on 19/11/2024.
// Made by Saku on today
//

#include <ft_ping.h>

int		open_socket_fd(const struct addrinfo *addrinfo, bool verbose)
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
	if (sfd != -1 && verbose)
		print_socket_verbose(sfd, addrinfo_i->ai_socktype, hints.ai_family);
	return (sfd);
}

int		ping_addr(const struct addrinfo *addrinfo, const t_parsed_cmd *cmd)
{
	t_ping_stats	ping_stats = (t_ping_stats) {{0, 0}, {0, 0}, 0, 0, 0, 0, 0, 0, 0};
	int				sfd;
	int				result;

	sfd = open_socket_fd(addrinfo, cmd->verbose);
	if (sfd == -1)
		return (ping_error("Error creating socket filedescriptor"));
	print_start(cmd, addrinfo);
	if (clock_gettime(CLOCK_MONOTONIC, &ping_stats.start_time) == -1)
	{
		close(sfd);
		return (ping_error("Error getting time"));
	}
	if (cmd->preload == 0)
		result = do_ping(sfd, addrinfo, cmd, &ping_stats);
	else
		result = do_ping_preload(sfd, addrinfo, cmd, &ping_stats);
	if (result != STATUS_PROGRAM_ERROR)
	{
		if (clock_gettime(CLOCK_MONOTONIC, &ping_stats.end_time) == -1)
		{
			close(sfd);
			return (ping_error("Error getting time"));
		}
		print_stats(cmd->destination, &ping_stats);
	}
	else
		ping_error("Internal error");
	close(sfd);
	return (result);
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
