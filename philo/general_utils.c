/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:14:34 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/10 12:10:48 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	number;

	i = 1;
	while (i < ac)
	{
		if (!ft_isdigit(av[i]))
			return (0);
		number = ft_atoi(av[i]);
		if (i != 1 && number == -1)
			return (0);
		i++;
	}
	return (1);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t time, t_data *data)
{
	time_t	stop;

	stop = get_time() + time;
	while (get_time() < stop)
	{
		if (is_finished(data) == 1)
			break ;
		usleep(100);
	}
}

int	ft_atoi(char *str)
{
	int							i;
	unsigned long long int		number;

	i = 0;
	number = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return (number);
}
