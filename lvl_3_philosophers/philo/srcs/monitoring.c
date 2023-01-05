/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 21:14:48 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

#define DEAD_EMOJI "😵"
#define EAT_EMOJI "😋"
#define THINK_EMOJI "🤔"
#define SLEEP_EMOJI "😴"
#define FORK_EMOJI "🍴"

void	monitoring(t_data *args, t_event_id event)
{
	size_t	timestamp;
	int		philo_nbr;

	timestamp = get_time() - args->current_philo->start_time;
	philo_nbr = args->current_philo->philo_nbr;
	printf("%02ld %d ", timestamp, philo_nbr);
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
}
