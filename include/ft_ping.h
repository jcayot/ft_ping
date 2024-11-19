//
// Created by jules on 19/11/2024.
//

#ifndef FT_PING_H
# define FT_PING_H

# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_parsed_command {
	char	*destination;
	bool	verbose;
	bool	help;
}	t_parsed_command;

typedef enum parsing_result {
	OK = 0,
	UNKNOWN_PARAMETER = 1,
	NO_ARGUMENT = 2,
}	t_parsing_result;

int		help_ft_ping(void);

int		parse_args(int argc, char* argv[], t_parsed_command* dest);

int		ping_addr(struct addrinfo* addrinfo, bool verbose);

#endif
