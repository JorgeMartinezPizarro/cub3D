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

void	render_end_screen(t_game *g)
{
	char	*l2;

	l2 = "Press a key to close the game.";
	clear_frame(&g->frame, 0x000000);
	blit_fireworks(g, &g->fireworks, 40, 40);
	blit_fireworks(g, &g->fireworks2, WIDTH - 40 - g->fireworks2.w, 40);
	blit_fireworks(g, &g->fireworks2, 40, HEIGHT - 40 - g->fireworks2.h);
	blit_fireworks(g, &g->fireworks, WIDTH - 40 - g->fireworks.w,
		HEIGHT - 40 - g->fireworks.h);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	mlx_string_put(g->mlx, g->win,
		WIDTH / 2 - ft_strlen(g->win_msg) * FONT_CHAR_W / 2,
		HEIGHT / 2 - 10, 0x00FFFFFF, g->win_msg);
	mlx_string_put(g->mlx, g->win, WIDTH / 2 - ft_strlen(l2) * FONT_CHAR_W / 2,
		HEIGHT / 2 + 20, 0x00FFFFFF, l2);
}
