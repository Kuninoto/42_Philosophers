/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:39:41 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline bool	is_digit(char c)
{
	return ((c >= '0' && c <= '9'));
}

static bool	is_all_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}

/* Checks if argc == 5 || == 6 & if all characters represent digits */
bool	valid_args(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || !is_all_digits(argv))
	{
		panic(NULL, NULL, NULL, INVALID_ARGS_ERR);
		return (false);
	}
	return (true);
}
