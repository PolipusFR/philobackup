/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:15:24 by lsabatie          #+#    #+#             */
/*   Updated: 2024/01/26 03:05:20 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h> // malloc/free
# include <sys/time.h> // gettimeofday
# include <stdio.h> // printf
# include <unistd.h> // usleep

struct	s_data;

typedef struct	s_philo
{
	pthread_t thread;
	struct s_data	*data;
	int	id;
	int	dead;
	int meals_eaten;
	int eating;
	long long unsigned int time_to_die;
	pthread_mutex_t lock;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philo;

typedef struct	s_data
{
	pthread_t	*tid;
	t_philo	*philos;
	int	program_end; // the program should end, either a philo died or they ate enough
    int philos_finished_eating; // number of philos that ate the correct number of meals
	int	number_of_philosophers;
	long long unsigned int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	long long unsigned start_time;
		
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;



int	ft_atoi(const char *str);
#endif