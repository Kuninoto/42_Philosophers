/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/05 21:59:35 by nnuno-ca         ###   ########.fr       */
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

typedef struct s_args {
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
}				t_args;

static inline t_args	init_args(void)
{
	return ((t_args){
		.nbr_of_philo = 0,
		.time_to_die = 0,
		.time_to_eat = 0,
		.time_to_sleep = 0,
		.must_eat_times = -1,
	});
}

typedef struct s_philo {
	int					philo_nbr;
	pthread_t			t_id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	suseconds_t			start_time;
	bool				has_anyone_died;
	int					eat_counter;
}				t_philo;

static inline t_philo	init_philo(t_args *args, int philo_nbr)
{
	return ((t_philo){
		.philo_nbr = philo_nbr,
		.time_to_die = args->time_to_die,
		.time_to_eat = args->time_to_eat,
		.time_to_sleep = args->time_to_sleep,
		.has_anyone_died = false,
		.eat_counter = 0,
	});
}

/* Thread parameters */
typedef struct s_data {
	t_philo			*current_philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_data;

static inline t_data	init_routine_args(t_philo *current_philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	return ((t_data){
		.current_philo = current_philo,
		.left_fork = left_fork,
		.right_fork = right_fork,
	});
}

// INPUT ------------------------------------

/* Checks if all arguments provided are digits */
void		validate_args(int argc, char **argv);

/* Atoi reimplementation. Exits the program on failure if the result 
	would overflow an integer, if it would be negative or 0 */
int			long_atoi(char *str);

static inline void	fill_args(t_args *args, char **argv)
{
	args->nbr_of_philo = long_atoi(argv[1]);
	args->time_to_die = long_atoi(argv[2]);
	args->time_to_eat = long_atoi(argv[3]);
	args->time_to_sleep = long_atoi(argv[4]);
	if (argv[5])
		args->must_eat_times = long_atoi(argv[5]);
}

typedef enum e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
}				t_event_id;


// PHILOSOPHER ACTIONS -------------------------

/* Simulates the eat philosopher action. Locks, sleeps
time_to_eat miliseconds, unlocks left and right fork (mutex)
and prints its respective monitoring messages */
void	eat(t_data *args);

/* Prints Philosophers' activity logs */
void	monitoring(t_data *args, t_event_id event);

// UTILS --------------------------

/* Encapsulates the gettimeofday() procedure and 
returns only the suseconds_t from it */
suseconds_t	get_time(void);

/* Prints Error: error_msg, followed by a newline,
to STDERR and exits the program on failure */
void		on_error(char *error_msg);

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