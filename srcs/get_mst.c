//
// Created by jules on 25/11/2024.
//

#include <ft_ping.h>

u_long	get_mst(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
