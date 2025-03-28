/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:54:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:38:19 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* In case there's an error on initializing any fork this is
the function responsible for destroy the mutexes that were creating
so far and freeing the fork's array 
This situation would be suitable to call panic()
but it assumes that there will be nbr_philos forks on that array 
and here we only have [0, until] forks because some initialization failed */
static void	free_forks_until(pthread_mutex_t *forks, int until)
{
	int	i;

	i = 0;
	while (i <= until)
	{
		pthread_mutex_destroy(&forks[i]);
		i += 1;
	}
	free(forks);
}

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(args->nbr_of_philo * sizeof(pthread_mutex_t));
	if (!forks)
		panic(args, NULL, NULL, MALLOC_ERR);
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks_until(forks, i);
			panic(args, NULL, NULL, MUTEX_INIT_ERR);
		}
		i += 1;
	}
	return (forks);
}
