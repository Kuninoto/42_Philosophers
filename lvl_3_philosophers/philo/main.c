/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:40:22 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:38:37 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (!validate_args(argc, argv) || !init_args(&args, argv))
		return (EXIT_FAILURE);
	forks = init_forks(&args);
	philos = init_philos(&args, forks);
	if (!create_threads(&args, philos, forks))
		return (EXIT_FAILURE);
	destroy(&args, forks, philos);
	return (EXIT_SUCCESS);
}
