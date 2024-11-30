# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/28 16:24:23 by yooshima          #+#    #+#              #
#    Updated: 2024/11/30 12:41:10 by yooshima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

SRCS		=	$(wildcard *.c)

OBJ			=	$(SRCS:.c=.o)

INCLUDES	=	-I/usr/include -Imlx

MLX_DIR		=	./minilibx-linux
MLX_LIB		=	$(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS	=	-Lmlx -lXext -lX11

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
MATH_FLAGS	=	-lm

%.o:		%.c
			${CC} ${CFLAGS} -c $< -o $@

all:			$(NAME)

$(NAME):		$(MLX_LIB) $(OBJ)
				$(CC) $(CFLAGS) $(MATH_FLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(MLX_LIB)

$(MLX_LIB):
				${MAKE} -C $(MLX_DIR)

clean: 
				${MAKE} -C $(MLX_DIR) clean
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re

