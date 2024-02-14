/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:15:24 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/14 13:20:36 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t				start_time;
	int					number_of_philosophers;
	pthread_t			supervisor;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					number_of_meals;
	int					should_stop;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		*forks_mutex;
	t_philo				**philos;
}	t_data;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						meals_eaten;
	int						fork[2];
	pthread_mutex_t			time_mutex;
	time_t					last_ate;
	t_data					*data;
}	t_philo;

int					ft_atoi(char *str);
void				ft_usleep(time_t time, t_data *data);
void				message(char *str, int from_supervisor, t_philo *philo);
void				wait_to_start(time_t start_time);
void				*supervisor(void *data_pointer);
void				*routine(void *philo_pointer);
int					check_args(int ac, char **av);
void				*free_data(t_data *data);
t_data				*init_data(int ac, char **av);
int					is_finished(t_data *data);
int					error_int(char *str, t_data *data, int main);
void				*error_void(char *str, t_data *data);
time_t				get_time(void);
void				destroy(t_data *data);
void				think_odd(t_philo *philo);

#endif