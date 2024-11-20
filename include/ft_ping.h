//
// Created by jules on 19/11/2024.
//

#ifndef FT_PING_H
# define FT_PING_H

# include <ctype.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_parsed_command {
	char	*destination;
	bool	audible;
	bool	verbose;
	bool	help;
	bool	quiet;
	int		count;
	int		size;
	int		preload;
}	t_parsed_command;

typedef enum parsing_result {
	OK = 0,
	UNKNOWN_PARAMETER = 1,
	NO_ARGUMENT = 2,
	INVALID_ARGUMENT = 3,
}	t_parsing_result;

static const struct addrinfo hints = {0, 0, 0, IPPROTO_ICMP, 0, NULL, NULL, NULL};

void	ping_error(const char* msg);

int		help_ft_ping(void);

int		parse_args(int argc, char* argv[], t_parsed_command* dest);
int		p_parsing_error(int err);

int		ping_addr(struct addrinfo* addrinfo, bool verbose);

int		strict_atoi(const char *str);

#endif
