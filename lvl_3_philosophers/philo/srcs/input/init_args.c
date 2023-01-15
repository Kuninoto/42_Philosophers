/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 19:35:38 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

#define MUST_EAT_0 "Philosophers do not need to eat\n"

t_args	init_args(char **argv)
{
	t_args	args;

	args.nbr_of_philo = long_atoi(argv[1]);
	args.time_to_die = long_atoi(argv[2]);
	args.time_to_eat = long_atoi(argv[3]);
	args.time_to_sleep = long_atoi(argv[4]);
	args.must_eat_times = -1;
	if (argv[5])
		args.must_eat_times = long_atoi(argv[5]);
	if (args.must_eat_times == 0)
	{
		printf(MUST_EAT_0);
		exit(EXIT_SUCCESS);
	}
	if (pthread_mutex_init(&args.monitoring_mutex, NULL) == 0)
		panic(MUTEX_INIT_ERR);
	return (args);
}
