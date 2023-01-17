/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/17 21:10:03 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers_bonus.h"

/* Kills all philosophers processes */
void	end_processes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->args->nbr_of_philo)
	{
		kill(philos[i].pid, SIGTERM);
		i += 1;
	}
}

void	*death_checker(void *philos)
{
	t_philo	*casted;

	casted = (t_philo *)philos;
	sem_wait(casted->args->someone_died_sem);
	if (casted->args->end == true)
		return (NULL);
	casted->args->end = true;
	sem_post(casted->args->eaten_sem);
	end_processes(casted);
	return (NULL);
}

void	*eats_checker(void *philos)
{
	t_philo	*casted;
	int		i;

	casted = (t_philo *)philos;
	i = 0;
	while (i < casted->args->nbr_of_philo)
	{
		sem_wait(casted->args->eaten_sem);
		if (casted->args->end == true)
			return (NULL);
		i += 1;
	}
	casted->args->end = true;
	sem_post(casted->args->someone_died_sem);
	printf("Every Philosopher ate %d meals!\n",
					casted->args->must_eat_times);
	end_processes(casted);
	return (NULL);
}

/* Creates death and eats checker threads and makes main join them */
void	create_checkers(t_args *args, t_philo *philos)
{
	if (pthread_create(&args->death_checker_tid, NULL, death_checker, (void *)philos) != 0)
		destroy(args, philos);
	pthread_join(args->death_checker_tid, NULL);
	if (pthread_create(&args->eats_checker_tid, NULL, eats_checker, (void *)philos) != 0)
		destroy(args, philos);
	pthread_join(args->eats_checker_tid, NULL);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philos;

	validate_args(argc, argv);
	args = init_args(argv);
	philos = init_philos(&args);
	create_processes(&args, philos);
	create_checkers(&args, philos);
	destroy(&args, philos);
	return (EXIT_SUCCESS);
}
