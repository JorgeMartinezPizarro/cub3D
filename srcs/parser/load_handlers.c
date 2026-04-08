/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:51 by jomarti3          #+#    #+#             */
/*   Updated: 2026/04/08 17:17:47 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_move(int x, int y, t_game *g)
{
	int	center_x;
	int	center_y;
	int	delta_x;

	if (!g->mouse_enable)
		return (0);
	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	if (abs(delta_x) > 1 && abs(delta_x) < 200)
	{
		g->p.angle += delta_x * MOUSE_SENS;
		normalize_angle(&g->p.angle);
	}
	mlx_mouse_move(g->mlx, g->win, center_x, center_y);
	return (0);
}

void	ft_draw_crosshair(t_game *g)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	put_pixel(&g->frame, cx, cy, COLOR_WALL);
	i = 3;
	while (i <= 10)
	{
		put_pixel(&g->frame, cx - i, cy, COLOR_WALL);
		put_pixel(&g->frame, cx + i, cy, COLOR_WALL);
		put_pixel(&g->frame, cx, cy - i, COLOR_WALL);
		put_pixel(&g->frame, cx, cy + i, COLOR_WALL);
		i++;
	}
}

void	load_handlers(t_game *g)
{
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_hook(g->win, 17, 0, exit_program, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}

void	toggle_mouse(t_game *g, int enable)
{
	if (enable)
		mlx_mouse_hide(g->mlx, g->win);
	else
		mlx_mouse_show(g->mlx, g->win);
	g->mouse_enable = enable;
}
