/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/14 17:12:24 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <memory.h> // memset()
# include <stdio.h> // printf()
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // write(), usleep()
# include <sys/time.h> // gettimeofday()
# include <pthread.h> // POSIX thread API
# include <stdbool.h> // boolean data type

# define TO_MICROSEC 1000

typedef struct s_args {
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_times;
	bool				is_anyone_dead;
	pthread_mutex_t		monitoring_mutex;
}				t_args;

typedef struct s_philo {
	int					philo_nbr;
	int					eaten_meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	suseconds_t			last_meal_time;
	pthread_t			t_id;
	suseconds_t			start_time;
	bool				can_die;
	t_args				*args;
}				t_philo;

typedef enum e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
}				t_event_id;

// FORK UTILS ------------------------------

// Init forks (mutexes)
pthread_mutex_t	*init_forks(t_args *args);

// Destroys all forks & monitoring_mutex
void			destroy_mutexes(t_args *args, pthread_mutex_t *forks,
					t_philo *philos);

// INPUT ------------------------------------

/* Checks if argc == 5 || 6 and if 
all arguments provided are digits */
void			validate_args(int argc, char **argv);

/* Atoi reimplementation. Exits the program on failure if the result 
would overflow an integer, if it would be negative or 0 */
int				long_atoi(char *str);

/* 	Initializes and fills a t_args structure */
t_args			init_fill_args(char **argv);

// PHILOSOPHERS -------------------------

/* Initializes philosophers array */
t_philo			*init_philos(t_args *args, pthread_mutex_t *forks_array);

/* Creates Philosophers and supervisor threads */
void			create_threads(t_args *args, t_philo *philos);

/* Philosophers' routine: eat, sleep, think */
void			*routine(void *routine_args);

/* Prints Philosophers' activity logs */
void			monitoring(t_philo *philo, t_event_id event);

// UTILS --------------------------

/* Encapsulates the gettimeofday() procedure and 
returns only the suseconds_t from it */
suseconds_t		get_time(void);

/* Prints Error: <error_msg>\n to STDERR 
and exits the program on failure */
void			panic(char *error_msg);

/* Checks if c is a character that represents a digit or a signal */
static inline bool	isdigit_or_signal(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c == '+' || c == '-'))
		return (true);
	else
		return (false);
}

#endif