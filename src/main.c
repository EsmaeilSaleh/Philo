/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   main.c                                               :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:53:42 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:53:42 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				philo_routine, &table->philos[i]) != 0)
		{
			pthread_mutex_lock(&table->stop_lock);
			table->stop = 1;
			pthread_mutex_unlock(&table->stop_lock);
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (parse_args(&table, argc, argv) != 0)
		return (1);
	if (init_table(&table) != 0)
		return (1);
	if (create_philosophers(&table) != 0)
	{
		destroy_table(&table);
		return (1);
	}
	run_monitor(&table);
	i = 0;
	while (i < table.num_philos)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	destroy_table(&table);
	return (0);
}
