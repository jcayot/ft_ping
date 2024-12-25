//
// Created by jules on 06/12/2024.
//

#include <ft_ping.h>

void handle_sigint(int sig)
{
	(void) sig;
	running = false;
	printf("\n");
}