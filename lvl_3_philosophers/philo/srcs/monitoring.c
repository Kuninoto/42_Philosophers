/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/10 19:46:39 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

#define DEAD_EMOJI "😵"
#define EAT_EMOJI "😋"
#define THINK_EMOJI "🤔"
#define SLEEP_EMOJI "😴"
#define FORK_EMOJI "🍴"

void	monitoring(t_philo *philo, t_event_id event)
{
	suseconds_t	timestamp;

	timestamp = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->args->monitoring_mutex);
	printf("%ld %d ", timestamp, philo->philo_nbr);
	if (event == FORK)
		printf("has taken a fork %s\n", FORK_EMOJI);
	else if (event == EAT)
		printf("is eating %s\n", EAT_EMOJI);
	else if (event == SLEEP)
		printf("is sleeping %s\n", SLEEP_EMOJI);
	else if (event == THINK)
		printf("is thinking %s\n", THINK_EMOJI);
	else if (event == DEAD)
		printf("died %s\n", DEAD_EMOJI);
	pthread_mutex_unlock(&philo->args->monitoring_mutex);
}
