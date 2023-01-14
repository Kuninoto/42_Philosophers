/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 16:53:53 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

// t_id stands for thread identifier (id).

void	*routine(void *routine_args)
{
	t_philo	*casted;

	casted = (t_philo *)routine_args;
	while (!casted->args->is_anyone_dead)
	{
		eat(routine_args);
		monitoring(casted, SLEEP);
		usleep(casted->args->time_to_sleep * TO_MICROSEC);
		monitoring(casted, THINK);
		casted->can_die = true;
	}
	return (NULL);
}

// Thread that watches the philosophers activity
void	*supervisor(void *philos)
{
	t_philo	*casted;
	int		satisfied_philos;
	int		i;

	casted = (t_philo *)philos;
	satisfied_philos = 0;
	while (satisfied_philos != casted->args->nbr_of_philo)
	{
		i = 0;
		while (i < casted->args->nbr_of_philo)
		{
			if (((get_time() - casted[i].last_meal_time)
					>= casted->args->time_to_die && casted[i].can_die))
			{
				monitoring(casted, DEAD);
				pthread_mutex_unlock(&casted[i].args->monitoring_mutex);
				return (NULL);
			}
			if (casted[i].eaten_meals == casted->args->must_eat_times)
				satisfied_philos += 1;
			i += 1;
		}
	}
	printf("Every Philosopher had %d meals!\n", casted->args->must_eat_times);
	return (NULL);
}

// Creates and makes main thread join supervisor thread
void	create_supervisor(void *philos)
{
	pthread_t	supervisor_id;

	pthread_create(&supervisor_id, NULL, supervisor, philos);
	pthread_join(supervisor_id, NULL);
}

void	create_threads(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL,
				routine, (void *)&philos[i]) != 0)
		{
			free(philos);
			panic("Failed to create a thread");
		}
		if (pthread_detach(philos[i].t_id) != 0)
		{
			free(philos);
			panic("Failed to detach a thread");
		}
		i += 1;
	}
	create_supervisor((void *)philos);
}

t_philo	*init_philos(t_args *args, pthread_mutex_t *forks_array)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		panic("Failed to allocate memory for the philosophers array");
	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i].philo_nbr = i + 1;
		philos[i].eaten_meals = 0;
		philos[i].left_fork = &forks_array[i];
		philos[i].right_fork = &forks_array[(i + 1) % args->nbr_of_philo];
		philos[i].last_meal_time = get_time();
		philos[i].can_die = true;
		philos[i].args = args;
		i += 1;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	validate_args(argc, argv);
	args = init_fill_args(argv);
	forks = init_forks(&args);
	philos = init_philos(&args, forks);
	create_threads(&args, philos);
	destroy_mutexes(&args, forks, philos);
	free(philos);
	return (EXIT_SUCCESS);
}
