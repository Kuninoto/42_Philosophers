/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:53:37 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 19:22:07 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	destroy(t_args *args, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		philos[i].left_fork = NULL;
		philos[i].right_fork = NULL;
		i += 1;
	}
	pthread_mutex_destroy(&args->monitoring_mutex);
	free(forks);
	forks = NULL;
	free(philos);
	philos = NULL;
}
