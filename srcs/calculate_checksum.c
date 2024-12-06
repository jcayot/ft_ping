//
// Created by jules on 29/11/2024.
//

#include <calculate_checksum.h>

u_int16_t	calculate_checksum(const void* data, size_t len)
{
	u_int32_t		checksum;
	const u_int16_t*	word_data;

	checksum = 0;
	word_data = (const u_int16_t*) data;
	while (len > 1)
	{
		checksum += *word_data++;
		len -= 2;
	}
	if (len == 1)
	{
		checksum += *((const u_int8_t*)word_data);
	}
	while (checksum >> 16)
	{
		checksum = (checksum & 0xffff) + (checksum >> 16);
	}
	return ((u_int16_t) ~checksum);
}
