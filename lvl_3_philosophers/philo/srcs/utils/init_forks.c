/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:54:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 19:20:41 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(args->nbr_of_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < args->nbr_of_philo)
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
			panic("Mutex init has failed");
	return (forks);
}
