/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/02 12:13:20 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = philo_pointer;
	while (is_finished(philo))
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			message("died", philo);
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = philo_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (philo->data->number_of_philosophers == 1)
	{
		message("has taken a fork", philo);
		usleep(philo->data->time_to_die * 1000);
		message("died", philo);
	}
	while (is_finished(philo))
	{
		eat(philo);
		message("is thinking", philo);
	}
	return (NULL);
}

int	launch_and_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->tid[i], NULL, &routine
				, &data->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&data->philos->thread, NULL, &supervisor
			, data->philos) != 0)
		return (-1);
	usleep(1000);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(data->philos->thread, NULL) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	supervisor;

	if (check_args(ac, av) == -1 || init_av(ac, av, &data) == -1)
		return (-1);
	init_forks(&data);
	init_philos(&data);
	data.start_time = get_time();
	if (launch_and_join(&data) != 0)
		return (-1);
	destroy(&data);
	return (0);
}
