//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>
#include <string.h>

int		ping_addr(struct addrinfo* addrinfo, bool verbose)
{
	(void) verbose;
	for (; addrinfo; addrinfo = addrinfo->ai_next) {
		write(1, addrinfo->ai_addr->sa_data, 14);
		write(1, "\n", 1);
		if (addrinfo->ai_canonname)
			write(1, addrinfo->ai_canonname, strlen(addrinfo->ai_canonname));
		write(1, "\n", 1);
	}
	return (0);
}
