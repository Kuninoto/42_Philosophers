/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 18:47:51 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

// t_id stands for thread identifier (id).

int counter;

void	*routine(void *mutex)
{
//	pthread_mutex_lock(&mutex);

	(void)mutex;
	
//	unsigned long i = 0;
    counter++;
//  printf("\n Job %d has started\n", counter);
  
   /*  for (i = 0; i < (0xFFFFFFFF); i++)
        ; */
    printf("\n Job %d has finished\n", counter);
//	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	create_threads(t_args *args, pthread_t *t_ids)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_create(&t_ids[i++], NULL, routine, NULL) != 0)
		{
			free(t_ids);
			on_error("Failed to create a thread");
		}
	}
}

void	join_threads(t_args *args, pthread_t *t_ids)
{
	int i;

	i = 0;
	while (i < args->nbr_of_philo)
	{
		if (pthread_join(t_ids[i++], NULL) != 0)
		{
			free(t_ids);
			on_error("Failed to join a thread");
		}
	}
}

int main(int argc, char **argv)
{
	validate_args(argc, argv);
	t_args args;
	args = init_args();
	fill_args(&args, argv);
	
/* 	pthread_mutex_t shared_fork;
	if (pthread_mutex_init(&shared_fork, NULL) != 0)
        on_error("Mutex init has failed"); */

	pthread_t *t_ids;
	t_ids = malloc(args.nbr_of_philo * sizeof(pthread_t));
	create_threads(&args, t_ids);

	// equivalent wait() for threads
	join_threads(&args, t_ids);

	monitoring(&args, DEAD);

	return (EXIT_SUCCESS);	
}

/* 	printf("%d\n", args.nbr_of_philo);
	printf("%d\n", args.time_to_die);
	printf("%d\n", args.time_to_eat);
	printf("%d\n", args.time_to_sleep);
	if (args.nbr_of_times_each_philo_must_eat)
		printf("%d\n", args.nbr_of_times_each_philo_must_eat); */