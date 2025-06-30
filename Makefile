# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 12:47:32 by ahammoud          #+#    #+#              #
#    Updated: 2021/11/22 08:11:11 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_printf.c \
			ft_types.c \
			./source/ft_putcharf.c \
			./source/ft_putnbr_base.c \
		  	./source/ft_putstrf.c \

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	libftprintf.a 

CFLAGS	=	-Wall -Werror -Wextra -g -pipe -Ofast -march=native -finline-functions

CC	=	gcc

AR	=	ar rcs

${NAME}	:	${OBJS}
			cd libft && make bonus
			cp libft/libft.a ${NAME}
			${AR}  ${NAME} ${OBJS}

all	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C libft
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}
			${RM} libft/libft.a

re		:	fclean all

.PHONY	:	all clean fclean re
