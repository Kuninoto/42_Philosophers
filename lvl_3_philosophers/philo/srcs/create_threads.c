/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 02:43:10 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Thread that watches the philosophers' activity */
static void	*supervisor(void *philos)
{
	t_philo	*casted;
	int		i;

	casted = (t_philo *)philos;
	while (!all_ate_n_times(casted))
	{
		i = 0;
		while (i < casted->args->nbr_of_philo)
		{
			if (starved(&casted[i]) && casted[i].can_die)
			{
				monitoring(casted, DEAD);
				casted->args->someone_died = true;
				pthread_mutex_unlock(&casted[i].args->monitoring_mutex);
				return (NULL);
			}
			if (casted[i].eaten_meals == casted->args->must_eat_times)
				casted->args->satisfied_philos += 1;
			i += 1;
		}
	}
	printf("Every Philosopher had %d meals!\n", casted->args->must_eat_times);
	return (NULL);
}

/* Creates and makes main thread join supervisor thread */
static void	create_supervisor(t_args *args, pthread_mutex_t *forks,
											t_philo *philos)
{
	pthread_t	supervisor_tid;

	if (pthread_create(&supervisor_tid, NULL,
			supervisor, (void *)philos) != 0)
	{
		destroy(args, forks, philos);
		panic(THREAD_CREATE_ERR);
	}
	if (pthread_join(supervisor_tid, NULL) != 0)
	{
		destroy(args, forks, philos);
		panic(THREAD_JOIN_ERR);
	}
}

void	create_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL,
				routine, (void *)&philos[i]) != 0)
		{
			destroy(args, forks, philos);
			panic(THREAD_CREATE_ERR);
		}
		i += 1;
	}
	create_supervisor(args, forks, philos);
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_join(philos[i].t_id, NULL) != 0)
		{
			destroy(args, forks, philos);
			panic(THREAD_JOIN_ERR);
		}
		i += 1;
	}
}

/* One philosopher is deadlocking because it is locking the same mutex twice
aka his left mutex is the same as the right one */
