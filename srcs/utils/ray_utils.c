/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_step(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		return (0);
	}
	r->side_y += r->delta_y;
	r->map_y += r->step_y;
	return (1);
}

int	ray_door_open(t_game *g, t_ray *r, int side)
{
	t_img	*tex;
	double	dist;
	double	wall_x;
	int		tex_x;

	tex = g->door_anim_tex;
	if (side == 0)
		dist = (r->map_x - g->p.x + (1 - r->step_x) / 2) / r->dir_x;
	else
		dist = (r->map_y - g->p.y + (1 - r->step_y) / 2) / r->dir_y;
	if (side == 1)
		wall_x = g->p.x + dist * r->dir_x;
	else
		wall_x = g->p.y + dist * r->dir_y;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->w);
	if ((unsigned int)get_pixel(tex, tex_x, tex->h / 2) != DOOR_ALPHA_KEY)
		return (0);
	if (!r->has_door)
	{
		r->has_door = 1;
		r->door_dist = dist;
		r->door_wall_x = wall_x;
	}
	return (1);
}
