/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 20:04:14 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

static void	pick_forks(t_philo *philo)
{
	sem_wait(&philo->args->forks);
	sem_wait(&philo->args->forks);
	monitoring(philo, FORK);
	monitoring(philo, FORK);
}

static void	drop_forks(t_philo *philo)
{
	sem_post(&philo->args->forks);
	sem_post(&philo->args->forks);
	monitoring(philo, DROP);
	monitoring(philo, DROP);
}

/* Encapsulates the eat philosopher action. Picks 2 forks from the table, 
sleeps time_to_eat miliseconds, drops 2 forks on the table and prints 
its respective monitoring messages */
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

void	*routine(t_philo *philo)
{
	while (true)
	{
		eat(philo);
		monitoring(philo, SLEEP);
		usleep(philo->args->time_to_sleep * TO_MICROSEC);
		monitoring(philo, THINK);
		philo->can_die = true;
	}
	return (NULL);
}