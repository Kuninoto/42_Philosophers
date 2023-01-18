/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:59:41 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:23:43 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

/* Unlinks and opens "/lock_death" named binary semaphore 
Returns false if sem_open() failed */
static bool	open_sem(t_philo *philo)
{
	sem_unlink(SEM_LOCK_DEATH);
	philo->sem_lock_death = sem_open(SEM_LOCK_DEATH, O_CREAT, S_IRWXU, 1);
	if (philo->sem_lock_death == SEM_FAILED)
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
		philos[i].last_meal_time = get_time();
		if (!open_sem(&philos[i]))
		{
			destroy(args, philos);
			panic(SEMOPEN_ERR);
		}
		philos[i].args = args;
		i += 1;
	}
	return (philos);
}
