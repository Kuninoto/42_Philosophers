/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 17:46:51 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

#define debug printf("debug\n")
#define debug_args printf("%d\n", args.nbr_of_philo); printf("%d\n", args.time_to_die); printf("%d\n", args.time_to_eat); printf("%d\n", args.time_to_sleep); if (args.nbr_of_times_each_philo_must_eat) printf("%d\n", args.nbr_of_times_each_philo_must_eat);

// t_id stands for thread identifier (id).

void	*routine(void *routine_args)
{
	t_routine_args *casted;

	casted = (t_routine_args *)routine_args;

	pthread_mutex_lock(casted->left_fork);
	monitoring(casted->current_philo->start_time, casted->current_philo->philo_nbr, _FORK);

	pthread_mutex_lock(casted->right_fork);
	monitoring(casted->current_philo->start_time, casted->current_philo->philo_nbr, _FORK);

	monitoring(casted->current_philo->start_time, casted->current_philo->philo_nbr, EAT);
	usleep(casted->current_philo->time_to_eat);

	pthread_mutex_unlock(casted->left_fork);
	pthread_mutex_unlock(casted->right_fork);
 	usleep(casted->current_philo->time_to_sleep);
	usleep(casted->current_philo->time_to_die);
	return (NULL);
}

void	create_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int 			i;
	t_routine_args	routine_args;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		routine_args = init_routine_args(&philos[i], &forks[i], &forks[(i + 1) % args->nbr_of_philo]);
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL, routine, (void *)&routine_args) != 0)
		{
			free(philos);
			on_error("Failed to create a thread");
		}
		i++;
	}
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_join(philos[i++].t_id, NULL) != 0)
		{
			free(philos);
			on_error("Failed to detach a thread");
		}
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo *philos;
	int		i;
	
	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		on_error("Failed to allocate memory for the philosophers array");
	i = 0;
	while (i < args->nbr_of_philo)
	{
		philos[i] = init_philo(args, (i + 1));
		i += 1;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t *forks;
	int i;

	forks = malloc(args->nbr_of_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
        	on_error("Mutex init has failed");
		i += 1;
	}
	return (forks);
}

void	destroy_forks(t_args *args, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
		pthread_mutex_destroy(&forks[i += 1]);
	free(forks);
}

int main(int argc, char **argv)
{
	validate_args(argc, argv);
	t_args args;
	args = init_args();
	fill_args(&args, argv);
	
	t_philo *philos;
	pthread_mutex_t *forks;

	philos = init_philos(&args);
	forks = init_forks(&args);

	create_threads(&args, philos, forks);


	pthread_exit(0);

	destroy_forks(&args, forks);
	free(philos);	
	return (EXIT_SUCCESS);
}
