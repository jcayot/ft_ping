//
// Created by jules on 25/11/2024.
//

#include <ft_ping.h>

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

void	update_stats(const t_ping_result *result, t_ping_stats *stats)
{
	switch (result->status) {
		case STATUS_OK:
			stats->avg = ((stats->avg * stats->received) + result->time) / (stats->received + 1);
			stats->min = ((stats->min > result->time || stats->received == 0) ? result->time : stats->min);
			stats->max = ((stats->max < result->time || stats->received == 0) ? result->time : stats->max);
			stats->sent++;
			stats->received++;
			break;
		case STATUS_TIMEOUT:
			stats->sent++;
			stats->result = 1;
			break;
		case STATUS_INVALID_ANSWER:
			stats->sent++;
			stats->result = 1;
			break;
		case STATUS_NO_ANSWER:
			stats->sent++;
			stats->result = 1;
			break;
		default:
			stats->result = 1;
	}
}

void	print_start(const char* dest, const char* ip, int size)
{
	printf("PING %s (%s) %d data bytes\n", dest, ip, size);
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
