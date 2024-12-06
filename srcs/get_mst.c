//
// Created by jules on 25/11/2024.
//

#include <ft_ping.h>

u_long_long	get_ust(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
