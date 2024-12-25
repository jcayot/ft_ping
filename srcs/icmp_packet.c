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

bool check_received_icmp_packet(size_t len, void* received)
{
	if (len < sizeof(struct iphdr) + sizeof(struct icmphdr))
		return (false);
	struct icmphdr	*icmphdr = received + sizeof(struct iphdr);
	uint16_t		excepted_checkum = icmphdr -> checksum;

	icmphdr->checksum = 0;
	if (calculate_checksum(received, len) == excepted_checkum)
		return (true);
	return (false);
}
