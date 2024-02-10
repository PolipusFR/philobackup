/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:29:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/10 17:03:00 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_main(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	error_int(char *str, t_data *data)
{
	free_data(data);
	printf("%s\n", str);
	return (-1);
}

void	*error_void(char *str, t_data *data)
{
	free_data(data);
	printf("%s\n", str);
	return (NULL);
}

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (NULL);
	if (data->forks_mutex)
		free(data->forks_mutex);
	if (data->philos)
	{
		while (i < data->number_of_philosophers)
		{
			if (data->philos[i])
				free(data->philos[i]);
			i++;
		}
		free (data->philos);
	}
	free(data);
	return (NULL);
}
