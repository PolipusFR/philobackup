/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:14:34 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/02 11:21:22 by lsabatie         ###   ########.fr       */
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
