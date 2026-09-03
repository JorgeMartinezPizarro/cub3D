/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen_preview.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	preview_color(t_game *g, int x, int y)
{
	int	tile;

	tile = g->world[y][x];
	if (tile == TILE_WALL)
		return (COLOR_WALL);
	if (tile == TILE_DOOR || tile == TILE_DOOR_HALF)
		return (COLOR_DOOR);
	return (COLOR_EMPTY);
}

void	render_map_preview(t_game *g, int ox, int oy, int scale)
{
	int	x;
	int	y;
	int	i;
	int	color;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			color = preview_color(g, x, y);
			i = 0;
			while (i < scale * scale)
			{
				put_pixel(&g->frame, ox + x * scale + i % scale,
					oy + y * scale + i / scale, color);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	draw_spawn_arrow(t_game *g, int ox, int oy, int scale)
{
	int	dx;
	int	dy;
	int	relx;
	int	rely;

	dx = (g->p.angle == 0) - (g->p.angle == M_PI);
	dy = (g->p.angle == M_PI / 2) - (g->p.angle == -M_PI / 2);
	rely = -START_ARROW_LEN;
	while (rely <= START_ARROW_LEN)
	{
		relx = -START_ARROW_LEN;
		while (relx <= START_ARROW_LEN)
		{
			if (relx * dx + rely * dy >= 0
				&& relx * dy - rely * dx + relx * dx + rely * dy
				<= START_ARROW_LEN
				&& relx * dx + rely * dy - relx * dy + rely * dx
				<= START_ARROW_LEN)
				put_pixel(&g->frame, ox + (int)(g->p.x * scale) + relx,
					oy + (int)(g->p.y * scale) + rely, COLOR_PLAYER);
			relx++;
		}
		rely++;
	}
}
