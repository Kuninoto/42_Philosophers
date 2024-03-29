/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:01:26 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/19 00:11:14 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

int	panic(t_args *args, pthread_mutex_t *forks,
		t_philo *philos, char *error_msg)
{
	destroy(args, forks, philos);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
