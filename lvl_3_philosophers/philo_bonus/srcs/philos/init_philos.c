/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:59:41 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 17:46:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

/* Unlinks and opens "/can_die" named binary semaphore 
Returns false if it failed to open the semaphore */
static bool	open_sem(t_philo *philo)
{
	sem_unlink(SEM_CAN_DIE);
	philo->can_die = sem_open(SEM_CAN_DIE, O_CREAT, S_IRWXU, 1);
	if (philo->can_die == SEM_FAILED)
		return (false);
	return (true);
}

t_philo	*init_philos(t_args *args)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		panic(MALLOC_ERR);
	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].philo_nbr = i + 1;
		philos[i].must_eat_meals = args->must_eat_times;
		philos[i].last_meal_time = get_time();
		philos[i].is_alive = true;
		philos[i].args = args;
		if (!open_sem(&philos[i]))
		{
			destroy(args, philos);
			panic(SEMOPEN_ERR);
		}
		i += 1;
	}
	return (philos);
}
