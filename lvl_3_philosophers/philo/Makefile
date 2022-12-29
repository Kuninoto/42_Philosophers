# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnuno-ca <nnuno-ca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 12:34:39 by nnuno-ca          #+#    #+#              #
#    Updated: 2022/12/29 15:55:59 by nnuno-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

NAME = philo
SRCS =  srcs/utils/on_error.c\
		srcs/utils/long_atoi.c\
		srcs/input/validate_args.c\
	   	main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o philo

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.SILENT:
