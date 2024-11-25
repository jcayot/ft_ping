//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int	help_ft_ping(void)
{
	const char help[423] = "Usage\nping [options] <destination>\n\nOptions:\n"
						"\t<destination>      dns name or ip address\n"
		"\t-?                 print help and exit\n"
		"\t-a                 use audible ping\n"
		"\t-c <count>         stop after <count> replies\n"
		"\t-l <preload>       send <preload> number of packages while waiting replies\n"
		"\t-q                 quiet output\n"
		"\t-s <size>          use <size> as number of data bytes to be sent\n"
		"\t-v                 verbose output\n"
		"\n";

	write(STDOUT_FILENO, help, 423);
	return (0);
}
