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

void	hostname_from_addrinfo(const struct sockaddr *sa, socklen_t sa_len, char *dest, int dest_size)
{
	getnameinfo(sa, sa_len, dest, dest_size, NULL, 0, NI_NAMEREQD);
}

const char* family_to_string(const int ai_family)
{
	switch (ai_family) {
		case AF_INET:
			return ("AF_INET");
		case AF_INET6:
			return ("AF_INET6");
		case AF_UNIX:
			return ("AF_UNIX");
		case AF_UNSPEC:
			return ("AF_UNSPEC");
		default:
			return ("Unknown");
	}
}

const char* ai_socktype_to_string(const int ai_socktype)
{
	switch (ai_socktype) {
		case SOCK_STREAM:
			return "SOCK_STREAM";
		case SOCK_DGRAM:
			return "SOCK_DGRAM";
		case SOCK_RAW:
			return "SOCK_RAW";
		case SOCK_SEQPACKET:
			return "SOCK_SEQPACKET";
		case SOCK_RDM:
			return "SOCK_RDM";
		default:
			return "Unknown";
	}
}