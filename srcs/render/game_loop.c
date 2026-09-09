/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:25:41 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/08 16:57:08 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_hand_animation(t_game *g)
{
	if (get_time() - g->last_hand_time >= 100)
	{
		g->current_hand_frame = (g->current_hand_frame + 1) % 4;
		g->last_hand_time = get_time();
	}
}

static int	in_bounds(t_game *g, double x, double y)
{
	return (x >= 0 && x < g->width && y >= 0 && y < g->height);
}

static void	move_player(t_game *g, double dx, double dy)
{
	double	margin_x;
	double	margin_y;
	int		tile;

	update_hand_animation(g);
	if (dx > 0)
		margin_x = PLAYER_RADIUS;
	else
		margin_x = -PLAYER_RADIUS;
	if (dy > 0)
		margin_y = PLAYER_RADIUS;
	else
		margin_y = -PLAYER_RADIUS;
	if (in_bounds(g, g->p.x + dx + margin_x, g->p.y))
	{
		tile = g->world[(int)g->p.y][(int)(g->p.x + dx + margin_x)];
		if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
			g->p.x += dx;
	}
	if (in_bounds(g, g->p.x, g->p.y + dy + margin_y))
	{
		tile = g->world[(int)(g->p.y + dy + margin_y)][(int)g->p.x];
		if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
			g->p.y += dy;
	}
}

static void	apply_movement(t_game *g, double distance, double angle)
{
	if (g->keys[KEY_W])
		move_player(g, cos(g->p.angle) * distance,
			sin(g->p.angle) * distance);
	if (g->keys[KEY_S])
		move_player(g, -cos(g->p.angle) * distance,
			-sin(g->p.angle) * distance);
	if (g->keys[KEY_A])
		move_player(g, sin(g->p.angle) * distance,
			-cos(g->p.angle) * distance);
	if (g->keys[KEY_D])
		move_player(g, -sin(g->p.angle) * distance,
			cos(g->p.angle) * distance);
	if (g->keys[KEY_LEFT])
	{
		g->p.angle -= angle;
		update_hand_animation(g);
	}
	if (g->keys[KEY_RIGHT])
	{
		g->p.angle += angle;
		update_hand_animation(g);
	}
	normalize_angle(&g->p.angle);
}

int	game_loop(t_game *g)
{
	long long	now;

	now = get_time();
	if (now - g->last_time < 1000 / FPS)
	{
		return (0);
	}
	if (g->started && !g->finished)
	{
		apply_movement(g,
			MOVE_SPEED * (now - g->last_time),
			ROT_SPEED * (now - g->last_time));
		ft_update_doors(g);
		ft_update_key_anim(g);
		g->last_time = now;
	}
	render(g);
	return (0);
}
