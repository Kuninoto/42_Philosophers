/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 16:40:02 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

t_args	init_args(char **argv)
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
	unlink_sems();
	args.forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, args.nbr_of_philo);
	if (args.forks == SEM_FAILED)
		panic("Failed to open forks semaphore");
	args.print_sem = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	if (args.print_sem == SEM_FAILED)
	{
		sem_close(args.forks);
		panic("Failed to open print semaphore");
	}
	return (args);
}
