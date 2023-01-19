/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:34:37 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/19 00:01:42 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	*eats_checker(void *philos)
{
	t_philo	*casted;
	int		satisfied_philos;
	int		i;

	casted = (t_philo *)philos;
	satisfied_philos = 0;
	while (satisfied_philos < casted->args->nbr_of_philo)
	{
		i = 0;
		while (i < casted->args->nbr_of_philo)
		{
			sem_wait(casted->args->sem_meal);
			i += 1;
		}
		satisfied_philos += 1;
	}
	printf("Every Philosopher ate %d meals!\n",
					casted->args->must_eat_times);
	sem_wait(casted->args->sem_print);
	end_processes(philos);
	return (NULL);
}

void	create_eats_checker(t_args *args, t_philo *philos)
{
	if (pthread_create(&args->eats_checker_tid, NULL, eats_checker, (void *)philos) != 0)
		destroy(args, philos);
	pthread_detach(args->eats_checker_tid);
}
