/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:16:58 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 15:59:26 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(time_t time)
{
	time_t	stop;

	stop = get_time() + time;
	while (get_time() < stop)
		usleep(10);
}

void	message(char *str, int from_supervisor, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (is_finished(philo->data) == 1 && from_supervisor == 0)
	{
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	printf("%ld %d %s\n", get_time() - philo->data->start_time,
		philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	is_finished(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->should_stop == 1)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}
