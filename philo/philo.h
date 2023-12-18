/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:15:24 by lsabatie          #+#    #+#             */
/*   Updated: 2023/12/18 18:00:36 by lsabatie         ###   ########.fr       */
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
	int eat_cont;
	int eating;
	pthread_mutex_t lock;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
}	t_philo;

typedef struct	s_data
{
	pthread_t	*tid;
	t_philo	*philos;
	int	dead;
	int	finished;
	int	death_time;
    int	number_of_philosophers;
	int	time_to_die;
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