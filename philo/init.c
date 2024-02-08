/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 02:11:18 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/08 17:13:43 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_av(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][0] == '0' && av[i][1] == '\0')
			return (-1);
		while (av[i][j])
		{
			if (av[i][j] >= 48 && av[i][j] <= 57)
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (-1);
	}
	if (is_valid_av(av) == -1)
	{
		printf ("Error: Wrong arguments");
		return (-1);
	}
	else
		return (0);
}

int	init_av(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	{
		printf ("Error: Argument overflow");
		return (-1);
	}
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = -1;
	data->tid = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->tid)
		return (-1);
	data->philos = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (-1);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].dead = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->program_end = 0;
		data->philos_finished_eating = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return ;
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->number_of_philosophers - 1];
	i = 1;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
}
