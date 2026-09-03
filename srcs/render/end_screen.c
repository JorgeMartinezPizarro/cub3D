/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_build_win_message(t_game *g, int min, int sec, int ms)
{
	char	buf[96];
	int		i;

	i = 0;
	append_str(buf, &i, "You opened all ");
	append_pad(buf, &i, g->door_total, 1);
	append_str(buf, &i, " doors in ");
	append_pad(buf, &i, min, 2);
	append_str(buf, &i, ":");
	append_pad(buf, &i, sec, 2);
	append_str(buf, &i, ".");
	append_pad(buf, &i, ms, 3);
	append_str(buf, &i, ".");
	buf[i] = '\0';
	return (ft_strdup(buf));
}

static void	blit_fireworks(t_game *g, t_img *tex, int ox, int oy)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < ICON_DISPLAY_SIZE)
	{
		x = 0;
		while (x < ICON_DISPLAY_SIZE)
		{
			color = get_pixel(tex, x * tex->w / ICON_DISPLAY_SIZE,
					y * tex->h / ICON_DISPLAY_SIZE);
			if (color != 0x000000)
				put_pixel(&g->frame, ox + x, oy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_corner(t_game *g, t_img *tex, int cx, int cy)
{
	blit_fireworks(g, tex, cx - ICON_DISPLAY_SIZE / 2,
		cy - ICON_DISPLAY_SIZE / 2);
}

void	put_centered(t_game *g, int y, char *s)
{
	put_centered_scaled(g, y, s, 1.5);
}
