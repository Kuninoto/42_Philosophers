/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/02 19:01:59 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

#define debug printf("debug\n")
#define debug_args printf("%d\n", args.nbr_of_philo); printf("%d\n", args.time_to_die); printf("%d\n", args.time_to_eat); printf("%d\n", args.time_to_sleep); if (args.nbr_of_times_each_philo_must_eat) printf("%d\n", args.nbr_of_times_each_philo_must_eat);

// t_id stands for thread identifier (id).

void	*routine(void *routine_args)
{
	t_routine_args *casted;
	int				philo_nbr;

	casted = (t_routine_args *)routine_args;
	philo_nbr = casted->philo_num + 1;

	if (philo_nbr == casted->nbr_of_philo) 
	{
		pthread_mutex_lock(casted->right_fork);
		printf("Philosopher %d picked up his right fork.\n", philo_nbr);
		pthread_mutex_lock(casted->left_fork);
		printf("Philosopher %d picked up his left fork and started eating.\n", philo_nbr);
	}
	else
	{
		pthread_mutex_lock(casted->left_fork);
		printf("Philosopher %d picked up his left fork.\n", philo_nbr);
		pthread_mutex_lock(casted->right_fork);
		printf("Philosopher %d picked up his right fork and started eating.\n", philo_nbr);
	}
	usleep(3);
	pthread_mutex_unlock(casted->left_fork);
	pthread_mutex_unlock(casted->right_fork);
	return (NULL);
}

void	create_threads(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int i;
	t_routine_args routine_args;

	i = 0;
	while (i < (args->nbr_of_philo - 1))
	{
		routine_args = init_routine_args(args, &forks[i], &forks[(i - 1) % args->nbr_of_philo], i);
		if (pthread_create(&philos[i].t_id, NULL, routine, (void *)&routine_args) != 0)
		{
			free(philos);
			on_error("Failed to create a thread");
		}
		if (pthread_detach(philos[i].t_id) != 0)
		{
			free(philos);
			on_error("Failed to detach a thread");
		}
		//printf("philos[%d].t_id = %lu\n", i, philos[i].t_id);
		i++;
	}
}

t_philo	*init_philos(t_args *args)
{
	t_philo *philos;
	int		i;
	
	philos = malloc(args->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		on_error("Failed to allocate memory for philosophers array");
	i = 0;
	while (i < args->nbr_of_philo)
		philos[i++] = init_philo(args);
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
		i++;
	}
	return (forks);
}

void	destroy_forks(t_args *args, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
		pthread_mutex_destroy(&forks[i++]);
}

int main(int argc, char **argv)
{
	validate_args(argc, argv);
	t_args args;
	args = init_args();
	fill_args(&args, argv);
	
	t_philo *philos;
	philos = init_philos(&args);

	pthread_mutex_t *forks;
	forks = init_forks(&args);

	create_threads(&args, philos, forks);

	pthread_exit(0);
	monitoring(SLEEP);
	destroy_forks(&args, forks);
	free(philos);
	
	return (EXIT_SUCCESS);
}

/* 	printf("%d\n", args.nbr_of_philo);
	printf("%d\n", args.time_to_die);
	printf("%d\n", args.time_to_eat);
	printf("%d\n", args.time_to_sleep);
	if (args.nbr_of_times_each_philo_must_eat)
		printf("%d\n", args.nbr_of_times_each_philo_must_eat); */