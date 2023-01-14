/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 17:06:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

// t_id stands for thread identifier (id).

int	main(int argc, char **argv)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	validate_args(argc, argv);
	args = init_fill_args(argv);
	forks = init_forks(&args);
	philos = init_philos(&args, forks);
	create_threads(&args, philos);
	destroy_mutexes(&args, forks, philos);
	free(philos);
	return (EXIT_SUCCESS);
}
