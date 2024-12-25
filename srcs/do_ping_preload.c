//
// Created by jules on 10/12/2024.
//

#include <ft_ping.h>

int	send_process(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, int outpipe, int inpipe)
{
	(void)sfd;
	(void)addrinfo;
	(void)cmd;
	(void)outpipe;
	(void)inpipe;
	return (0);
}

int	recv_process(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, int outpipe, int inpipe)
{
	(void)sfd;
	(void)addrinfo;
	(void)cmd;
	(void)outpipe;
	(void)inpipe;
	return (0);
}

int	do_ping_preload(int sfd, const struct addrinfo *addrinfo, const t_parsed_cmd *cmd, t_ping_stats *stats)
{
	(void)stats;
	int	send_to_main[2], main_to_send[2];
	if (pipe(send_to_main) == -1)
		return (STATUS_PROGRAM_ERROR);
	if (pipe(main_to_send) == -1)
		return (!close_pipe(send_to_main));

	pid_t	pid = fork();
	if (pid == -1)
		return (!(close_pipe(send_to_main) && close_pipe(main_to_send)));
	if (pid == 0)
	{
		close(send_to_main[0]);
		close(main_to_send[1]);
		int	result = send_process(sfd, addrinfo, cmd, send_to_main[1], main_to_send[0]);
		exit(result);
	}
	close(send_to_main[1]);
	close(main_to_send[0]);
	int	result = recv_process(sfd, addrinfo, cmd, send_to_main[1], main_to_send[0]);
	close(send_to_main[0]);
	close(main_to_send[1]);
	return (result);
}
