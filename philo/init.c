/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:11:18 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 16:17:31 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_forks(t_philo *philo)
{
	// verifier comprehension
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->data->number_of_philosophers;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->number_of_philosophers;
		philo->fork[1] = philo->id;
	}
}

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t)* data->number_of_philosophers);
	if (!forks)
		return(error_void("Error: malloc init failed", data));
	while(i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_void("Error: mutex init failed", data));
		i++;
	}
	return (forks);
}

static int	init_mutex(t_data *data)
{
	data->forks_mutex = init_forks(data);
	if (!data->forks_mutex)
		return (0);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (error_int("Error: mutex init failed", data));
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (error_int("Error: mutex init failed", data));
	return (1);
}

static t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
		return (error_void("Error: malloc init failed", data));
	while (i < data->number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (error_void("Error: malloc init failed", data));
		if (pthread_mutex_init(&philos[i]->time_mutex, 0) != 0)
			return (error_void("Error: mutex init failed", data));
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->meals_eaten = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;
	
	data = malloc (sizeof(t_data));
	if (!data)
		return (error_void("Error: mutex init failed", data));
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = -1;
	data->philos = init_philos(data);
	if (!data->philos)
		return (NULL);
	if (init_mutex(data) == -1)
		return (NULL);
	data->should_stop = 0;
	return (data);
}





