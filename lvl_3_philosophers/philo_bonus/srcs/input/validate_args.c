/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:46:47 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 17:44:01 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

static void	is_all_digits(char **argv)
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
				panic("Not all arguments are numbers");
			j += 1;
		}
		i += 1;
	}
}

void	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		panic("Invalid number of arguments");
	is_all_digits(argv);
}
