/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:38:26 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Auxiliary function just to encapsulate lines due to the norm */
static inline void	all_have_eaten(t_args *args)
{
	args->simulation_should_end = true;
	printf("Every Philosopher had %d meals!\n", args->must_eat_times);
	pthread_mutex_unlock(&args->monitoring_mutex);
}

/* Checks if a philosopher has died, returns true if so,
Also checks if the philosher have eaten <must_eat_times>,
and if so increments args.satisfied_philos and also checks */
static bool	is_philo_dead(t_args *args, t_philo *philo, int *satisfied_philos)
{
	if (args->must_eat_times > 0 && philo->eaten_meals >= args->must_eat_times)
		*satisfied_philos += 1;
	if (starved(philo))
	{
		pthread_mutex_unlock(&args->monitoring_mutex);
		monitoring(philo, DEAD);
		pthread_mutex_lock(&args->monitoring_mutex);
		args->simulation_should_end = true;
		pthread_mutex_unlock(&args->monitoring_mutex);
		return (true);
	}
	return (false);
}

/* Function that watches the philosophers' activity */
static void	supervise(t_philo *philos, t_args *args)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&args->monitoring_mutex);
		while (++i < args->nbr_of_philo)
		{
			if (is_philo_dead(args, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == args->nbr_of_philo)
			return (all_have_eaten(args));
		pthread_mutex_unlock(&args->monitoring_mutex);
	}
}

bool	launch_threads_and_join(t_args *args, t_philo *philos,
						pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL,
				routine, (void *)&philos[i]) != 0)
		{
			panic(args, forks, philos, THREAD_CREATE_ERR);
			return (false);
		}
	}
	supervise(philos, args);
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		if (pthread_join(philos[i].t_id, NULL) != 0)
		{
			panic(args, forks, philos, THREAD_JOIN_ERR);
			return (false);
		}
	}
	return (true);
}
