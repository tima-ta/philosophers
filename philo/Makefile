# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fraqioui <fraqioui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 11:57:30 by fraqioui          #+#    #+#              #
#    Updated: 2023/05/31 17:18:46 by fraqioui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FALGS = -Wall -Wextra -Werror
HEADER = philo.h
RM = rm -rf 

FILES = main \
		initialize \
		thread_1 \
		thread_2 \
		helpers

FOBJ = ${FILES:=.o}

all: ${NAME}

${NAME}: ${FOBJ} ${HEADER}
	${CC} ${FALGS} ${FOBJ} -o $@

%.o: %.c
	${CC} ${FALGS} -c $< -o $@

clean:
	${RM} ${FOBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY = all clean fclean re
