/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   init.c                                               :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:24:22 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:24:22 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_forks(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	destroy_philo_locks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	free(table->philos);
}

static int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = table->start_time;
		philo->left_fork = &table->forks[i];
		philo->right_fork = &table->forks[(i + 1) % table->num_philos];
		philo->table = table;
		if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		{
			destroy_philo_locks(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	table->stop = 0;
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->stop_lock);
		return (1);
	}
	table->start_time = get_time_ms();
	if (init_forks(table) != 0)
	{
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->stop_lock);
		return (1);
	}
	if (init_philos(table) != 0)
	{
		destroy_forks(table, table->num_philos);
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->stop_lock);
		return (1);
	}
	return (0);
}
