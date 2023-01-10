/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:54:46 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/10 20:15:32 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
}

void	eat(t_philo *philo)
{
	pick_forks(philo);
	philo->can_die = false;
	monitoring(philo, EAT);
	usleep(philo->args->time_to_eat * to_microsec);
	philo->last_meal_time = get_time();
	drop_forks(philo);
	philo->eaten_meals += 1;
}
