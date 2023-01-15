/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:36:24 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/15 16:39:09 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

void	destroy(t_args *args, t_philo *philo_array)
{
	sem_close(args->forks);
	sem_close(args->print_sem);
	free(philo_array);
	philo_array = NULL;
}
