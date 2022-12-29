/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:07:42 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 19:15:10 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

#define DEAD_EMOJI "😵"
#define EAT_EMOJI "😋"
#define THINK_EMOJI "🤔"
#define SLEEP_EMOJI "😴"

void	monitoring(t_args *args, t_event_id event)
{
	(void)args;

	event = DEAD;
	printf("At: %d\n"
		   "Philosopher: %d\n" 
		   "Action: ", 
			10, 1);
	if (event == DEAD)
		printf("%s\n", DEAD_EMOJI);
	else if (event == EAT)
		printf("%s\n", EAT_EMOJI);
	else if (event == THINK)
		printf("%s\n", THINK_EMOJI);
	else if (event == SLEEP)
		printf("%s\n", SLEEP_EMOJI);
}
