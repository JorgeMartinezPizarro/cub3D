/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hand_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:01:50 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/22 15:18:51 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_hand(t_game *g)
{
	if (g->key_anim_frame >= 0)
		draw_hand_frame(g, &g->key_sheet, g->key_anim_frame);
	else
		draw_hand_frame(g, &g->hand_sheet, g->current_hand_frame);
}

void	draw_hand_frame(t_game *g, t_img *sheet, int frame_idx)
{
	int			x;
	int			y;
	t_charview	cv;
	int			color;

	cv.tex_w = sheet->w / 2;
	cv.tex_h = sheet->h / 2;
	cv.tex_x = (frame_idx % 2) * cv.tex_w;
	cv.tex_y = (frame_idx / 2) * cv.tex_h;
	cv.screen_x = (WIDTH / 2) - (cv.tex_w * HAND_SCALE / 2);
	cv.screen_y = HEIGHT - (cv.tex_h * HAND_SCALE) + (20 * HAND_SCALE);
	y = 0;
	while (y < cv.tex_h * HAND_SCALE)
	{
		x = 0;
		while (x < cv.tex_w * HAND_SCALE)
		{
			color = get_pixel(sheet, cv.tex_x + x / HAND_SCALE,
					cv.tex_y + y / HAND_SCALE);
			if (color != 0x000000 && color > 0)
				put_pixel(&g->frame, cv.screen_x + x, cv.screen_y + y, color);
			x++;
		}
		y++;
	}
}
