# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 13:06:26 by dangtran          #+#    #+#              #
#    Updated: 2025/03/22 14:17:05 by dangtran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS= -Wall -Wextra -Werror -I${HEADER_DIR} -g

SRCS_DIR = 	$(addprefix sources/, parsing.c init.c routine.c check.c philos.c main.c) $(EXTRAS)

SRCS_OBJ = ${SRCS_DIR:.c=.o}

EXTRAS = $(addprefix extras/, ft_atoi.c get_time.c)

HEADER_DIR=./includes/

all: $(NAME)

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) $(SRCS_OBJ) -o $(NAME)


clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all