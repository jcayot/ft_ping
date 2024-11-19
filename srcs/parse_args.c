//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int	parse_args(int argc, char* argv[], t_parsed_command* dest)
{
	if (argc < 2)
		return (1);
	dest->destination = argv[1];
	dest->help = false;
	dest->verbose = false;
	return (0);
}
