/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:31:55 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/22 15:18:51 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_frame(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel(img, x++, y, color);
		y++;
	}
}

static void	compute_ray(t_game *g, int x, t_ray *ray)
{
	double	fov;

	fov = M_PI / 3.0;
	ray->angle = g->p.angle - fov / 2
		+ (double)x / WIDTH * fov;
	ray->dist = cast_ray(g, ray);
	ray->cam_dist = ray->dist * cos(ray->angle - g->p.angle);
	if (ray->cam_dist <= 0.1)
		ray->cam_dist = 0.1;
}

static void	setup_column(t_game *g, t_ray *ray, t_column *col)
{
	col->wall_h = (int)(HEIGHT / ray->cam_dist);
	col->start = HEIGHT / 2 - col->wall_h / 2;
	col->end = HEIGHT / 2 + col->wall_h / 2;
	if (col->start < 0)
		col->start = 0;
	if (col->end >= HEIGHT)
		col->end = HEIGHT - 1;
	if (ray->side == 0 || ray->side == 1)
		col->wall_x = ray->hit_x;
	else
		col->wall_x = ray->hit_y;
	col->wall_x -= floor(col->wall_x);
	if (ray->hit_type == TILE_DOOR)
		col->tex = &g->door_closed;
	else if (ray->hit_type == TILE_DOOR_HALF)
		col->tex = &g->door_half;
	else if (ray->side == 0)
		col->tex = &g->wall_north;
	else if (ray->side == 1)
		col->tex = &g->wall_south;
	else if (ray->side == 2)
		col->tex = &g->wall_east;
	else
		col->tex = &g->wall_west;
}

static void	draw_column(t_game *g, t_column *c)
{
	int	y;
	int	tex_x;
	int	tex_y;

	y = 0;
	while (y < c->start)
		put_pixel(&g->frame, c->x, y++, g->ceiling_color);
	tex_x = (int)(c->wall_x * c->tex->w);
	y = c->start;
	while (y < c->end)
	{
		tex_y = (y - (HEIGHT / 2 - c->wall_h / 2))
			* c->tex->h / c->wall_h;
		put_pixel(&g->frame, c->x, y++,
			get_pixel(c->tex, tex_x, tex_y));
	}
	while (y < HEIGHT)
		put_pixel(&g->frame, c->x, y++, g->floor_color);
}

void	render(t_game *g)
{
	int			x;
	t_ray		ray;
	t_column	col;

	clear_frame(&g->frame, 0x000000);
	x = 0;
	while (x < WIDTH)
	{
		col.x = x;
		compute_ray(g, x, &ray);
		setup_column(g, &ray, &col);
		draw_column(g, &col);
		x++;
	}
	draw_hand_frame(g, &g->hand_sheet, g->current_hand_frame);
	ft_draw_crosshair(g);
	render_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}
