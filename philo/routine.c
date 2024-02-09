/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:57:02 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 17:47:13 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->fork[0]]);
	message("has taken a fork", 0, philo);
	pthread_mutex_lock(&philo->data->forks_mutex[philo->fork[1]]);
	message("has taken a fork", 0, philo);
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	message("is eating", 0, philo);
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
	ft_usleep(philo->data->time_to_eat);
	if (is_finished(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->time_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->time_mutex);
	}
	message("is sleeping", 0, philo);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->fork[0]]);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->fork[1]]);
	ft_usleep(philo->data->time_to_sleep);
}

static void	think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->time_mutex);
	time_to_think = (philo->data->time_to_die
			- (get_time() - philo->last_ate)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->time_mutex);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	message("is thinking", 0, philo);
	ft_usleep(time_to_think);
}

static void	*routine_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->fork[0]]);
	message("has taken a fork", 0, philo);
	ft_usleep(philo->data->time_to_die);
	message("died", 0, philo);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->fork[0]]);
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = philo_pointer;
	if (philo->data->number_of_meals == 0)
		return (NULL);
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_ate = philo->data->start_time;
	pthread_mutex_unlock(&philo->time_mutex);
	wait_to_start(philo->data->start_time);
	if (philo->data->time_to_die == 0)
		return (NULL);
	if (philo->data->number_of_philosophers == 1)
	{
		routine_one(philo);
		return (NULL);
	}
	else if (philo->id % 2 == 1)
		think(philo);
	while (is_finished(philo->data) == 0)
	{
		eat(philo);
		think(philo);
	}
	return (NULL);
}
