/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 22:34:50 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philos;

	validate_args(argc, argv);
	args = init_args(argv);
	philos = init_philos(&args);
	create_processes(&args, philos);
	destroy(&args, philos);
	return (EXIT_SUCCESS);
}
