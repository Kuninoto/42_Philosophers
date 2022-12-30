/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/30 16:30:21 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

#define DEAD_EMOJI "😵"
#define EAT_EMOJI "😋"
#define THINK_EMOJI "🤔"
#define SLEEP_EMOJI "😴"

void	monitoring(t_event_id event)
{
	printf("\nAt: %d\n"
		   "Philosopher: %d\n" 
		   "Action: ", 
			10, 1);
	if (event == DEAD)
		printf("Died %s\n", DEAD_EMOJI);
	else if (event == EAT)
		printf("Eating %s\n", EAT_EMOJI);
	else if (event == THINK)
		printf("Thinking %s\n", THINK_EMOJI);
	else if (event == SLEEP)
		printf("A mimir %s\n", SLEEP_EMOJI);
}
