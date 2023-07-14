/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:37:44 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	pick_forks(t_philo *philo)
{
	if (philo->philo_nbr % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		monitoring(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		monitoring(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		monitoring(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		monitoring(philo, FORK);
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->philo_nbr % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		monitoring(philo, DROP);
		pthread_mutex_unlock(philo->right_fork);
		monitoring(philo, DROP);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		monitoring(philo, DROP);
		pthread_mutex_unlock(philo->left_fork);
		monitoring(philo, DROP);
	}
}

/* Encapsulates the eat philosopher action.
Locks left and right fork, sleeps time_to_eat miliseconds,
unlocks left and right fork (mutexes) and prints its respective
monitoring messages */
static void	eat(t_philo *philo)
{
	pick_forks(philo);
	pthread_mutex_lock(&philo->args->monitoring_mutex);
	philo->last_meal_time = get_time();
	philo->eaten_meals += 1;
	pthread_mutex_unlock(&philo->args->monitoring_mutex);
	monitoring(philo, EAT);
	usleep(philo->args->time_to_eat * MICROSEC);
	drop_forks(philo);
}

static inline void	_sleep(t_philo *philo)
{
	monitoring(philo, SLEEP);
	usleep(philo->args->time_to_sleep * MICROSEC);
}

void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->args->nbr_of_philo == 1)
	{
		monitoring(philo, FORK);
		return (NULL);
	}
	while (true)
	{
		pthread_mutex_lock(&philo->args->monitoring_mutex);
		if (philo->args->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->args->monitoring_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->monitoring_mutex);
		eat(philo);
		_sleep(philo);
		monitoring(philo, THINK);
	}
	return (NULL);
}
