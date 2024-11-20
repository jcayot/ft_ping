//
// Created by jules on 20/11/2024.
//

#include <ft_ping.h>

int	strict_atoi(const char *str)
{
	long	result;
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (!isdigit(str[i]))
			return (-1);
		i++;
	}
	result = strtol(str, NULL, 10);
	if (result > INT_MAX || result < INT_MIN)
		return (-1);
	return ((int) result);
}
