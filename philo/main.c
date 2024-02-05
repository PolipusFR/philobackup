/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/05 14:57:04 by lsabatie         ###   ########.fr       */
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
		{
			message("died", philo);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

// int	program_should_end(t_data *data)
// {
// 	pthread_mutex_lock(&data->lock);
// 	if (data->program_end == 1)
// 	{
// 		pthread_mutex_unlock(&data->lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->lock);
// 	return (0);
// }

// void	*supervisor(void *data_pointer)
// {
// 	t_data	*data;
	
// 	data = (t_data *)data_pointer;
// 	while (1)
// 	{
// 		if (program_should_end(data) == 1)
// 			return (NULL);
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = philo_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		message("has taken a fork", philo);
		ft_usleep(philo->data->time_to_die);
		message("died", philo);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (is_finished(philo))
	{
		eat(philo);
		message("is thinking", philo);
	}
	return (NULL);
}

int	launch_threads(t_data *data)
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
	return (0);
}

int join_threads(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(data->philos->thread, NULL) != 0)
		return (-1);
	destroy(data);
	return (0);
	
}

int	main(int ac, char **av)
{
	t_data		data;

	if (check_args(ac, av) == -1 || init_av(ac, av, &data) == -1)
		return (-1);
	init_forks(&data);
	init_philos(&data);
	data.start_time = get_time();
	if (launch_threads(&data) != 0)
		return (EXIT_FAILURE);
	join_threads(&data);
	return (EXIT_SUCCESS);
}
