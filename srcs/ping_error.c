//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int	ping_error(const char* msg)
{
	write(STDERR_FILENO, "ft_ping: ", 9);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO,"\n", 1);
	return (1);
}
