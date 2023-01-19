/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:56:26 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/* Waits and kills all philosophers processes */
void	wait_childs(t_philo *philos)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		end_processes(philos);
}

/* Thread that watches the philosophers activity */
static void	*supervisor(void *philo)
{
	t_philo	*casted;

	casted = (t_philo *)philo;
	while (true)
	{
		sem_wait(casted->sem_lock_death);
		if (starved(casted))
		{
			monitoring(casted, DEAD);
			sem_wait(casted->args->sem_print);
			//return (NULL);
			exit(EXIT_SUCCESS);
		}
		sem_post(casted->sem_lock_death);
	}
	return (NULL);
}

/* Creates supervisor thread and makes philosopher process enter routine() */
static void	create_philo(t_philo *philo)
{
	pthread_t	supervisor_tid;

	pthread_create(&supervisor_tid, NULL, supervisor, (void *)philo);
	pthread_detach(supervisor_tid);
	routine(philo);
	exit(EXIT_SUCCESS);
}

void	create_processes(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	if (args->must_eat_times > 0)
		create_eats_checker(args, philos);
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
			create_philo(&philos[i]);
		usleep(100);
		i += 1;
	}
	wait_childs(philos);
}
