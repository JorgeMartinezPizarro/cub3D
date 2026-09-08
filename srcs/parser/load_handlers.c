/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:51 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/08 15:36:40 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_move(int x, int y, t_game *g)
{
	int	center_x;
	int	center_y;
	int	delta_x;
	int	abs_delta;

	if (!g->mouse_enable)
		return (0);
	center_x = g->frame.w / 2;
	center_y = g->frame.h / 2;
	if (x == center_x && y == center_y)
		return (0);
	delta_x = x - center_x;
	abs_delta = delta_x;
	if (abs_delta < 0)
		abs_delta = -abs_delta;
	if (abs_delta > 1 && abs_delta < 200)
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

	cx = g->frame.w / 2;
	cy = g->frame.h / 2;
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
	mlx_do_key_autorepeatoff(g->mlx);
	mlx_mouse_move(g->mlx, g->win, g->frame.w / 2, g->frame.h / 2);
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

void	resolve_win_size(t_game *g, int *win_w, int *win_h)
{
	int	max_w;
	int	max_h;

	mlx_get_screen_size(g->mlx, &max_w, &max_h);
	max_w -= WIN_FRAME_W;
	max_h -= WIN_FRAME_H;
	*win_w = WANTED_WIDTH;
	if (*win_w == 0 || *win_w > max_w)
		*win_w = max_w;
	*win_h = WANTED_HEIGHT;
	if (*win_h == 0 || *win_h > max_h)
		*win_h = max_h;
}
