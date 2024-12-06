//
// Created by jules on 19/11/2024.
//

#ifndef FT_PING_H
# define FT_PING_H

# include <ctype.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>

typedef unsigned long long	u_long_long;

typedef struct s_parsed_command
{
	char	*destination;
	bool	audible;
	bool	verbose;
	bool	help;
	bool	quiet;
	int		count;
	int		size;
	int		preload;
}	t_parsed_cmd;

typedef struct s_ping_result
{
	int			status;
	u_int		size;
	u_int		seq;
	u_int		ttl;
	u_long_long	time;
}	t_ping_result;

typedef struct s_ping_stats
{
	u_long_long	start_time;
	u_long_long	end_time;
	u_int		sent;
	u_int		received;
	u_long_long	min;
	u_long_long	avg;
	u_long_long	max;
	u_long_long	mdev;
	int			result;
}	t_ping_stats;

typedef enum parsing_result
{
	PARSING_OK = 0,
	UNKNOWN_PARAMETER = 1,
	NO_ARGUMENT = 2,
	INVALID_ARGUMENT = 3,
}	t_parsing_result;

typedef enum ping_status
{
	STATUS_OK = 0,
	STATUS_TIMEOUT = 1,
	STATUS_NETWORK_ERROR = 2,
	STATUS_INVALID_ANSWER = 3,
	STATUS_PROGRAM_ERROR = 4
} t_ping_status;

static const struct addrinfo hints = {0, AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, NULL, NULL, NULL};

int			ping_error(const char* msg);

int			help_ft_ping(void);

int			parse_args(int argc, const char *argv[], t_parsed_cmd *dest);
int			p_parsing_error(int err);

int			ping_addr(const struct addrinfo *addrinfo, const t_parsed_cmd* command);

void		print_start(const char* dest, const char* ip, int size);
void		print_result(const t_ping_result *result);
void		update_stats(const t_ping_result *result,t_ping_stats *stats);
void		print_stats(const char* dest, const t_ping_stats *stats);

void		play_alert_sound(void);

void		*make_icmp_packet(int size, u_int16_t sequence);
bool		check_icmp_packet_checksum(ssize_t len, struct icmphdr	*packet);

u_int16_t	calculate_checksum(const void* data, size_t len);
int			strict_atoi(const char *str);
u_long_long	get_ust(void);

#endif
