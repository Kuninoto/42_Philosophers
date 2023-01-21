/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:59:41 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:37:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philos(t_args *args, pthread_mutex_t *forks_array)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
	{
		destroy(args, forks_array, NULL);
		panic(MALLOC_ERR);
	}
	i = -1;
	while (++i < args->nbr_of_philo)
	{
		philos[i].philo_nbr = i + 1;
		philos[i].eaten_meals = 0;
		philos[i].left_fork = &forks_array[i];
		philos[i].right_fork = &forks_array[(i + 1) % args->nbr_of_philo];
		philos[i].last_meal_time = get_time();
		if (pthread_mutex_init(&philos[i].can_die, NULL) != 0)
		{
			destroy(args, forks_array, philos);
			panic(MUTEX_INIT_ERR);
		}
		philos[i].args = args;
	}
	return (philos);
}
