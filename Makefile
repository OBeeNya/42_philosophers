# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 14:04:56 by baubigna          #+#    #+#              #
#    Updated: 2022/03/21 15:02:03 by baubigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	srcs/main.c \
			srcs/funcs_0.c \
			srcs/funcs_1.c \
			srcs/funcs_2.c
			
OBJS	=	${SRCS:.c=.o}

GCC		=	gcc

RM		=	rm -rf

GFLAGS	=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread #-fsanitize=address

all:		${NAME}

.c.o:
			${GCC} ${GLAGS} -c $< -o ${<:.c=.o}

${NAME}:	
			${GCC} ${GFLAGS} ${SRCS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all fclean clean re
