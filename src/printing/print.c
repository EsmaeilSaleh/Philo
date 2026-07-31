/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   print.c                                              :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:38:38 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:38:38 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *msg)
{
	t_table	*table;
	long	timestamp;
	int		stopped;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->stop_lock);
	stopped = table->stop;
	pthread_mutex_unlock(&table->stop_lock);
	if (!stopped)
	{
		timestamp = get_time_ms() - table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&table->print_lock);
}

void	print_death(t_philo *philo)
{
	t_table	*table;
	long	timestamp;

	table = philo->table;
	pthread_mutex_lock(&table->print_lock);
	pthread_mutex_lock(&table->stop_lock);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_lock);
	timestamp = get_time_ms() - table->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&table->print_lock);
}
