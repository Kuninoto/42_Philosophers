/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:35:17 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/18 23:55:25 by nnuno-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <memory.h> // memset()
# include <stdio.h> // printf()
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // write(), usleep()
# include <sys/types.h> // fork()
# include <sys/time.h> // gettimeofday()
# include <sys/wait.h> // waitpid()
# include <pthread.h> // POSIX thread API, pthread_* functions
# include <stdbool.h> // boolean data type
# include <fcntl.h> // O_* constants
# include <sys/stat.h> // mode constants
# include <semaphore.h> // POSIX semaphore API, sem_* functions
# include <signal.h> // kill(), SIG* constants

/* CONSTANTS */

# define MICROSEC 1000

/* Semaphore names */

# define SEM_FORKS "/forks"
# define SEM_MEAL "/meal"
# define SEM_PRINT "/print"
# define SEM_LOCK_DEATH "/lock_death"

/* Error Messages */

# define SEMOPEN_ERR "Failed to open a semaphore"
# define FORK_ERR "Failed to fork()"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"

typedef struct s_args {
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_times;
	sem_t				*sem_forks;
	sem_t				*sem_meal;
	sem_t				*sem_print;
	pthread_t			eats_checker_tid;
}				t_args;

typedef struct s_philo {
	int					philo_nbr;
	pid_t				pid;
	suseconds_t			last_meal_time;
	suseconds_t			start_time;
	sem_t				*sem_lock_death;
	t_args				*args;
}				t_philo;

typedef enum e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
	DROP,
}				t_event_id;

// INPUT ------------------------------------

/* Checks if argc == 5 || 6 and if 
all arguments provided are digits */
void			validate_args(int argc, char **argv);

/* Custom atoi() implementation. Exits the program on failure if the result 
would overflow an integer or if it would be negative */
int				ft_atoi(char *str);

/* 	Initializes and fills a t_args structure */
t_args			init_args(char **argv);

// PHILOSOPHERS -------------------------

/* Initializes philosophers array */
t_philo			*init_philos(t_args *args);

/* Creates Philosophers and supervisor processes */
void			create_processes(t_args *args, t_philo *philos);

void			create_eats_checker(t_args *args, t_philo *philos);

/* Philosophers' routine: eat, sleep, think */
void			routine(t_philo *philo);

/* Prints Philosophers' activity logs */
void			monitoring(t_philo *philo, t_event_id event);

// UTILS --------------------------

/* Encapsulates the gettimeofday() procedure and 
returns only the suseconds_t from it */
suseconds_t		get_time(void);

/* Prints Error: <error_msg>\n to STDERR 
and exits the program on failure */
void			panic(char *error_msg);

/* Kills all philosopher processes */
void			end_processes(t_philo *philos);

/* Checks if a philosopher starved 
(current time - last time philosopher had a meal)
and checks if that is bigger than the time a philosopher
can pass without eating */
static inline bool	starved(t_philo *philo)
{
	return (((get_time() - philo->last_meal_time)
			>= philo->args->time_to_die));
}

/* Frees args and philosophers array */
void			destroy(t_args *args, t_philo *philo_array);

static inline bool	isdigit_or_signal(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c == '+' || c == '-'))
		return (true);
	return (false);
}

static inline bool	is_spaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

#endif
