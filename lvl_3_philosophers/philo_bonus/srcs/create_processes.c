/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/16 16:21:39 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

#define FORK_ERR "failed to fork()"

static void	end_processes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->args->nbr_of_philo)
	{
		kill(philos[i].pid, SIGKILL);
		i += 1;
	}
}

/* Process that watches the philosophers activity */
static void	supervisor(void *philos)
{
	t_philo	*casted;
	int		satisfied_philos;
	int		i;

	casted = (t_philo *)philos;
	satisfied_philos = 0;
	while (satisfied_philos != casted->args->nbr_of_philo)
	{
		i = 0;
		while (i < casted->args->nbr_of_philo)
		{
			if (starved(&casted[i]) && casted[i].can_die)
			{
				end_processes(casted);
				monitoring(casted, DEAD);
				exit(EXIT_SUCCESS);
			}
			printf("eaten meals = %d\n", casted[i].eaten_meals);
			if (casted[i].eaten_meals == casted->args->must_eat_times)
				satisfied_philos += 1;
			i += 1;
		}
		//printf("Satisfied_philos = %d\n", satisfied_philos);
	}
	end_processes(casted);
	printf("Every Philosopher had %d meals!\n", casted->args->must_eat_times);
	exit(EXIT_SUCCESS);
}

/* Creates supervisor process and makes main process wait for its pid */
static void	create_supervisor(t_args *args, t_philo *philos)
{
	int			exit_status;
	pid_t		supervisor_pid;

	supervisor_pid = fork();
	if (supervisor_pid == -1)
	{
		destroy(args, philos);
		panic(FORK_ERR);
	}
	if (supervisor_pid == 0)
		supervisor(philos);
	else
		waitpid(-1, exit_status, 0);
}

void	create_processes(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			destroy(args, philos);
			panic(FORK_ERR);
		}
		if (philos[i].pid == 0)
			routine(&philos[i]);
		i += 1;
	}
	create_supervisor(args, philos);
}
