# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2026/08/31 14:43:55 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

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

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx_linux

MLX			= $(MLX_DIR)/libmlx_Linux.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
CPPFLAGS	= -I./includes -I./$(LIBFT_DIR)/src -I./$(MLX_DIR)
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS  := -lft -lmlx_Linux -lXext -lX11 -lm

OBJECTS			= $(addprefix srcs/, $(FILES:=.o))
DEPENDENCIES	= $(addprefix srcs/, $(FILES:=.d))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean || true
	rm -f $(OBJECTS) $(DEPENDENCIES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(MLX_DIR)/Makefile.gen $(MLX_DIR)/test/Makefile.gen
	rm -f $(NAME)

re: fclean all

###############################################################################
## Basic code metrics.
###############################################################################
stats:
	@./scripts/summary.sh

test: all
	@./scripts/test.sh

debug: all
	@./scripts/debug.sh

-include $(DEPENDENCIES)

.PHONY: all clean fclean re bonus stats test debug
