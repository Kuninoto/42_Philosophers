/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:06:35 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 19:58:33 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

/* Process that watches the philosophers activity */
void	*supervisor(t_philo *philos)
{
	int		satisfied_philos;
	int		i;

	satisfied_philos = 0;
	while (satisfied_philos != philos->args->nbr_of_philo)
	{
		i = 0;
		while (i < philos->args->nbr_of_philo)
		{
			if (((get_time() - philos[i].last_meal_time)
					>= philos->args->time_to_die && philos[i].can_die))
			{
				monitoring(philos, DEAD);
				return (NULL);
			}
			if (philos[i].eaten_meals == philos->args->must_eat_times)
				satisfied_philos += 1;
			i += 1;
		}
	}
	printf("Every Philosopher had %d meals!\n", philos->args->must_eat_times);
	return (NULL);
}

/* Creates supervisor process and makes main process wait for its pid */
void	create_supervisor(t_args *args, t_philo *philos)
{
	pid_t		supervisor_pid;

	supervisor_pid = fork();
	if (supervisor_pid == -1)
	{
		destroy(args, philos);
		panic(FORK_ERROR);
	}
	if (supervisor_pid == 0)
	{
		supervisor(philos);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(supervisor_pid, NULL, 0);
}

void	create_processes(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			destroy(args, philos);
			panic(FORK_ERROR);
		}
		// Child process
		if (philos[i].pid == 0)
			routine(&philos[i]);
		i += 1;
	}
	create_supervisor(args, philos);
}
