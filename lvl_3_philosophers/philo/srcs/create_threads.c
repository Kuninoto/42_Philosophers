/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 17:09:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Thread that watches the philosophers activity */
void	*supervisor(void *philos)
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
			if (((get_time() - casted[i].last_meal_time)
					>= casted->args->time_to_die && casted[i].can_die))
			{
				monitoring(casted, DEAD);
				pthread_mutex_unlock(&casted[i].args->monitoring_mutex);
				return (NULL);
			}
			if (casted[i].eaten_meals == casted->args->must_eat_times)
				satisfied_philos += 1;
			i += 1;
		}
	}
	printf("Every Philosopher had %d meals!\n", casted->args->must_eat_times);
	return (NULL);
}

/* Creates and makes main thread join supervisor thread */
void	create_supervisor(void *philos)
{
	pthread_t	supervisor_id;

	pthread_create(&supervisor_id, NULL, supervisor, philos);
	pthread_join(supervisor_id, NULL);
}

void	create_threads(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL,
				routine, (void *)&philos[i]) != 0)
		{
			free(philos);
			panic("Failed to create a thread");
		}
		if (pthread_detach(philos[i].t_id) != 0)
		{
			free(philos);
			panic("Failed to detach a thread");
		}
		i += 1;
	}
	create_supervisor((void *)philos);
}