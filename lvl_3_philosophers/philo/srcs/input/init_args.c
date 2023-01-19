/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/19 00:30:28 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

#define MUST_EAT_0 "Philosophers do not need to eat\n"

bool	init_args(t_args *args, char **argv)
{
	args->nbr_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_times = -1;
	if (argv[5])
		args->must_eat_times = ft_atoi(argv[5]);
	if (args->must_eat_times == 0)
	{
		printf(MUST_EAT_0);
		return (false);
	}
	if (pthread_mutex_init(&args->monitoring_mutex, NULL) != 0)
	{
		panic(MUTEX_INIT_ERR);
		return (false);
	}
	args->satisfied_philos = 0;
	args->someone_died = false;
	return (true);
}
