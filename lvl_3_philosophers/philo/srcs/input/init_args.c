/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:38:04 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/10 19:40:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

t_args	init_args(void)
{
	t_args	args;
	
	args.nbr_of_philo = 0,
	args.time_to_die = 0,
	args.time_to_eat = 0,
	args.time_to_sleep = 0,
	args.must_eat_times = -1,
	args.is_anyone_dead = false,
	pthread_mutex_init(&args.monitoring_mutex, NULL);
	return (args);
}