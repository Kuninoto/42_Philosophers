/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 21:49:04 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

#define debug printf("debug\n")
#define debug_args printf("%d\n", args.nbr_of_philo); printf("%d\n", args.time_to_die); printf("%d\n", args.time_to_eat); printf("%d\n", args.time_to_sleep); if (args.nbr_of_times_each_philo_must_eat) printf("%d\n", args.nbr_of_times_each_philo_must_eat);

#define	ALL_ALIVE 1

// t_id stands for thread identifier (id).

void	*routine(void *routine_args)
{
	t_data	*casted;

	casted = (t_data *)routine_args;
 	monitoring(casted, THINK);	
	eat(routine_args);
	usleep(casted->current_philo->time_to_die);
	return (NULL);
}

void	create_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int 	i;
	t_data	data;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		data = init_routine_args(&philos[i], &forks[i], &forks[(i + 1) % args->nbr_of_philo]);
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].t_id, NULL, routine, (void *)&data) != 0)
		{
			free(philos);
			panic("Failed to create a thread");
		}
		if (pthread_join(philos[i++].t_id, NULL) != 0)
		{
			free(philos);
			panic("Failed to detach a thread");
		}
		i += 1;
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo *philos;
	int		i;
	
	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		panic("Failed to allocate memory for the philosophers array");
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
        		panic("Mutex init has failed");
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

int	main(int argc, char **argv)
{
	validate_args(argc, argv);

	t_args 			args;
	t_philo 		*philos;
	pthread_mutex_t *forks;
	args = init_args();
	fill_args(&args, argv);
	philos = init_philos(&args);
	forks = init_forks(&args);
	create_threads(&args, philos, forks);
	pthread_exit(0);

	destroy_forks(&args, forks);
	free(philos);	
	return (EXIT_SUCCESS);
}
