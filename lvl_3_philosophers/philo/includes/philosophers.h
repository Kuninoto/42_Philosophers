/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/04 23:36:28 by nnuno-ca         ###   ########.fr       */
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
#include <stdbool.h> // boolean data type

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
		.nbr_of_times_each_philo_must_eat = -1,
	});
}

typedef struct	s_philo {
	pthread_t			t_id;
	int					fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}				t_philo;

static inline t_philo init_philo(t_args *args) {
	return ((t_philo){
		.t_id = 0,
		.fork = 1,
		.time_to_die = args->time_to_die,
		.time_to_eat = args->time_to_eat,
		.time_to_sleep = args->time_to_sleep,
	});
}

typedef struct s_routine_args {
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_routine_args;

static inline t_routine_args init_routine_args(t_args *args, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int philo_num) {
	return ((t_routine_args){
		.nbr_of_philo = args->nbr_of_philo,
		.time_to_die = args->time_to_die,
		.time_to_eat = args->time_to_eat,
		.time_to_sleep = args->time_to_sleep,
		.philo_num = philo_num,
		.left_fork = left_fork,
		.right_fork = right_fork,
	});
}

// INPUT ------------------------------------

/* Checks if all arguments provided are digits */
void	validate_args(int argc, char **argv);

/* Atoi reimplementation. Exits the program on failure if the result 
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

// Prints Philosophers' activity logs
void	monitoring(t_event_id event);

// UTILS --------------------------

/* Prints Error: error_msg, followed by a newline,
to STDERR and exits the program on failure */
void	on_error(char *error_msg);

/* Checks if c is a character that represents a digit or a signal */
static inline bool	isdigit_or_signal(char c) { 
	if ((c >= '0' && c <= '9')
	|| (c == '+' || c == '-'))
		return (true);
	else
		return (false);
};

#endif