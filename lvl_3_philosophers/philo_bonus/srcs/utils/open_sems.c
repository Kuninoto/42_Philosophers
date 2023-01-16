/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_sems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:14:21 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/16 19:22:08 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

void	open_sems(t_args *args)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	args->forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, args->nbr_of_philo);
	if (args->forks == SEM_FAILED)
		panic("Failed to open forks semaphore");
	args->print_sem = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	if (args->print_sem == SEM_FAILED)
	{
		sem_close(args->forks);
		panic("Failed to open print semaphore");
	}
}
