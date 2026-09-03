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

static void	blit_glyph(t_game *g, int idx, int x, int y)
{
	int	i;
	int	j;
	int	sx;
	int	sy;
	int	color;

	sx = (idx % FONT_COLS) * FONT_CELL_W;
	sy = (idx / FONT_COLS) * FONT_CELL_H;
	j = 0;
	while (j < (int)(FONT_CELL_H * FONT_SIZE))
	{
		i = 0;
		while (i < (int)(FONT_CELL_W * FONT_SIZE))
		{
			color = get_pixel(&g->font, sx + (int)(i / FONT_SIZE),
					sy + (int)(j / FONT_SIZE));
			if (color != 0x00000000)
				put_pixel(&g->frame, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	put_text(t_game *g, int x, int y, char *s)
{
	while (*s)
	{
		if (*s >= FONT_FIRST_CHAR && *s < FONT_FIRST_CHAR + FONT_GLYPH_COUNT)
			blit_glyph(g, *s - FONT_FIRST_CHAR, x, y);
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
