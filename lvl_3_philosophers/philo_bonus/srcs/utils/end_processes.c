/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:18:44 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:18:56 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers_bonus.h"

void	end_processes(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->args->nbr_of_philo)
		kill(philos[i++].pid, SIGTERM);
}