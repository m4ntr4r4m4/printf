# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 12:47:32 by ahammoud          #+#    #+#              #
#    Updated: 2025/07/01 03:59:42 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_printf.c \
	parser.c \
	utils.c \
	sum.c \
	handlers_char_str.c \
	handlers_num.c \
	handlers_hex_ptr.c \
	source/ft_putcharf.c \
	source/ft_putstrf.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	libftprintf.a 

CFLAGS	=	-Wall -Werror -Wextra -g 

CC	=	gcc

AR	=	ar rcs

${NAME}	:	${OBJS}
			cd source/libft && make bonus
			cp source/libft/libft.a ${NAME}
			${AR}  ${NAME} ${OBJS}

all	:	${NAME}
bonus	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C source/libft
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}
			${RM} source/libft/libft.a

re		:	fclean all

.PHONY	:	all clean fclean re
.PHONY: analyze

ANALYZER      := scan-build
ANALYZE_ARGS  := --status-bugs \
                  --html-title="Static Analysis" \
                  --html-dir=clang-analyzer-report

analyze:
	@echo "Running Clang Static Analyzer…"
	$(ANALYZER) $(ANALYZE_ARGS) $(MAKE) all
