/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:16:58 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/01 04:55:27 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		message("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		message("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		message("has taken a fork", philo);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	message("is eating", philo);
	philo->time_to_die = philo->data->time_to_die + get_time();
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	message("is sleeping", philo);
	if (philo->data->number_of_meals != -1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->meals_eaten == philo->data->number_of_meals)
			philo->data->philos_finished_eating++;
		if (philo->data->philos_finished_eating
			>= philo->data->number_of_philosophers)
			philo->data->program_end = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	ft_usleep(philo->data->time_to_sleep);
}

void	message(char *str, t_philo *philo)
{
	long long unsigned int	time;

	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp("died", str) == 0 && philo->data->program_end == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->program_end = 1;
	}
	if (philo->data->program_end == 0)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_unlock(&philo->data->lock);
}

int	is_finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->program_end == 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}
