//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>
#include <string.h>

int		ping_addr(struct addrinfo* addrinfo, bool verbose)
{
	(void) verbose;
	for (; addrinfo; addrinfo = addrinfo->ai_next) {
		printf("%d\n", addrinfo->ai_protocol);
	}
	return (0);
}
