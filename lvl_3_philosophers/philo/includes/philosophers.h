/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/12 18:53:08 by nnuno-ca         ###   ########.fr       */
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

#define to_microsec 1000

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

// Destroys all forks (mutexes)
void	destroy_forks(t_args *args, pthread_mutex_t *forks);

// INPUT ------------------------------------

/* Checks if all arguments provided are digits */
void		validate_args(int argc, char **argv);

/* Atoi reimplementation. Exits the program on failure if the result 
	would overflow an integer, if it would be negative or 0 */
int			long_atoi(char *str);

static inline t_args	init_fill_args(char **argv)
{
	t_args	args;

	args.nbr_of_philo = long_atoi(argv[1]);
	args.time_to_die = long_atoi(argv[2]);
	args.time_to_eat = long_atoi(argv[3]);
	args.time_to_sleep = long_atoi(argv[4]);
	if (argv[5])
		args.must_eat_times = long_atoi(argv[5]);
	else
		args.must_eat_times = -1;
	args.is_anyone_dead = false;
	pthread_mutex_init(&args.monitoring_mutex, NULL);
	return (args);
}

// PHILOSOPHER ACTIONS -------------------------

/* Simulates the eat philosopher action. Locks, sleeps
time_to_eat miliseconds, unlocks left and right fork (mutex)
and prints its respective monitoring messages */
void	eat(t_philo *philo);

/* Prints Philosophers' activity logs */
void	monitoring(t_philo *philo, t_event_id event);

// UTILS --------------------------

/* Encapsulates the gettimeofday() procedure and 
returns only the suseconds_t from it */
suseconds_t	get_time(void);

/* Prints Error: <error_msg>\n to STDERR 
and exits the program on failure */
void	panic(char *error_msg);

/* Checks if c is a character that represents a digit or a signal */
static inline bool	isdigit_or_signal(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c == '+' || c == '-'))
		return (true);
	else
		return (false);
};

#endif