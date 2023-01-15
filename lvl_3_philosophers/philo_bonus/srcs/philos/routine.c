/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 16:43:19 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

static void	pick_forks(t_philo *philo)
{
	sem_wait(philo->args->forks);
	monitoring(philo, FORK);
	sem_wait(philo->args->forks);
	monitoring(philo, FORK);
}

static void	drop_forks(t_philo *philo)
{
	monitoring(philo, DROP);
	monitoring(philo, DROP);
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
}

/* Encapsulates the eat philosopher action. Picks 2 forks from the middle
of the table, sleeps time_to_eat miliseconds, drops 2 forks on the table
and prints its respective monitoring messages */
static void	eat(t_philo *philo)
{
	pick_forks(philo);
	philo->can_die = false;
	monitoring(philo, EAT);
	philo->last_meal_time = get_time();
	usleep(philo->args->time_to_eat * MICROSEC);
	drop_forks(philo);
	philo->eaten_meals += 1;
	philo->can_die = true;
}

static void	_sleep(t_philo *philo)
{
	monitoring(philo, SLEEP);
	usleep(philo->args->time_to_sleep * MICROSEC);
}

void	routine(t_philo *philo)
{
	while (ALL_ALIVE)
	{
		eat(philo);
		_sleep(philo);
		monitoring(philo, THINK);
	}
}
