//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int		get_socket_fd(const struct addrinfo *addrinfo)
{
	struct addrinfo	*addrinfo_i;
	int				sfd;

	sfd = -1;
	addrinfo_i = addrinfo;
	while (addrinfo_i)
	{
		sfd = socket(addrinfo_i->ai_family, addrinfo_i->ai_socktype, addrinfo_i->ai_protocol);
		if (sfd == -1)
			continue ;
		if (bind(sfd, addrinfo_i->ai_addr, addrinfo_i->ai_addrlen) == 0)
			break ;
		close(sfd);
		addrinfo_i = addrinfo_i->ai_next;
	}
	return (sfd);
}

int		ping_addr(const struct addrinfo *addrinfo, const t_parsed_cmd *cmd)
{
	u_long	start_time;
	u_long	end_time;
	int		sfd;
	int		i;

	sfd = get_socket_fd(addrinfo);
	if (sfd == -1)
		return (1);
	i = 0;
	while (cmd->count == 0 || i < cmd->count)
	{
		start_time = get_mst();
		end_time = get_mst();
		i++;
	}
	return (0);
}
