/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:34:11 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 00:19:55 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/philosophers_bonus.h"

int	ft_atoi(char *str)
{
	ssize_t	res;
	int		i;

	res = 0;
	i = 0;
	while (is_spaces(str[i]))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			panic("Arguments cannot be negative");
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i += 1;
	}
	if (res > INT_MAX || res <= INT_MIN)
		panic("One of the arguments overflows integer type");
	return ((int)res);
}
