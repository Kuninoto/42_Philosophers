/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:34:11 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 21:11:57 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/philosophers.h"

int	long_atoi(char *str)
{
	ssize_t	res;
	int		i;

	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			on_error("Arguments cannot be negative");
		i += 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i += 1;
	}
	if (res > INT_MAX || res <= INT_MIN)
		on_error("One of the arguments overflows integer type");
	else if (res == 0)
		on_error("Arguments must be bigger than 0");
	return ((int)res);
}
