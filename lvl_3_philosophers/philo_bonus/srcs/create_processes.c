/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 21:09:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/* Thread that watches the philosophers activity */
static void	*supervisor(void *philo)
{
	t_philo	*casted;

	casted = (t_philo *)philo;
	while (true)
	{
		sem_wait(casted->can_die);
		if (starved(casted))
		{
			casted->is_alive = false;
			monitoring(casted, DEAD);
			sem_wait(casted->args->print_sem);
			sem_post(casted->args->someone_died_sem);
			return (NULL);
		}
		sem_post(casted->can_die);
		if (casted->must_eat_meals == 0)
			sem_wait(casted->args->eaten_sem);
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
}

static void	wait_childs(t_philo *philos)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 0;
	while (i < philos->args->nbr_of_philo)
	{
		waitpid(-1, &exit_status, 0);
		i += 1;
	}
	end_processes(philos);
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
			create_philo(&philos[i]);
		usleep(1);
		i += 1;
	}
	wait_childs(philos);
}
