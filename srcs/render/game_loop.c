/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:41 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/23 14:06:28 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_game *g, double dx, double dy)
{
	double	margin_x;
	double	margin_y;
	int		tile;

	if (get_time() - g->last_hand_time >= 100)
	{
		g->current_hand_frame = (g->current_hand_frame + 1) % 4;
		g->last_hand_time = get_time();
	}
	if (dx > 0)
		margin_x = PLAYER_RADIUS;
	else
		margin_x = -PLAYER_RADIUS;
	if (dy > 0)
		margin_y = PLAYER_RADIUS;
	else
		margin_y = -PLAYER_RADIUS;
	tile = g->world[(int)g->p.y][(int)(g->p.x + dx + margin_x)];
	if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
		g->p.x += dx;
	tile = g->world[(int)(g->p.y + dy + margin_y)][(int)g->p.x];
	if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
		g->p.y += dy;
}

static void	apply_movement(t_game *g)
{
	if (g->keys[KEY_W])
		move_player(g, cos(g->p.angle) * MOVE_SPEED,
			sin(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_S])
		move_player(g, -cos(g->p.angle) * MOVE_SPEED,
			-sin(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_A])
		move_player(g, sin(g->p.angle) * MOVE_SPEED,
			-cos(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_D])
		move_player(g, -sin(g->p.angle) * MOVE_SPEED,
			cos(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_LEFT])
		g->p.angle -= ROT_SPEED;
	if (g->keys[KEY_RIGHT])
		g->p.angle += ROT_SPEED;
	normalize_angle(&g->p.angle);
}

int	game_loop(t_game *g)
{
	long long	now;

	now = get_time();
	if (now - g->last_time < 1000 / FPS)
		return (0);
	g->last_time = now;
	apply_movement(g);
	ft_update_doors(g);
	render(g);
	return (0);
}
