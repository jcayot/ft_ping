//
// Created by jules on 19/11/2024.
//

#ifndef FT_PING_H
# define FT_PING_H

# include <stdbool.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>
# include <pthread.h>
# include <arpa/inet.h>
# include <errno.h>
# include <signal.h>

# include <calculate_checksum.h>
# include <strict_atoi.h>
# include <close_pipe.h>

# ifndef MAX_SENDER_ADDR_LEN
#  define MAX_SENDER_ADDR_LEN	128
# endif

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
	int				status;
	u_int			size;
	u_int			seq;
	u_int			ttl;
	u_int			id;
	u_long			time;
	struct sockaddr	sender_addr;
	socklen_t		sender_addr_len;
}	t_ping_result;

typedef struct s_ping_stats
{
	struct timespec	start_time;
	struct timespec	end_time;
	u_int			sent;
	u_int			received;
	u_long			min;
	u_long			avg;
	u_long			max;
	u_long			mdev;
	int				result;
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
	STATUS_NO_ANSWER = 4,
	STATUS_PROGRAM_ERROR = 5
} t_ping_status;

static const struct addrinfo hints = {0, AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, NULL, NULL, NULL};

extern bool	running;

int			ping_error(const char* msg);

int			help_ft_ping(void);

int			parse_args(int argc, const char *argv[], t_parsed_cmd *dest);
int			p_parsing_error(int err);

int			do_ping(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats);
int			do_ping_preload(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats);

void		update_stats(const t_ping_result *result,t_ping_stats *stats);

void		print_socket_verbose(int sfd, int ai_socktype, int hints_ai_family);
void		print_start(const t_parsed_cmd* cmd, const struct addrinfo* dest_addr);
void		print_result(const t_ping_result *result, bool quiet, bool verbose);
void		print_stats(const char* dest, const t_ping_stats *stats);

void		play_alert_sound(void);

void		*make_icmp_packet(int size, u_int16_t sequence);
bool		check_received_icmp_packet(size_t len, void* received);

void		ip_from_addrinfo(const struct sockaddr *sa, int family, char *dest, int dest_size);
void		hostname_from_addrinfo(const struct sockaddr *sa, socklen_t sa_len, char *dest, int dest_size);
const char	*family_to_string(int ai_family);
const char	*ai_socktype_to_string(int ai_socktype);

void		handle_sigint(int sig);

#endif
