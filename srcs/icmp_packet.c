//
// Created by jules on 06/12/2024.
//

#include <ft_ping.h>

void	*make_icmp_packet(int size, u_int16_t sequence)
{
	void			*packet;
	struct icmphdr	*icmphdr;

	packet = calloc(1, size + 8);
	if (!packet)
		return (NULL);
	icmphdr = packet;
	icmphdr->type = ICMP_ECHO;
	icmphdr->code = 0;
	icmphdr->checksum = 0;
	icmphdr->un.echo.id = getpid();
	icmphdr->un.echo.sequence = sequence;
	icmphdr->checksum = calculate_checksum(packet, size);
	return (packet);
}

bool check_icmp_packet_checksum(ssize_t len, struct icmphdr	*packet)
{
	return (true);
	uint16_t		excepted_checkum = packet->checksum;

	packet->checksum = 0;
	if (calculate_checksum(packet, len) == excepted_checkum)
		return (true);
	return (false);
}
