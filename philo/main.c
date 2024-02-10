/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:13:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/10 12:06:33 by lsabatie         ###   ########.fr       */
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

static void	join_threads(t_data *data)
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
		return (error_main("Error: Wrong number of arguments"));
	if (!check_args(ac, av))
		return (error_main("Error: Non-valid arguments"));
	data = init_data(ac, av);
	if (!data)
		return (error_main("Error: Failed initializing data structure"));
	if (launch_threads(data) != 0)
		return (error_main("Error: Failed launching threads"));
	join_threads(data);
	return (0);
}
