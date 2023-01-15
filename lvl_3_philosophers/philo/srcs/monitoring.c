/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 15:24:21 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

#define TAKE_FORK_STR "has taken a fork 🍴\n"
#define DROP_FORK_STR "has dropped a fork 🍴\n"
#define EAT_STR "is eating 😋\n"
#define THINK_STR "is thinking 🤔\n"
#define SLEEP_STR "is sleeping 😴\n"
#define DEAD_STR "is dead 😵\n"

void	monitoring(t_philo *philo, t_event_id event)
{
	suseconds_t	timestamp;
	const char	*events[6] = {DEAD_STR, EAT_STR, THINK_STR,
		SLEEP_STR, TAKE_FORK_STR, DROP_FORK_STR};

	timestamp = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->args->monitoring_mutex);
	printf("%ld %d %s", timestamp, philo->philo_nbr, events[event]);
	pthread_mutex_unlock(&philo->args->monitoring_mutex);
}
