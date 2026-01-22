# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2026/01/20 14:46:14 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

MLX_DIR     = mlx_linux

MLX      = $(MLX_DIR)/libmlx_Linux.a

FILES = \
	main

OBJECTS = $(addprefix srcs/, $(FILES:=.o))
CC       = cc

CFLAGS   = -Wall -Wextra -Werror \
	-I./includes -I./$(LIBFT_DIR)/src -I./$(MLX_DIR)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx_Linux \
		-L/usr/lib -lXext -lX11 -lm \
		-o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)
	
clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus