/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 15:48:13 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	*routine(void *param)
{
	(void)param;

	int sum = 2;
	for (int i = 2; i < 10; i++)
	{
		usleep(1000);
		sum *= sum;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	validate_args(argc, argv);
	t_args args = init_args();
	fill_args(&args, argv);

	printf("%d\n", args.nbr_of_philo);
	printf("%d\n", args.time_to_die);
	printf("%d\n", args.time_to_eat);
	printf("%d\n", args.time_to_sleep);
	if (args.nbr_of_times_each_philo_must_eat)
		printf("%d\n", args.nbr_of_times_each_philo_must_eat);






	/* pthread_t t1_id;
	pthread_t t2_id;

	if (pthread_create(&t1_id, NULL, routine, NULL) != 0)
		on_error("Failed to create thread 1");
	if (pthread_create(&t2_id, NULL, routine, NULL) != 0)
		on_error("Failed to create thread 2");

	// equivalent wait() for threads
	pthread_join(t1_id, NULL);
	pthread_join(t2_id, NULL); */

	return (EXIT_SUCCESS);	
}
