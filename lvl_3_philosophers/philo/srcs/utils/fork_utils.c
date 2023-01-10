/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:11:15 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/10 17:12:01 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t *forks;
	int i;

	forks = malloc(args->nbr_of_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
        		panic("Mutex init has failed");
		i += 1;
	}
	return (forks);
}

void	destroy_forks(t_args *args, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}
