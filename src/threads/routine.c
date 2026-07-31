/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   routine.c                                            :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:43:35 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:43:35 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	should_stop(t_table *table)
{
	int	stopped;

	pthread_mutex_lock(&table->stop_lock);
	stopped = table->stop;
	pthread_mutex_unlock(&table->stop_lock);
	return (stopped);
}

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	while (!should_stop(philo->table))
		usleep(500);
	pthread_mutex_unlock(philo->left_fork);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->time_to_eat, philo->table);
	while (!should_stop(philo->table))
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is sleeping");
		precise_sleep(philo->table->time_to_sleep, philo->table);
	}
	return (NULL);
}
