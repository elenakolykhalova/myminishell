# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/09 11:16:03 by jinigo            #+#    #+#              #
#    Updated: 2021/07/22 18:22:05 by mcarry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= minishell.c env.c pwd.c init.c unset.c export.c exit.c echo.c \
				cd.c utils.c preparsing.c pipe_parser.c parsing.c signal.c \
				func_pipe.c export_utils.c utils2.c parsing_utils.c quote.c \
				dollar.c spacer.c dollar_ver.c dollar_mal.c spacer_ver.c \
				redirect.c redirect_creat.c redirect_creat_utils.c

HEADERS		= minishell.h

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

LIBFT_DIR	= libft/

LIBFT		= libft.a

INCLUDES	= -I${LIBFT_DIR}

CC			= gcc

RM			= rm -f

CFLAGS		= -g -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${LIBFT_DIR}${LIBFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${INCLUDES} -L${LIBFT_DIR} -lreadline -L/Users/mcarry/.brew/Cellar/readline/8.1/lib/ -I/Users/mcarry/.brew/Cellar/readline/8.1/include -lft -o ${NAME}

${LIBFT_DIR}${LIBFT}: ${LIBFT_DIR}
			${MAKE} -C ${LIBFT_DIR} bonus


bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}


re:			fclean all

.PHONY:		all clean fclean re
