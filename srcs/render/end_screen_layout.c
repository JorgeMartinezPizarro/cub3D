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

static int	end_msg_width(t_game *g, char *l2)
{
	int	w;

	w = ft_strlen(g->map_msg);
	if (ft_strlen(g->win_msg) > w)
		w = ft_strlen(g->win_msg);
	if (g->score_msg && ft_strlen(g->score_msg) > w)
		w = ft_strlen(g->score_msg);
	if (g->record_msg && ft_strlen(g->record_msg) > w)
		w = ft_strlen(g->record_msg);
	if (ft_strlen(l2) > w)
		w = ft_strlen(l2);
	return (w * FONT_CHAR_W / 2);
}

static void	draw_all_corners(t_game *g, int half_w, int top, int bottom)
{
	draw_corner(g, &g->fireworks, (WIDTH / 2 - half_w) * 2 / 3, top * 2 / 3);
	draw_corner(g, &g->fireworks2, WIDTH - (WIDTH / 2 - half_w) * 2 / 3,
		top * 2 / 3);
	draw_corner(g, &g->fireworks2, (WIDTH / 2 - half_w) * 2 / 3,
		HEIGHT - (HEIGHT - bottom) * 2 / 3);
	draw_corner(g, &g->fireworks, WIDTH - (WIDTH / 2 - half_w) * 2 / 3,
		HEIGHT - (HEIGHT - bottom) * 2 / 3);
}

static void	draw_end_texts(t_game *g, char *l2)
{
	int	y;

	put_centered(g, HEIGHT / 2 - 40, g->map_msg);
	put_centered(g, HEIGHT / 2 - 10, g->win_msg);
	y = HEIGHT / 2 + 20;
	if (g->score_msg)
	{
		put_centered(g, y, g->score_msg);
		y += 20;
	}
	if (g->record_msg)
	{
		put_centered(g, y, g->record_msg);
		y += 20;
	}
	put_centered(g, y, l2);
}

void	render_end_screen(t_game *g)
{
	char	*l2;
	int		half_w;
	int		bottom;

	l2 = "Press ENTER to close the game.";
	half_w = end_msg_width(g, l2);
	bottom = HEIGHT / 2 + 22;
	if (g->score_msg)
		bottom += 20;
	if (g->record_msg)
		bottom += 20;
	clear_frame(&g->frame, 0x000000);
	draw_all_corners(g, half_w, HEIGHT / 2 - 51, bottom);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	draw_end_texts(g, l2);
}
