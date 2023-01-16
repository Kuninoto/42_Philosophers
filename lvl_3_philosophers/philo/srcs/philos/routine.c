/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/16 20:49:41 by nnuno-ca         ###   ########.fr       */
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
static void	eat(t_philo *philo)
{
	pick_forks(philo);
	philo->can_die = false;
	monitoring(philo, EAT);
	usleep(philo->args->time_to_eat * MICROSEC);
	philo->last_meal_time = get_time();
	drop_forks(philo);
	philo->eaten_meals += 1;
	philo->can_die = true;
}

static void	_sleep(t_philo *philo)
{
	monitoring(philo, SLEEP);
	usleep(philo->args->time_to_sleep * MICROSEC);
}

void	*routine(void *philo)
{
	t_philo	*casted;

	casted = (t_philo *)philo;
	while (!casted->args->someone_died 
		&& !all_ate_n_times(casted))
	{
		eat(casted);
		_sleep(casted);
		monitoring(casted, THINK);
	}
	return (NULL);
}
