# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 12:47:32 by ahammoud          #+#    #+#              #
#    Updated: 2021/11/18 17:38:46 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_printf.c  ft_putnbr16.c ./source/ft_putchar_fd.c ./source/ft_putnbr_fd.c ./source/ft_putstr_fd.c

SRCSB	=

OBJS	=	${SRCS:.c=.o}

OBJSBN	=	${SRCSB:.c=.o}


.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

NAME	=	 libftprintf.a

CFLAGS	=	-Wall -Werror -Wextra

CC	=	gcc

AR	=	ar rc

${NAME}	:	${OBJS}
		${AR}  ${NAME} ${OBJS}

bonus	:	${OBJS} ${OBJSBN}
		${AR}  ${NAME} ${OBJS} ${OBJSBN}

all	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C ./libft
		${RM} ${OBJS} ${OBJSBN}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
