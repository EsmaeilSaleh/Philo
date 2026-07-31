/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   parsing.c                                            :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 23:01:53 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:01:53 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static void	print_usage(void)
{
	const char	msg[] = "Usage: ./philo n_philos die eat sleep [n_meals]\n";

	write(2, msg, sizeof(msg) - 1);
}

static long	parse_field(const char *arg, long max, int *error)
{
	long	value;

	value = ft_atol_strict(arg, error);
	if (*error == 1)
		return (0);
	if (value < 1 || value > max)
	{
		*error = 1;
		return (0);
	}
	return (value);
}

static int	parse_required(t_table *table, char **argv)
{
	int	error;

	error = 0;
	table->num_philos = (int)parse_field(argv[1], INT_MAX, &error);
	if (error)
		return (1);
	table->time_to_die = parse_field(argv[2], LONG_MAX, &error);
	if (error)
		return (1);
	table->time_to_eat = parse_field(argv[3], LONG_MAX, &error);
	if (error)
		return (1);
	table->time_to_sleep = parse_field(argv[4], LONG_MAX, &error);
	if (error)
		return (1);
	return (0);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	int	error;

	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (1);
	}
	if (parse_required(table, argv) != 0)
	{
		print_usage();
		return (1);
	}
	table->must_eat_count = -1;
	if (argc == 6)
	{
		error = 0;
		table->must_eat_count = (int)parse_field(argv[5], INT_MAX, &error);
		if (error)
		{
			print_usage();
			return (1);
		}
	}
	return (0);
}
