//
// Created by jules on 19/11/2024.
// Made by Saku on today
//

#include <ft_ping.h>

int ft_ping(int argc, const char *argv[])
{
	t_parsed_cmd	cmd;
	struct addrinfo	*dest_addr_infos;
	int				result;

	result = parse_args(argc, argv, &cmd);
	if (result != 0)
		return (p_parsing_error(result));
	if (cmd.help)
		return (help_ft_ping());
	result = getaddrinfo(cmd.destination, NULL, &hints, &dest_addr_infos);
	if (result == 0)
	{
		result = ping_addr(dest_addr_infos, &cmd);
		freeaddrinfo(dest_addr_infos);
	}
	else
		ping_error(gai_strerror(result));
	return (result);
}

int main(int argc, const char *argv[])
{
	return (ft_ping(argc, argv));
}
