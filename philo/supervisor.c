/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:52:34 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/14 13:21:48 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_death(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_ate) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->should_stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		message("died", 1, philo);
		pthread_mutex_unlock(&philo->time_mutex);
		return (1);
	}
	return (0);
}

static int	program_should_end(t_data *data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 1;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philos[i]->time_mutex);
		if (philo_death(data->philos[i]))
			return (1);
		if (data->number_of_meals != -1)
			if (data->philos[i]->meals_eaten < data->number_of_meals)
				finished_eating = 0;
		pthread_mutex_unlock(&data->philos[i]->time_mutex);
		i++;
	}
	if (data->number_of_meals != -1 && finished_eating == 1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->should_stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*supervisor(void *data_pointer)
{
	t_data	*data;

	data = data_pointer;
	if (data->number_of_meals == 0)
		return (NULL);
	pthread_mutex_lock(&data->stop_mutex);
	data->should_stop = 0;
	pthread_mutex_unlock(&data->stop_mutex);
	ft_usleep(100, data);
	wait_to_start(data->start_time);
	while (1)
	{
		if (program_should_end(data) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
