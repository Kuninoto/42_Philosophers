/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:36:54 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/01/21 01:39:41 by nnuno-ca         ###   ########.fr       */
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

/* Constants */

# define MICROSEC 1000

/* Error messages */

# define INVALID_ARGS_ERR "Invalid arguments"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define MUTEX_INIT_ERR "Failed to initialize mutex"

typedef struct s_args {
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_times;
	pthread_mutex_t		monitoring_mutex;
	bool				simulation_should_end;
}				t_args;

typedef struct s_philo {
	int					philo_nbr;
	int					eaten_meals;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	suseconds_t			last_meal_time;
	pthread_t			t_id;
	suseconds_t			start_time;
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

// FORK UTILS ------------------------------

/* Init forks (mutexes) */
pthread_mutex_t		*init_forks(t_args *args);

// PHILOSOPHERS -------------------------

/* Initializes philosophers array */
t_philo				*init_philos(t_args *args, pthread_mutex_t *forks_array);

/* Creates Philosophers and supervisor threads 
Returns false if the program should exit due to an error */
bool				launch_threads_and_join(t_args *args, t_philo *philos,
						pthread_mutex_t *forks);

/* Philosophers' routine: eat, sleep, think */
void				*routine(void *_philo);

/* Prints Philosophers' activity logs */
void				monitoring(t_philo *philo, t_event_id event_id);

// INPUT ------------------------------------

/* Checks if argc == 5 || argc == 6 & if all arguments
are composed by digits or signals */
bool				valid_args(int argc, char **argv);

/* Initializes and fills a t_args structure, 
returns false if the program should exit */
bool				init_args(t_args *args, char **argv);

// UTILS --------------------------

/* Encapsulates the gettimeofday() procedure and 
returns only the suseconds_t from it */
suseconds_t			get_time(void);

/* Calls destroy() and print Error: <error_msg>\n to STDERR */
int					panic(t_args *args, pthread_mutex_t *forks,
						t_philo *philos, char *error_msg);

/* Destroys all monitoring & forks mutexes and philosophers array */
void				destroy(t_args *args, pthread_mutex_t *forks,
						t_philo *philos);

/* Checks if a philosopher starved 
(current time - last time philosopher had a meal)
and checks if that is bigger than the time a philosopher
can pass without eating */
static inline bool	starved(t_philo *philo)
{
	return (((get_time() - philo->last_meal_time)
			>= philo->args->time_to_die));
}

int					ft_atoi(char *str);

#endif // PHILOSOPHERS_H
