/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:36:24 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:12:31 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

void	destroy(t_args *args, t_philo *philo_array)
{
	sem_close(args->sem_forks);
	sem_close(args->sem_meal);
	sem_close(args->sem_print);
	free(philo_array);
	philo_array = NULL;
}
