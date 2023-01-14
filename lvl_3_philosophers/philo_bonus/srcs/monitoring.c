/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 22:29:34 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

#define DEAD_EMOJI "😵"
#define EAT_EMOJI "😋"
#define THINK_EMOJI "🤔"
#define SLEEP_EMOJI "😴"
#define FORK_EMOJI "🍴"

void	monitoring(t_philo *philo, t_event_id event)
{
	suseconds_t	timestamp;

	sem_wait(&philo->args->monitoring_sem);
	timestamp = get_time() - philo->start_time;
	printf("%ld %d ", timestamp, philo->philo_nbr);
	if (event == FORK)
		printf("has taken a fork %s\n", FORK_EMOJI);
	else if (event == DROP)
		printf("has dropped a fork %s\n", FORK_EMOJI);
	else if (event == EAT)
		printf("is eating %s\n", EAT_EMOJI);
	else if (event == SLEEP)
		printf("is sleeping %s\n", SLEEP_EMOJI);
	else if (event == THINK)
		printf("is thinking %s\n", THINK_EMOJI);
	else if (event == DEAD)
		printf("died %s\n", DEAD_EMOJI);
	sem_post(&philo->args->monitoring_sem);
}
