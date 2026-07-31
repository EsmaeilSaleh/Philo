/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   time_utils.c                                         :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:10:03 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:10:03 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + (long)tv.tv_usec / 1000);
}

void	precise_sleep(long ms, t_table *table)
{
	long	start;
	int		stopped;

	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&table->stop_lock);
		stopped = table->stop;
		pthread_mutex_unlock(&table->stop_lock);
		if (stopped || get_time_ms() - start >= ms)
			return ;
		usleep(500);
	}
}
