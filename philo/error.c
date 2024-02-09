/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:29:48 by lsabatie          #+#    #+#             */
/*   Updated: 2024/02/09 17:45:35 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_int(char *str, t_data *data)
{
	free(data);
	printf("%s\n", str);
	return (-1);
}

void	*error_void(char *str, t_data *data)
{
	free_data(data);
	printf("%s\n", str);
	return (NULL);
}
