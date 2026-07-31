/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   cleanup.c                                            :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:53:12 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:53:12 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->stop_lock);
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philos);
}
