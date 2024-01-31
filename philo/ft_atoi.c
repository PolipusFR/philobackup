/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:22:10 by lsabatie          #+#    #+#             */
/*   Updated: 2024/01/31 03:16:14 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_caclulator(char *string, int i)
{
	int	number;

	number = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		if ((number * 10) / 10 != number)
			return (-1);
		number = number * 10 + string[i] - 48;
		i++;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		number;
	char	*string;
	
	i = 0;
	string = (char *)str;
	number = ft_caclulator(string, i);
	return (number);
}
