/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:15:24 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/08 16:35:49 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h> // malloc/free
# include <sys/time.h> // gettimeofday
# include <stdio.h> // printf
# include <unistd.h> // usleep

typedef struct	s_data	t_data;

typedef struct s_philo
{
	t_data					*data;
	int						id;
	int						dead;
	int						meals_eaten;
	int						eating;
	long long unsigned int	time_to_die;
	pthread_mutex_t			lock;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t			*tid;
	pthread_t			supervisor;
	t_philo				*philos;
	int					program_end;
	int					philos_finished_eating;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	long long unsigned	start_time;

	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}	t_data;

int					ft_atoi(const char *str);
void				ft_usleep(long long unsigned int time);
void				message(char *str, t_philo *philo);
int					check_args(int ac, char **av);

int					init_av(int ac, char **av, t_data *data);
void				init_philos(t_data *data);
void				init_forks(t_data *data);

int					ft_strcmp(char *s1, char *s2);
long long unsigned	get_time(void);
void				destroy(t_data *data);

void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				message(char *str, t_philo *philo);
int					is_finished(t_philo *philo);

#endif