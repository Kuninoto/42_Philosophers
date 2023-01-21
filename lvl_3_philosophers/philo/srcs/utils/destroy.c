/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:53:37 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:38:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_args *args, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&args->monitoring_mutex);
	if (forks)
	{
		i = 0;
		while (i < args->nbr_of_philo)
		{
			pthread_mutex_destroy(&philos[i].can_die);
			pthread_mutex_destroy(&forks[i]);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
			i += 1;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}
