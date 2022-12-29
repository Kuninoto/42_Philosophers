/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:34:11 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 15:54:55 by nnuno-ca         ###   ########.fr       */
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
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - 48);
	if (res > INT_MAX || res <= INT_MIN)
		on_error("One of the arguments overflows integer type");
	return ((int)res);
}
