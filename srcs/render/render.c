/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:31:55 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 15:34:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_column(t_game *g, int x, int start, int end, t_img *tex,
	double wall_x, int wall_h)
{
	int y;
	int tex_x = (int)(wall_x * tex->w);
	y = 0;
	while (y < start)
		put_pixel(&g->frame, x, y++, g->ceiling_color);
	while (y < end)
	{
		int tex_y = (y - (HEIGHT / 2 - wall_h / 2)) * tex->h / wall_h;
		put_pixel(&g->frame, x, y++, get_tex_pixel(tex, tex_x, tex_y));
	}
	while (y < HEIGHT)
		put_pixel(&g->frame, x, y++, g->floor_color);
}

void	render(t_game *g)
{
	int     x = 0;
	double  fov = M_PI / 3.0;

	while (x < WIDTH)
	{
		double ray_angle = g->p.angle - fov / 2 + (double)x / WIDTH * fov;
		double hx, hy;
		int side;
		int hit_type;
		double ray_dist = cast_ray(g, ray_angle, &hx, &hy, &side, &hit_type);
		double cam_dist = ray_dist * cos(ray_angle - g->p.angle);
		
		if (cam_dist <= 0.1) cam_dist = 0.1;
		int wall_h = (int)(HEIGHT / cam_dist);
		int start = HEIGHT / 2 - wall_h / 2;
		int end = HEIGHT / 2 + wall_h / 2;

		if (start < 0) start = 0;
		if (end >= HEIGHT) end = HEIGHT - 1;
		t_img *tex;
		double wall_x;
		
		if (side == 0 || side == 1)
			wall_x = hx;
		else
			wall_x = hy;
		if (hit_type == TILE_DOOR)
			tex = &g->door_closed;
		else if (side == 0)
			tex = &g->wall_north;
		else if (side == 1)
			tex = &g->wall_south;
		else if (side == 2)
			tex = &g->wall_east;
		else
			tex = &g->wall_west;
		wall_x -= floor(wall_x);
		draw_column(g, x, start, end, tex, wall_x, wall_h);
		x++;
	}
	draw_hand_frame(g, &g->hand_sheet, g->current_hand_frame);
	render_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}
