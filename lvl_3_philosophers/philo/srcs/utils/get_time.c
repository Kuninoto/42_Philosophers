/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:31:08 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 17:37:22 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

suseconds_t	get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_usec);
}