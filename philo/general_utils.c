/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:14:34 by lsabatie          #+#    #+#             */
/*   Updated: 2024/01/31 03:29:59 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

long long unsigned	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (long long unsigned int)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long long unsigned time)
{
	long long unsigned	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	case_one(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die);
	printf("%d 1 has died\n", data->time_to_die);
	return ;
}

void	destroy(t_data *data)
{
	if (data)
	{
		if (data->tid)
			free (data->tid);
		if (data->philos)
			free (data->philos);
		if (data->forks)
			free (data->forks);
	}
	return ;
}
