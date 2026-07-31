/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   philo.h                                              :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 22:29:32 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 23:36:59 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

int		parse_args(t_table *table, int argc, char **argv);
int		init_table(t_table *table);
void	*philo_routine(void *arg);
int		run_monitor(t_table *table);
void	print_status(t_philo *philo, const char *msg);
void	print_death(t_philo *philo);
long	get_time_ms(void);
void	precise_sleep(long ms, t_table *table);
long	ft_atol_strict(const char *str, int *error);
void	destroy_table(t_table *table);

#endif
