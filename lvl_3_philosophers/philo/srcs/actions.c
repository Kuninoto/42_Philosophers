/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:54:46 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 21:07:47 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	pick_forks(t_data *args)
{
	pthread_mutex_lock(args->left_fork);
	pthread_mutex_lock(args->right_fork);
	monitoring(args, FORK);
	monitoring(args, FORK);
}

static void	drop_forks(t_data *args)
{
	pthread_mutex_unlock(args->left_fork);
	pthread_mutex_unlock(args->right_fork);
	monitoring(args, SLEEP);
	usleep(args->current_philo->time_to_sleep);
}

void	eat(t_data *args)
{
	pick_forks(args);
	monitoring(args, EAT);
	usleep(args->current_philo->time_to_eat);
	drop_forks(args);
	args->current_philo->eat_counter += 1;
}
