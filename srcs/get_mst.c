//
// Created by jules on 25/11/2024.
//

#include <get_mst.h>


unsigned long long	get_ust(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
