/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 21:58:40 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philos;

	validate_args(argc, argv);
	args = init_fill_args(argv);
	philos = init_philos(&args);
	create_processes(&args, philos);
	destroy(&args, philos);
	return (EXIT_SUCCESS);
}

/*
	There's a pool of forks in the middle of the table (counting semaphore) and philosophers try to take 2 to eat.
*/