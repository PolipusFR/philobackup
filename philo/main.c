/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 17:32:34 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_to_start(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}

static int	launch_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time() + (data->number_of_philosophers * 2 * 10);
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &routine
				, data->philos[i]) != 0)
			return (error_int("Error: pthread create failed", data));
		i++;
	}
	if (data->number_of_philosophers > 1)
	{
		if (pthread_create(&data->supervisor, NULL, &supervisor
				, data) != 0)
		return (error_int("Error: pthread create failed", data));
	}
	return (0);
}

static void join_threads(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->number_of_philosophers > 1)
		pthread_join(data->supervisor, NULL);
	free_data(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return(1);
	if (!check_args(ac, av))
		return (1);
	data = init_data(ac, av);
	if (!data)
		return (1);
	if (launch_threads(data) != 0)
		return (EXIT_FAILURE);
	join_threads(data);
	return (EXIT_SUCCESS);
}
