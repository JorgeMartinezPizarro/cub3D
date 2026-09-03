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
	append_str(buf, &i, "Has abierto todas las ");
	append_pad(buf, &i, g->door_total, 1);
	append_str(buf, &i, " puertas en ");
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
	while (y < tex->h)
	{
		x = 0;
		while (x < tex->w)
		{
			color = get_pixel(tex, x, y);
			if (color != 0x000000)
				put_pixel(&g->frame, ox + x, oy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_corner(t_game *g, t_img *tex, int cx, int cy)
{
	blit_fireworks(g, tex, cx - tex->w / 2, cy - tex->h / 2);
}

void	put_centered(t_game *g, int y, char *s)
{
	mlx_string_put(g->mlx, g->win, WIDTH / 2 - ft_strlen(s) * FONT_CHAR_W / 2,
		y, 0x00FFFFFF, s);
}
