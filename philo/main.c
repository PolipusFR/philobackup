/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2023/12/18 17:41:57 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this function will assign main arguments value to newly created struct s_philo
void	init_av(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_meals = ft_atoi(av[5]);
	else
		data->number_of_meals = 100;
	data->philos = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return ;
}

// this function fills in the info for every philo in the program
void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		pthread_mutex_init(&data->philos[i].mutex, NULL);
		i++;
	}
}

// this function inits forks (1 fork per philo) and protect each one with a mutex
void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return ;
	while(i < data->number_of_philosophers)
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

long long unsigned	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (long long unsigned int)1000) + (tv.tv_usec / 1000));
}
// thinking function of philos
// void	thinking(t_data *data)
// {
	
// }

// death function of philos
void	death(t_philo *philo)
{
	long long unsigned time;
	
	time = get_time() - philo->data->start_time;
	printf("%llu %d died\n", time, philo->id);
}



int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo;

	
	if (ac < 5 || ac > 6)
		return (1);
	init_av(ac, av, &data);
	init_philos(&data);
	init_forks(&data);
	data.start_time = get_time();
	philo = data.philos[0];
	death(&philo);
	usleep(99999);
	death(&philo);
	return (0);
}