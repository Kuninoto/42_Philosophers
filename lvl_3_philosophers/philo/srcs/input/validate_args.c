/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:46:47 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 18:42:58 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	is_all_digits(char **argv)
{
	int i = 1;
	int j;

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (isdigit_or_signal(argv[i][j++]) == false)
				on_error("Not all arguments are numbers");
		}
		i++;
	}
}

void	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		on_error("Invalid number of arguments");
	is_all_digits(argv);
}
