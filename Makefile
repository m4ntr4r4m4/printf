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

# Keep `make` (no target) building the library, not the libft-clone rule below
.DEFAULT_GOAL := all

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	libftprintf.a 

CFLAGS	=	-Wall -Werror -Wextra -g 

CC	=	gcc

AR	=	ar rcs

LIBFT_DIR	=	source/libft

LIBFT_REPO	=	git@github.com:m4ntr4r4m4/libft.git

# Fetch libft on demand if it is not already present
$(LIBFT_DIR)/Makefile	:
	@echo "libft not found - cloning from $(LIBFT_REPO)"
	@rm -rf $(LIBFT_DIR)
	git clone $(LIBFT_REPO) $(LIBFT_DIR)

${NAME}	:	$(LIBFT_DIR)/Makefile ${OBJS}
			${MAKE} -C $(LIBFT_DIR) bonus
			cp $(LIBFT_DIR)/libft.a ${NAME}
			${AR}  ${NAME} ${OBJS}

all	:	${NAME}
bonus	:	${NAME}

RM	=	rm -f

clean	:
		@if [ -f $(LIBFT_DIR)/Makefile ]; then ${MAKE} clean -C $(LIBFT_DIR); fi
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}
			${RM} $(LIBFT_DIR)/libft.a

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
