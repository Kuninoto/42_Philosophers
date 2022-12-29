/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2022/12/29 18:41:11 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <memory.h> // memset()
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()
#include <unistd.h> // write(), usleep()
#include <sys/time.h> // gettimeofday()
#include <pthread.h> // POSIX thread API
#include <stdbool.h>

typedef struct	s_args {
	int nbr_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nbr_of_times_each_philo_must_eat;
}				t_args;

static inline t_args init_args(void) {
	return ((t_args){
		.nbr_of_philo = 0,
		.time_to_die = 0,
		.time_to_eat = 0,
		.time_to_sleep = 0,
		.nbr_of_times_each_philo_must_eat = 0,
	});
}

// INPUT ------------------------------------

/* Checks if all arguments provided are digits */
void	validate_args(int argc, char **argv);

/* Atoi reimplementation, exits on failure if the result 
   would overflow an integer or if it would be negative */
int	long_atoi(char *str);

static inline void	fill_args(t_args *args, char **argv)
{
	args->nbr_of_philo = long_atoi(argv[1]);
	args->time_to_die = long_atoi(argv[2]);
	args->time_to_eat = long_atoi(argv[3]);
	args->time_to_sleep = long_atoi(argv[4]);
	if (argv[5])
		args->nbr_of_times_each_philo_must_eat = long_atoi(argv[5]);
}

typedef enum	e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
}				t_event_id;

// Prints activity logs
void	monitoring(t_args *args, t_event_id event);

// UTILS --------------------------

/* Prints Error: error_msg, followed by a newline
to STDERR and exits the program on failure */
void	on_error(char *error_msg);

/* Checks if c is a character that represents a digit */
static inline bool	isdigit_or_signal(char c) { 
	if ((c >= '0' && c <= '9')
	|| (c == '+' || c == '-'))
		return (true); 
	else 
		return (false); 
};

#endif