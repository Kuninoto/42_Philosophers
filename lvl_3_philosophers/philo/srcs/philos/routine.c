/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 20:14:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	monitoring(philo, FORK);
	monitoring(philo, FORK);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	monitoring(philo, DROP);
	monitoring(philo, DROP);
}

/* Encapsulates the eat philosopher action. 
Locks left and right fork, sleeps time_to_eat miliseconds,
unlocks left and right fork (mutexes) and prints its respective 
monitoring messages */
void	eat(t_philo *philo)
{
	pick_forks(philo);
	philo->can_die = false;
	monitoring(philo, EAT);
	usleep(philo->args->time_to_eat * TO_MICROSEC);
	philo->last_meal_time = get_time();
	drop_forks(philo);
	philo->eaten_meals += 1;
}

void	*routine(void *philo)
{
	t_philo	*casted;

	casted = (t_philo *)philo;
	while (true)
	{
		eat(casted);
		monitoring(casted, SLEEP);
		usleep(casted->args->time_to_sleep * TO_MICROSEC);
		monitoring(casted, THINK);
		casted->can_die = true;
	}
	return (NULL);
}