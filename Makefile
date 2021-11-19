# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 12:47:32 by ahammoud          #+#    #+#              #
#    Updated: 2021/11/19 11:22:57 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_printf.c \
		  ./source/ft_putnbr16.c \


SRCSB	=

OBJS	=	${SRCS:.c=.o}

OBJSBN	=	${SRCSB:.c=.o}


.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	libftprintf.a 

CFLAGS	=	-Wall -Werror -Wextra

CC	=	gcc

AR	=	ar rcs

${NAME}	:	${OBJS}
			cd ./source/libft/ && make
			cp ./source/libft/libft.a ${NAME}
			${AR}  ${NAME} ${OBJS}

bonus	:	${OBJS} ${OBJSBN}
		${AR}  ${NAME} ${OBJS} ${OBJSBN}
all	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C ./source/libft
		${RM} ${OBJS} ${OBJSBN}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
