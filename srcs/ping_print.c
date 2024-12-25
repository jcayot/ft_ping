//
// Created by jules on 25/12/2024.
//

#include <ft_ping.h>

void	print_socket_verbose(int sfd, int ai_socktype, int hints_ai_family)
{
	printf("ping: sock4.fd: %d (socktype: %s), hints.ai_family: %s\n\n", sfd, ai_socktype_to_string(ai_socktype),
		family_to_string(hints_ai_family));
}

void	print_start(const t_parsed_cmd* cmd, const struct addrinfo* dest_addr)
{
	char	ip[INET6_ADDRSTRLEN];

	ip_from_addrinfo(dest_addr->ai_addr, dest_addr->ai_family, ip, INET6_ADDRSTRLEN);
	if (cmd->verbose)
		printf("ai->ai_family: %s, ai->ai_canonname: '%s'\n", family_to_string(dest_addr->ai_family),
			cmd->destination);
	printf("PING %s (%s) %d data bytes\n", cmd->destination, ip, cmd->size);
}

void	print_result(const t_ping_result *result, bool quiet, bool verbose)
{
	if (!quiet) {
		if (result->status == STATUS_OK)
		{
			char	sender_ip[INET6_ADDRSTRLEN];
			char	sender_hostname[MAX_SENDER_ADDR_LEN];

			ip_from_addrinfo(&result->sender_addr, result->sender_addr.sa_family, sender_ip, INET6_ADDRSTRLEN);
			hostname_from_addrinfo(&result->sender_addr, result->sender_addr_len, sender_hostname, MAX_SENDER_ADDR_LEN);

			printf("%d bytes from %s (%s): icmp_seq=%d ", result->size, sender_hostname, sender_ip, result->seq);
			if (verbose)
				printf("ident=%d ", result->id);
			printf("ttl=%d time=%1.1f ms\n", result->ttl, ((double)result->time / 1000.0));
		}
	}
}

void	print_stats(const char* dest, const t_ping_stats* stats)
{
	printf("--- %s ping statistics ---\n", dest);
	printf("%d packets transmitted, %d received, %d%% packet loss, time %lums\n", stats->sent, stats->received,
		(1 - (stats->received / stats->sent)) * 100, (u_long) (((stats->end_time.tv_sec - stats->start_time.tv_sec)
			* 1e6 + (stats->end_time.tv_nsec - stats->start_time.tv_nsec) / 1e3) / 1000));
	printf("rtt min/avg/max/mdev = %1.3f/%1.3f/%1.3f/%1.3f ms\n", ((double) stats->min / 1000.0),
		((double) stats->avg / 1000.0), ((double) stats->max / 1000.0), 0.0);
}
