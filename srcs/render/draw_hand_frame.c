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

void	draw_hand_frame(t_game *g, t_img *sheet, int frame_idx)
{
	int			x;
	int			y;
	t_charview	cv;
	int			color;

	cv.tex_x = (frame_idx % 2) * HAND_WIDTH;
	cv.tex_y = (frame_idx / 2) * HAND_HEIGHT;
	cv.screen_x = (WIDTH / 2) - (HAND_WIDTH / 2);
	cv.screen_y = HEIGHT - HAND_HEIGHT + 20;
	y = 0;
	while (y < HAND_HEIGHT)
	{
		x = 0;
		while (x < HAND_WIDTH)
		{
			color = get_pixel(sheet, cv.tex_x + x, cv.tex_y + y);
			if (color != 0x000000 && color > 0)
				put_pixel(&g->frame, cv.screen_x + x, cv.screen_y + y, color);
			x++;
		}
		y++;
	}
}
