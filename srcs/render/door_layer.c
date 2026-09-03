/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_layer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_door(t_ray *ray, t_column *col)
{
	col->has_door = ray->has_door;
	if (!ray->has_door)
		return ;
	col->d_wall_h = (int)(HEIGHT / ray->door_cam_dist);
	col->d_start = HEIGHT / 2 - col->d_wall_h / 2;
	col->d_end = HEIGHT / 2 + col->d_wall_h / 2;
	if (col->d_start < 0)
		col->d_start = 0;
	if (col->d_end >= HEIGHT)
		col->d_end = HEIGHT - 1;
	col->d_wall_x = ray->door_wall_x;
}

void	draw_door_layer(t_game *g, t_column *c)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	pixel;

	tex_x = (int)(c->d_wall_x * g->door_anim_tex->w);
	y = c->d_start;
	while (y < c->d_end)
	{
		tex_y = (y - (HEIGHT / 2 - c->d_wall_h / 2))
			* g->door_anim_tex->h / c->d_wall_h;
		pixel = get_pixel(g->door_anim_tex, tex_x, tex_y);
		if ((unsigned int)pixel != DOOR_ALPHA_KEY)
			put_pixel(&g->frame, c->x, y, pixel);
		y++;
	}
}
