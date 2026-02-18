/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:44:09 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/18 19:16:52 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_spawn(t_config *config, int x, int y, char c)
{
	config->x_spawn = x;
	config->y_spawn = y;
	if (c == 'N')
		config->spawn_angle = -M_PI / 2;
	else if (c == 'S')
		config->spawn_angle = M_PI / 2;
	else if (c == 'E')
		config->spawn_angle = 0;
	else if (c == 'W')
		config->spawn_angle = M_PI;
}

static void	ft_fill_row(t_config *config, t_game *game, int y)
{
	int	x;
	int	len;

	len = ft_strlen(config->map[y]);
	x = 0;
	while (x < config->width)
	{
		if (x < len && config->map[y][x] == '1')
			game->world[y][x] = TILE_WALL;
		else if (x < len && config->map[y][x] == 'D')
			game->world[y][x] = TILE_DOOR;
		else
			game->world[y][x] = TILE_EMPTY;
		x++;
	}
}

static int	ft_create_world(t_config *config, t_game *game)
{
	int	y;

	game->world = malloc(sizeof(int *) * config->height);
	if (!game->world)
		return (0);
	y = 0;
	while (y < config->height)
	{
		game->world[y] = malloc(sizeof(int) * config->width);
		if (!game->world[y])
		{
			game->height = y;
			free_game(game);
			return (0);
		}
		ft_fill_row(config, game, y);
		y++;
	}
	return (1);
}

int	ft_config_to_game(t_config *config, t_game *game)
{
	if (config->width > MAX_MAP_SIZE || config->height > MAX_MAP_SIZE)
	{
		ft_print_errors(ERR_MAP_TOO_LONG);
		return (0);
	}
	game->width = config->width;
	game->height = config->height;
	if (!ft_create_world(config, game))
		return (0);
	game->p.x = config->x_spawn + 0.5;
	game->p.y = config->y_spawn + 0.5;
	game->p.angle = config->spawn_angle;
	game->floor_color = rgb_to_hex(config->floor);
	game->ceiling_color = rgb_to_hex(config->sky);
	return (1);
}
