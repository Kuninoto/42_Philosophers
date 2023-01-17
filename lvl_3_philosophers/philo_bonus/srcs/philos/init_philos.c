/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:59:41 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 12:10:13 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

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
		philos[i].can_die = true;
		philos[i].is_alive = true;
		philos[i].args = args;
		i += 1;
	}
	return (philos);
}
