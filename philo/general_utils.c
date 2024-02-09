/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:14:34 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 17:46:04 by lsabatie         ###   ########.fr       */
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
		if (i == 1 && (number <= 0 || number > 200))
			return (0);
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
	return ((tv.tv_sec * (long long unsigned int)1000) + (tv.tv_usec / 1000));
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

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (NULL);
	if (data->forks_mutex)
		free(data->forks_mutex);
	if (data->philos)
	{
		while (i < data->number_of_philosophers)
		{
			if (data->philos[i])
				free(data->philos[i]);
			i++;
		}
		free (data->philos);
	}
	free(data);
	return (NULL);
}
