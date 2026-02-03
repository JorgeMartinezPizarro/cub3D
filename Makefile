# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2026/02/03 02:00:21 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx_linux

MLX			= $(MLX_DIR)/libmlx_Linux.a

FILES		= \
	main \
	parser/load_map \
	render/render_minimap render/put_pixel \
	utils/free_functions 

OBJECTS		= $(addprefix srcs/, $(FILES:=.o))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror \
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
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJECTS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(MLX_DIR)/Makefile.gen $(MLX_DIR)/test/Makefile.gen
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

###############################################################################
## Basic code metrics.
###############################################################################
stats:
	@lines=$$( \
		{ \
			find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) -exec cat {} +; \
		} | grep -Ev '^[[:space:]]*(#|//|$$)' | wc -l \
	); \
	echo ""; \
	echo "  - Total of lines: \033[0;32m$$lines\033[0m"; \
	files=$$( \
		find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) | wc -l \
	); \
	echo "  - Total of files: \033[0;32m$$files\033[0m"; \
	echo ""