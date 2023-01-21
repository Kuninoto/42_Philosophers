# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 12:34:39 by nnuno-ca          #+#    #+#              #
#    Updated: 2023/01/21 01:39:11 by nnuno-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -rf

NAME = philo
SRCS =  srcs/utils/ft_atoi.c\
		srcs/utils/panic.c\
		srcs/utils/destroy.c\
		srcs/utils/get_time.c\
		srcs/utils/init_forks.c\
		srcs/input/is_all_digits.c\
		srcs/input/init_args.c\
		srcs/philos/init_philos.c\
		srcs/philos/routine.c\
		srcs/create_threads.c\
		srcs/monitoring.c\
	   	main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o philo

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

run: all clean

.PHONY: all clean fclean re run

.SILENT:
