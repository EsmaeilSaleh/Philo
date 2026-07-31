/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   monitor.c                                            :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:50:30 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:50:30 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_table *table)
{
	int		i;
	long	last;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		last = table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		if (get_time_ms() - last > table->time_to_die)
		{
			print_death(&table->philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_ate_enough(t_table *table)
{
	int		i;
	long	meals;

	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		meals = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		if (meals < table->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

int	run_monitor(t_table *table)
{
	while (1)
	{
		if (check_death(table))
			return (1);
		if (all_ate_enough(table))
		{
			pthread_mutex_lock(&table->stop_lock);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_lock);
			return (0);
		}
		usleep(500);
	}
}
