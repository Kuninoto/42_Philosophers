/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 20:35:14 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

#define MUST_EAT_0 "Philosophers do not need to eat\n"

/* Unlinks and opens "/forks" and "/print" named counting & binary semaphores */
static void	open_sems(t_args *args)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	args->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, args->nbr_of_philo);
	if (args->forks == SEM_FAILED)
		panic(SEMOPEN_ERR);
	args->print_sem = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	if (args->print_sem == SEM_FAILED)
	{
		sem_close(args->forks);
		panic(SEMOPEN_ERR);
	}
	args->someone_died_sem = sem_open(SEM_DEAD, O_CREAT, S_IRWXU, 1);
	if (args->someone_died_sem == SEM_FAILED)
	{
		sem_close(args->forks);
		sem_close(args->print_sem);
		panic(SEMOPEN_ERR);
	}
	args->eaten_sem = sem_open(SEM_DEAD, O_CREAT, S_IRWXU, 1);
	if (args->eaten_sem == SEM_FAILED)
	{
		sem_close(args->forks);
		sem_close(args->print_sem);
		sem_close(args->someone_died_sem);
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
	args.end = false;
	return (args);
}
