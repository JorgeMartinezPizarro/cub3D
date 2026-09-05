/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen_layout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_all_corners(t_game *g)
{
	draw_corner(g, &g->fireworks, START_KEY_MARGIN, START_KEY_MARGIN);
	draw_corner(g, &g->fireworks2, WIDTH - START_KEY_MARGIN,
		START_KEY_MARGIN);
	draw_corner(g, &g->fireworks2, START_KEY_MARGIN,
		HEIGHT - START_KEY_MARGIN);
	draw_corner(g, &g->fireworks, WIDTH - START_KEY_MARGIN,
		HEIGHT - START_KEY_MARGIN);
}

static void	draw_end_texts(t_game *g)
{
	int	y;

	y = HEIGHT / 2 - 2 * font_line_h();
	put_centered(g, y, g->map_msg);
	y += font_line_h();
	put_centered(g, y, g->win_msg);
	y += font_line_h();
	if (g->score_msg)
	{
		put_centered(g, y, g->score_msg);
		y += font_line_h();
	}
	if (g->record_msg)
	{
		put_centered(g, y, g->record_msg);
		y += font_line_h();
	}
	put_centered(g, y, "Press ESC to exit, or ENTER to play again.");
}

void	render_end_screen(t_game *g)
{
	clear_frame(&g->frame, 0x000000);
	draw_all_corners(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	draw_end_texts(g);
}
