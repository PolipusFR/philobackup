/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2023/12/22 18:50:36 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_philo *philo);

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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
		data->number_of_meals = -1;
	data->tid = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!data->tid)
		return ;
	data->philos = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return ;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
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
		data->philos[i].eating = 0;
		data->philos[i].eat_count = 0;
		data->philos[i].dead = 0;
		data->philos[i].time_to_die = data->time_to_die;
		if (data->philos[i].id % 2 == 0)
			usleep(1);
		pthread_mutex_init(&data->philos[i].lock, NULL);
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
void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	message("has taken a fork", philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = philo->data->time_to_die + get_time();
	message("is eating", philo);
	philo->eat_count++;
	usleep(philo->data->time_to_eat * 1000);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	message("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	message(char *str, t_philo *philo)
{
	long long unsigned int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void *supervisor(void *philo_pointer)
{
	t_philo	*philo;
	
	philo = philo_pointer;
	while(philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			printf("time to die : %lld\n", philo->time_to_die);
			message("died", philo);
		}
		if (philo->eat_count == philo->data->number_of_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished = 1;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo *philo;

	philo = philo_pointer;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (pthread_create(&philo->thread, NULL, &supervisor, philo))
		return ((void *)0);
	while(philo->data->dead == 0)
	{
		eat(philo);
		message("is thinking", philo);
	}
	if (pthread_join(philo->thread, NULL))
		return((void *)1);
	return ((void *)0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (1);
	init_av(ac, av, &data);
	init_forks(&data);
	init_philos(&data);
	data.start_time = get_time();
	while (i < data.number_of_philosophers)
	{
		if (pthread_create(&data.tid[i], NULL, &routine, &data.philos[i]))
			return(-1);
		usleep(1);
		i++;
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		if (pthread_join(data.tid[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}