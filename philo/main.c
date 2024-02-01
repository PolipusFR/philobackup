/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/01 05:00:42 by lsabatie         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
		ft_usleep(10);
	if (pthread_create(&philo->thread, NULL, &supervisor, philo))
		return ((void *)0);
	while (is_finished(philo))
	{
		eat(philo);
		message("is thinking", philo);
	}
	if (!pthread_join(philo->thread, NULL))
		return ((void *)1);
	return (NULL);
}

int	launch_and_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (-1);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av) == -1 || init_av(ac, av, &data) == -1)
		return (-1);
	if (data.number_of_philosophers == 1)
	{
		case_one(&data);
		return (0);
	}
	init_forks(&data);
	init_philos(&data);
	ft_usleep(100);
	data.start_time = get_time();
	launch_and_join(&data);
	destroy(&data);
	return (0);
}
