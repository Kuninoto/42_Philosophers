/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:02:31 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

#define MUST_EAT_0 "Philosophers do not need to eat\n"

/* Unlinks and opens "/forks", "/meal" and "/print" named semaphores */
static void	open_sems(t_args *args)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_PRINT);
	args->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, args->nbr_of_philo);
	if (args->sem_forks == SEM_FAILED)
		panic(SEMOPEN_ERR);
	args->sem_meal = sem_open(SEM_MEAL, O_CREAT, S_IRWXU, 1);
	if (args->sem_meal == SEM_FAILED)
	{
		sem_close(args->sem_forks);
		panic(SEMOPEN_ERR);
	}
	args->sem_print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	if (args->sem_print == SEM_FAILED)
	{
		sem_close(args->sem_forks);
		sem_close(args->sem_meal);
		panic(SEMOPEN_ERR);
	}
}

t_args	init_args(char **argv)
{
	t_args	args;

	args.nbr_of_philo = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	args.must_eat_times = -1;
	if (argv[5])
		args.must_eat_times = ft_atoi(argv[5]);
	if (args.must_eat_times == 0)
	{
		printf(MUST_EAT_0);
		exit(EXIT_SUCCESS);
	}
	open_sems(&args);
	return (args);
}
