/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
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

static int	preview_scale(t_game *g)
{
	int	scale_w;
	int	scale_h;

	scale_w = START_PREVIEW_MAX_W / g->width;
	scale_h = START_PREVIEW_MAX_H / g->height;
	if (scale_w < 1)
		scale_w = 1;
	if (scale_h < 1)
		scale_h = 1;
	if (scale_w < scale_h)
		return (scale_w);
	return (scale_h);
}

static void	render_map_preview(t_game *g, int ox, int oy, int scale)
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

static void	draw_spawn_arrow(t_game *g, int ox, int oy, int scale)
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

void	render_start_screen(t_game *g)
{
	int	scale;
	int	ox;
	int	oy;
	int	y;

	clear_frame(&g->frame, 0x000000);
	draw_corner(g, &g->key_icon, START_KEY_MARGIN, START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, WIDTH - START_KEY_MARGIN, START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, START_KEY_MARGIN, HEIGHT - START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, WIDTH - START_KEY_MARGIN,
		HEIGHT - START_KEY_MARGIN);
	scale = preview_scale(g);
	ox = WIDTH / 2 - (g->width * scale) / 2;
	oy = (HEIGHT - (g->height * scale + START_TEXT_BLOCK_H)) / 2;
	render_map_preview(g, ox, oy, scale);
	draw_spawn_arrow(g, ox, oy, scale);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	y = oy + g->height * scale + 40;
	put_centered(g, y, g->load_msg);
	put_centered(g, y + 25, g->size_msg);
	put_centered(g, y + 50, g->best_msg);
	put_centered(g, y + 85, "Let's open all those dammit doors!");
	put_centered(g, y + 115, "Press ENTER to start.");
}
