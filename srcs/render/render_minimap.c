/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:47:57 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/02 21:48:53 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_minimap_color(t_game *g, int x, int y)
{
	int	map_x;
	int	map_y;
	int	color;

	map_x = (int)g->p.x + x;
	map_y = (int)g->p.y + y;
	color = 0x000000;
	if (map_x >= 0 && map_x < g->width
		&& map_y >= 0 && map_y < g->height)
	{
		if (g->world[map_y][map_x] == 1)
			color = COLOR_WALL;
		else
			color = COLOR_EMPTY;
	}
	return (color);
}

void	put_row(t_game *g, int x, int y)
{
	int	py;
	int	px;

	py = 0;
	while (py < MM_SCALE)
	{
		px = 0;
		while (px < MM_SCALE)
		{
			put_pixel(&g->frame,
				MM_OFFSET_X + (x + MINIMAP_RADIUS) * MM_SCALE + px,
				MM_OFFSET_Y + (y + MINIMAP_RADIUS) * MM_SCALE + py,
				get_minimap_color(g, x, y));
			px++;
		}
		py++;
	}
}

void	render_minimap(t_game *g)
{
	int	x;
	int	y;

	y = -MINIMAP_RADIUS;
	while (y <= MINIMAP_RADIUS)
	{
		x = -MINIMAP_RADIUS;
		while (x <= MINIMAP_RADIUS)
			put_row(g, x++, y);
		y++;
	}
	x = -MM_SCALE / 2;
	while (x < MM_SCALE / 2)
	{
		y = -MM_SCALE / 2;
		while (y < MM_SCALE / 2)
		{
			put_pixel(&g->frame,
				MM_OFFSET_X + MINIMAP_RADIUS * MM_SCALE + x,
				MM_OFFSET_Y + MINIMAP_RADIUS * MM_SCALE + y,
				COLOR_PLAYER);
			y++;
		}
		x++;
	}
}
