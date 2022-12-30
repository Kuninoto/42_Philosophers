/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/30 00:52:21 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

#define debug printf("debug\n")

// t_id stands for thread identifier (id).

int counter = 0;

void	*routine(void *mutex)
{
//	pthread_mutex_lock(mutex); // lock = 1

	(void)mutex;
    counter++;
 	printf("\n Thread %d has started\n", counter);
  
    for (size_t i = 0; i < (0xFFFFFFFF); i++)
        ;

    printf("\n Thread %d has finished\n", counter);
//	pthread_mutex_unlock(mutex); // lock = 0
	return ("teste");
}

void	create_n_join_threads(t_args *args, pthread_t *t_ids)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
	debug;
		if (pthread_create(&t_ids[i], NULL, routine(NULL), NULL) != 0)
		{
			free(t_ids);
			on_error("Failed to create a thread");
		}
		if (pthread_join(t_ids[i], NULL) != 0)
		{
			free(t_ids);
			on_error("Failed to join a thread");
		}
	//for (int i = 0; i < args.nbr_of_philo; i++)
		printf("t_ids[%d] = %lu\n", i, t_ids[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	validate_args(argc, argv);
	t_args args;
	args = init_args();
	fill_args(&args, argv);
	
/* 	pthread_mutex_t mutex;
	if (pthread_mutex_init(&mutex, NULL) != 0)
        on_error("Mutex init has failed"); */

/* 	pthread_t *t_ids;
	t_ids = malloc(args.nbr_of_philo * sizeof(pthread_t));
	if (!t_ids)
		on_error("Failed to allocate memory for t_ids");
	create_n_join_threads(&args, t_ids);
 */

//	pthread_mutex_destroy(&mutex);
	monitoring(&args, DEAD);
	return (EXIT_SUCCESS);	
}

/* 	printf("%d\n", args.nbr_of_philo);
	printf("%d\n", args.time_to_die);
	printf("%d\n", args.time_to_eat);
	printf("%d\n", args.time_to_sleep);
	if (args.nbr_of_times_each_philo_must_eat)
		printf("%d\n", args.nbr_of_times_each_philo_must_eat); */