/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:26:24 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/16 20:08:55 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	ray_init(t_game *g, t_ray *r)
{
	r->dir_x = cos(r->angle);
	r->dir_y = sin(r->angle);
	r->map_x = (int)g->p.x;
	r->map_y = (int)g->p.y;
	r->delta_x = fabs(1.0 / r->dir_x);
	r->delta_y = fabs(1.0 / r->dir_y);
	r->hit_type = TILE_WALL;
}

static void	ray_steps(t_game *g, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->p.x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->p.x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->p.y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->p.y) * r->delta_y;
	}
}

static int	ray_dda(t_game *g, t_ray *r)
{
	int	side;

	side = 0;
	while (1)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			side = 1;
		}
		if (g->world[r->map_y][r->map_x] == TILE_WALL
			|| g->world[r->map_y][r->map_x] == TILE_DOOR
			|| g->world[r->map_y][r->map_x] == TILE_DOOR_HALF)
		{
			r->hit_type = g->world[r->map_y][r->map_x];
			return (side);
		}
	}
}

static void	ray_hit(t_game *g, t_ray *r, int side)
{
	if (side == 0)
	{
		r->dist = (r->map_x - g->p.x + (1 - r->step_x) / 2) / r->dir_x;
		if (r->dir_x > 0)
			r->side = 2;
		else
			r->side = 3;
	}
	else
	{
		r->dist = (r->map_y - g->p.y + (1 - r->step_y) / 2) / r->dir_y;
		if (r->dir_y > 0)
			r->side = 1;
		else
			r->side = 0;
	}
	r->hit_x = g->p.x + r->dist * r->dir_x;
	r->hit_y = g->p.y + r->dist * r->dir_y;
}

double	cast_ray(t_game *g, t_ray *r)
{
	int	side;

	ray_init(g, r);
	ray_steps(g, r);
	side = ray_dda(g, r);
	ray_hit(g, r, side);
	return (r->dist);
}
