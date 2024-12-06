//
// Created by jules on 06/12/2024.
//

#include <ft_ping.h>

void	ip_from_addrinfo(const struct sockaddr *sa, int family, char *dest, int dest_size)
{
	if (family == AF_INET)
	{
		struct sockaddr_in *sin = (struct sockaddr_in *) sa;
		inet_ntop(AF_INET, &sin->sin_addr, dest, dest_size);
	}
	else if (family == AF_INET6)
	{
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;
		inet_ntop(AF_INET6, &sin6->sin6_addr, dest, dest_size);
	}
	else
	{
		printf("Unknown address family %d\n", family);
		dest[0] = '\0';
	}
}
