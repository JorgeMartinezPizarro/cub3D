# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2026/04/09 00:35:36 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

CPPFLAGS	= -I./includes -I./$(LIBFT_DIR)/src -I./$(MLX_DIR)

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx_linux

MLX			= $(MLX_DIR)/libmlx_Linux.a

FILES		= \
	main \
	render/render_minimap \
	render/animations render/draw_hand_frame \
	render/game_loop render/render \
	utils/free_functions utils/utils \
	utils/cast_ray utils/color \
	utils/helpers utils/get_pixel \
	utils/put_pixel \
	parser/parser parser/parser_init \
	parser/parser_textures parser/parser_map \
	parser/load_game parser/load_handlers \
	parser/load_map

OBJECTS		= $(addprefix srcs/, $(FILES:=.o))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJECTS) \
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

test: all
	@./tests/test.sh

debug: all
	@./tests/debug.sh