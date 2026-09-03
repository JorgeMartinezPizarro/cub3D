/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:28:07 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/16 20:31:16 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*door_frame_tex(t_game *g, int frame)
{
	if (frame <= 0)
		return (&g->door_closed);
	if (frame == 1)
		return (&g->door_half);
	return (&g->door_open);
}

static void	ft_print_win(t_game *g)
{
	long long	elapsed;
	int			min;
	int			sec;
	int			ms;

	elapsed = get_time() - g->game_start;
	min = (int)(elapsed / 60000);
	sec = (int)((elapsed / 1000) % 60);
	ms = (int)(elapsed % 1000);
	ft_printf("Has abierto todas las %d puertas en %02d:%02d.%03d.\n",
		g->door_total, min, sec, ms);
	g->win_msg = ft_build_win_message(g, min, sec, ms);
	g->finished = 1;
}

static void	ft_finish_door(t_game *g)
{
	if (g->door_opening)
	{
		g->world[g->door_y][g->door_x] = TILE_DOOR_OPEN;
		g->doors_opened++;
	}
	else
	{
		g->world[g->door_y][g->door_x] = TILE_DOOR;
		g->doors_opened--;
	}
	g->door_x = -1;
	if (g->doors_opened == g->door_total)
		ft_print_win(g);
}

void	ft_update_doors(t_game *g)
{
	long long	elapsed;
	int			frame;

	if (g->door_x < 0)
		return ;
	elapsed = get_time() - g->door_time;
	if (elapsed >= DOOR_ANIM_MS)
	{
		ft_finish_door(g);
		return ;
	}
	frame = (int)(elapsed / DOOR_FRAME_MS);
	if (!g->door_opening)
		frame = 2 - frame;
	g->door_anim_tex = door_frame_tex(g, frame);
}

void	ft_toggle_door(t_game *g)
{
	int	map_x;
	int	map_y;
	int	tile;

	if (g->door_x >= 0)
		return ;
	map_x = (int)(g->p.x + cos(g->p.angle) * 1.5);
	map_y = (int)(g->p.y + sin(g->p.angle) * 1.5);
	if (map_x < 0 || map_x >= g->width || map_y < 0 || map_y >= g->height)
		return ;
	tile = g->world[map_y][map_x];
	if (tile == TILE_DOOR || tile == TILE_DOOR_OPEN)
	{
		g->world[map_y][map_x] = TILE_DOOR_HALF;
		g->door_x = map_x;
		g->door_y = map_y;
		g->door_opening = (tile == TILE_DOOR);
		g->door_time = get_time();
		if (g->door_opening)
			g->door_anim_tex = &g->door_closed;
		else
			g->door_anim_tex = &g->door_open;
	}
}
