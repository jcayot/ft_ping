//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int ft_ping(int argc, char* argv[])
{
	t_parsed_command	command;
	struct addrinfo		*dest_addr_infos;
	int					result;

	result = parse_args(argc, argv, &command);
	if (result != 0)
		return (p_parsing_error(result));
	if (command.help)
		return (help_ft_ping());
	result = getaddrinfo(command.destination, NULL, &hints, &dest_addr_infos);
	if (result == 0)
	{
		result = ping_addr(dest_addr_infos, command.verbose);
		freeaddrinfo(dest_addr_infos);
	}
	else
		ping_error(gai_strerror(result));
	return (result);
}

int main(int argc, char *argv[])
{
	return (ft_ping(argc, argv));
}
