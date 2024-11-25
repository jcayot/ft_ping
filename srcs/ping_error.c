//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

void ping_error(const char *msg)
{
	write(STDERR_FILENO, "ping: ", 6);
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO,"\n", 1);
}
