/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	blit_glyph(t_game *g, t_charview *cv)
{
	int	i;
	int	j;
	int	color;

	j = 0;
	while (j < (int)(cv->tex_h * cv->scale))
	{
		i = 0;
		while (i < (int)(cv->tex_w * cv->scale))
		{
			color = get_pixel(&g->font, cv->tex_x + (int)(i / cv->scale),
					cv->tex_y + (int)(j / cv->scale));
			if (color != 0x00000000)
			{
				if (cv->invert)
					color = 0x00FFFFFF - color;
				put_pixel(&g->frame, cv->screen_x + i, cv->screen_y + j, color);
			}
			i++;
		}
		j++;
	}
}

void	put_glyph(t_game *g, int ch, t_charview *cv)
{
	int	idx;

	if (ch < FONT_FIRST_CHAR || ch >= FONT_FIRST_CHAR + FONT_GLYPH_COUNT)
		return ;
	idx = ch - FONT_FIRST_CHAR;
	cv->tex_x = (idx % FONT_COLS) * FONT_CELL_W;
	cv->tex_y = (idx / FONT_COLS) * FONT_CELL_H;
	cv->tex_w = FONT_CELL_W;
	cv->tex_h = FONT_CELL_H;
	blit_glyph(g, cv);
}

void	put_text(t_game *g, int x, int y, char *s)
{
	t_charview	cv;

	cv.scale = FONT_SIZE;
	cv.invert = 0;
	while (*s)
	{
		cv.screen_x = x;
		cv.screen_y = y;
		put_glyph(g, *s, &cv);
		x += (int)(FONT_CHAR_W * FONT_SIZE);
		s++;
	}
}

void	put_centered_scaled(t_game *g, int y, char *s)
{
	int	x;

	x = WIDTH / 2 - (int)(ft_strlen(s) * FONT_CHAR_W * FONT_SIZE) / 2;
	put_text(g, x, y, s);
}
