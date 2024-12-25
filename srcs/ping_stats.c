//
// Created by jules on 25/11/2024.
//

#include <ft_ping.h>

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
