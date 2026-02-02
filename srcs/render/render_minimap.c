/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:47:57 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/02 14:53:17 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_minimap(t_game *g)
{
	int mx;
	int my;
	int px;
	int py;

	my = 0;
	while (my < g->height)
	{
		mx = 0;
		while (mx < g->width)
		{
			int color;

			if (g->world[my][mx] == 1)
				color = COLOR_WALL;
			else
				color = COLOR_EMPTY;

			py = 0;
			while (py < MM_SCALE)
			{
				px = 0;
				while (px < MM_SCALE)
				{
					put_pixel(
						&g->frame,
						MM_OFFSET_X + mx * MM_SCALE + px,
						MM_OFFSET_Y + my * MM_SCALE + py,
						color
					);
					px++;
				}
				py++;
			}
			mx++;
		}
		my++;
	}

	/* jugador */
	int player_x = MM_OFFSET_X + g->p.x * MM_SCALE;
	int player_y = MM_OFFSET_Y + g->p.y * MM_SCALE;

	py = -2;
	while (py <= 2)
	{
		px = -2;
		while (px <= 2)
		{
			put_pixel(&g->frame,
				player_x + px,
				player_y + py,
				COLOR_PLAYER);
			px++;
		}
		py++;
	}
}