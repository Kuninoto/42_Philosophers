/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fill_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 16:42:43 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

t_args	init_fill_args(char **argv)
{
	t_args	args;

	args.nbr_of_philo = long_atoi(argv[1]);
	args.time_to_die = long_atoi(argv[2]);
	args.time_to_eat = long_atoi(argv[3]);
	args.time_to_sleep = long_atoi(argv[4]);
	if (argv[5])
		args.must_eat_times = long_atoi(argv[5]);
	else
		args.must_eat_times = -1;
	args.is_anyone_dead = false;
	pthread_mutex_init(&args.monitoring_mutex, NULL);
	return (args);
}