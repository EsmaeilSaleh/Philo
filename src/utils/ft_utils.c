/* ************************************************************************** */
/*                                                                            */
/*                                                          :::      :::::::: */
/*   ft_utils.c                                           :+:      :+:    :+: */
/*                                                        +:+ +:+         +:+ */
/*   By: esaleh <esaleh@student.42berlin.de>               +#+  +:+       +#+ */
/*                                                          +#+#+#+#+#+   +#+ */
/*   Created: 2026/07/16 22:42:12 by esaleh                        #+#    #+# */
/*   Updated: 2026/07/16 22:42:12 by esaleh                 ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	is_overflow(long result, int digit)
{
	if (result > (LONG_MAX - digit) / 10)
		return (1);
	return (0);
}

static long	parse_digits(const char *str, int *i, int *error)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		if (is_overflow(result, str[*i] - '0'))
		{
			*error = 1;
			return (0);
		}
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

long	ft_atol_strict(const char *str, int *error)
{
	int		i;
	int		sign;
	int		start;
	long	result;

	*error = 0;
	i = 0;
	sign = get_sign(str, &i);
	start = i;
	result = parse_digits(str, &i, error);
	if (*error == 1)
		return (0);
	if (i == start || str[i] != '\0')
	{
		*error = 1;
		return (0);
	}
	return (result * sign);
}
