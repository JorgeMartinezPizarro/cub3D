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

static void	draw_start_corners(t_game *g)
{
	draw_corner(g, &g->key_icon, START_KEY_MARGIN, START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, WIDTH - START_KEY_MARGIN, START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, START_KEY_MARGIN, HEIGHT - START_KEY_MARGIN);
	draw_corner(g, &g->key_icon, WIDTH - START_KEY_MARGIN,
		HEIGHT - START_KEY_MARGIN);
}

static int	start_text_block_h(void)
{
	return (40 + START_TEXT_LINES * font_line_h() + font_line_h() / 3);
}

static void	draw_start_texts(t_game *g, int oy, int y)
{
	put_centered(g, oy - START_TITLE_H + 8, g->title_msg);
	put_centered(g, y, g->load_msg);
	y += font_line_h();
	put_centered(g, y, g->size_msg);
	y += font_line_h();
	put_centered(g, y, g->best_msg);
	y += font_line_h() + font_line_h() / 3;
	put_centered(g, y, "Let's open all those FREAKING doors!");
	y += font_line_h();
	put_centered(g, y, "Press ENTER to start.");
	y += font_line_h();
	put_centered(g, y, "Press ESC to exit the game.");
}

void	render_start_screen(t_game *g)
{
	int	scale;
	int	ox;
	int	oy;

	clear_frame(&g->frame, 0x000000);
	draw_start_corners(g);
	scale = preview_scale(g);
	ox = WIDTH / 2 - (g->width * scale) / 2;
	oy = (HEIGHT - (g->height * scale + start_text_block_h() + START_TITLE_H))
		/ 2 + START_TITLE_H;
	render_map_preview(g, ox, oy, scale);
	draw_spawn_arrow(g, ox, oy, scale);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	draw_start_texts(g, oy, oy + g->height * scale + 40);
}
