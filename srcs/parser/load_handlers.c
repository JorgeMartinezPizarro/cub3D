/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:51 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 15:30:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_move(int x, int y, t_game *g)
{
	(void)y;
	g->mouse_x = x;
	return (0);
}

void	load_handlers(t_game *g)
{
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(g->mlx, g->win);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_hook(g->win, 17, 0, exit_program, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}
