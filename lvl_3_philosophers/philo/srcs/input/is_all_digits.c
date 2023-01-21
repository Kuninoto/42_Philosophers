/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:46:47 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:37:54 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_all_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (isdigit_or_signal(argv[i][j]) == false)
				return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}
