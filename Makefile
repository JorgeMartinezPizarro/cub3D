# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2026/09/02 14:57:40 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

FILES		= \
	main \
	render/render_minimap \
	render/animations render/draw_hand_frame \
	render/game_loop render/render \
	render/door_layer render/start_screen render/start_screen_preview \
	render/end_screen render/put_text \
	render/end_screen_layout render/hud \
	utils/free_functions utils/free_config utils/utils \
	utils/msg_utils utils/msg_utils2 \
	utils/cast_ray utils/ray_utils utils/color \
	utils/helpers utils/get_pixel \
	utils/put_pixel \
	utils/score_codec utils/score_io utils/score_game \
	parser/parser parser/parser_init \
	parser/parser_textures parser/parser_map \
	parser/load_game parser/load_handlers \
	parser/load_map parser/parser_flood \
	parser/load_font \
	parser/switch_map parser/map_reload

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx

MLX			= $(MLX_DIR)/libmlx_Linux.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP
CPPFLAGS	= -I./includes -I./$(LIBFT_DIR)/src -I./$(MLX_DIR)
LDFLAGS := -L$(LIBFT_DIR) -L$(MLX_DIR) -L/usr/lib
LDLIBS  := -lft -lmlx_Linux -lXext -lX11 -lm

SOURCES			= $(addprefix srcs/, $(FILES:=.c))
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

###############################################################################
## Test and debug targets
###############################################################################
build-san: $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) \
		$(LDFLAGS) $(LDLIBS) \
		-fsanitize=address -fsanitize=undefined \
		-o $(NAME)_san

clean-san: 
	rm -f $(NAME)_san*

test: all
	@./scripts/test.sh

debug: 
	@./scripts/debug.sh

-include $(DEPENDENCIES)

.PHONY: all clean fclean re bonus stats test debug build-san clean-san
