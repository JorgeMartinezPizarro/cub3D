/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 19:26:24 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/12 19:26:36 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

double	cast_ray(t_game *g, double angle, double *hitx, double *hity,
	int *side, int *hit_type)
{
	double raydir_x = cos(angle);
	double raydir_y = sin(angle);
	int map_x = (int)g->p.x;
	int map_y = (int)g->p.y;
	double delta_dist_x = fabs(1.0 / raydir_x);
	double delta_dist_y = fabs(1.0 / raydir_y);
	double side_dist_x;
	double side_dist_y;
	int step_x;
	int step_y;
	int hit = 0;
	int dda_side;

	if (raydir_x < 0) {
		step_x = -1;
		side_dist_x = (g->p.x - map_x) * delta_dist_x;
	} else {
		step_x = 1;
		side_dist_x = (map_x + 1.0 - g->p.x) * delta_dist_x;
	}
	if (raydir_y < 0) {
		step_y = -1;
		side_dist_y = (g->p.y - map_y) * delta_dist_y;
	} else {
		step_y = 1;
		side_dist_y = (map_y + 1.0 - g->p.y) * delta_dist_y;
	}
	*hit_type = TILE_WALL;
	while (!hit) {
		if (side_dist_x < side_dist_y) {
			side_dist_x += delta_dist_x;
			map_x += step_x;
			dda_side = 0;
		} else {
			side_dist_y += delta_dist_y;
			map_y += step_y;
			dda_side = 1;
		}
		if (g->world[map_y][map_x] == TILE_WALL)
		{
			hit = 1;
			*hit_type = TILE_WALL;
		}
		else if (g->world[map_y][map_x] == TILE_DOOR)
		{
			hit = 1;
			*hit_type = TILE_DOOR;
		}
	}
	double perp_dist;
	if (dda_side == 0)
		perp_dist = (map_x - g->p.x + (1 - step_x) / 2) / raydir_x;
	else
		perp_dist = (map_y - g->p.y + (1 - step_y) / 2) / raydir_y;
	*hitx = g->p.x + perp_dist * raydir_x;
	*hity = g->p.y + perp_dist * raydir_y;
	if (dda_side == 0)
		*side = (raydir_x > 0) ? 2 : 3;
	else
		*side = (raydir_y > 0) ? 1 : 0;
	return (perp_dist);
}
