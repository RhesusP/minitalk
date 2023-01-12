# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 15:24:06 by cbernot           #+#    #+#              #
#    Updated: 2023/01/12 16:04:56 by cbernot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME = server
SERVER_SRCS = ./server.c
SERVER_OBJS = ${SERVER_SRCS:.c=.o}

CLIENT_NAME = client
CLIENT_SRCS = ./client.c
CLIENT_OBJS = ${CLIENT_SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	cc ${FLAGS} -c $< -o $@

all: ${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}: ${SERVER_OBJS}
	make -C ./libft
	cc ${SERVER_OBJS} -L ./libft/ -l ft -o ${SERVER_NAME}

${CLIENT_NAME}: ${CLIENT_OBJS}
	make -C ./libft
	cc ${CLIENT_OBJS} -L ./libft/ -l ft -o ${CLIENT_NAME}

clean:
	make clean -C ./libft
	rm -f ${SERVER_OBJS} ${CLIENT_OBJS}

fclean: clean
	make fclean -C ./libft
	rm -f ${SERVER_NAME} ${CLIENT_NAME}

re: fclean all

.PHONY: all clean fclean re