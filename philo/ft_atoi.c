/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabatie <lsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:22:10 by lsabatie          #+#    #+#             */
/*   Updated: 2023/10/20 01:24:39 by lsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_rm_whitespace(char *string)
{
	int	i;

	i = 0;
	while (string[i] == '\t' || string[i] == '\n' || string[i] == '\v'
		|| string[i] == '\f' || string[i] == '\r' || string[i] == ' ')
		i++;
	return (i);
}

static int	ft_caclulator(char *string, int i, int negative)
{
	int	number;

	number = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		if ((number * 10) / 10 != number)
		{
			if (negative == -1)
				return (0);
			else
				return (-1);
		}
		number = number * 10 + string[i] - 48;
		i++;
	}
	return (number * negative);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		number;
	int		negative;
	char	*string;

	string = (char *)str;
	negative = 1;
	i = ft_rm_whitespace(string);
	if (string[i] == '-')
		negative = -1;
	if (string[i] == '-' || string[i] == '+')
		i++;
	number = ft_caclulator(string, i, negative);
	return (number);
}
