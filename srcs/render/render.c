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

static void	compute_ray(t_game *g, int x, t_ray *ray)
{
	double	fov;

	fov = M_PI / 3.0;
	ray->angle = g->p.angle - fov / 2
		+ (double)x / g->frame.w * fov;
	ray->dist = cast_ray(g, ray);
	ray->cam_dist = ray->dist * cos(ray->angle - g->p.angle);
	if (ray->cam_dist <= 0.1)
		ray->cam_dist = 0.1;
	if (ray->has_door)
		ray->door_cam_dist = ray->door_dist * cos(ray->angle - g->p.angle);
}

static void	setup_column_wall(t_game *g, t_ray *ray, t_column *col,
		t_img **walls)
{
	col->wall_h = (int)(g->frame.h / ray->cam_dist);
	col->start = g->frame.h / 2 - col->wall_h / 2;
	col->end = g->frame.h / 2 + col->wall_h / 2;
	if (col->start < 0)
		col->start = 0;
	if (col->end >= g->frame.h)
		col->end = g->frame.h - 1;
	if (ray->side == 0 || ray->side == 1)
		col->wall_x = ray->hit_x;
	else
		col->wall_x = ray->hit_y;
	col->wall_x -= floor(col->wall_x);
	col->tex = walls[ray->side];
	col->is_door = (ray->hit_type == TILE_DOOR
			|| ray->hit_type == TILE_DOOR_HALF);
	if (ray->hit_type == TILE_DOOR)
		col->tex = &g->door_closed;
	else if (ray->hit_type == TILE_DOOR_HALF)
		col->tex = g->door_anim_tex;
}

static void	setup_column(t_game *g, t_ray *ray, t_column *col)
{
	t_img	*walls[4];

	walls[0] = &g->wall_north;
	walls[1] = &g->wall_south;
	walls[2] = &g->wall_east;
	walls[3] = &g->wall_west;
	if (ray->no_hit)
	{
		col->wall_h = 0;
		col->start = g->frame.h / 2;
		col->end = col->start;
		col->is_door = 0;
		col->wall_x = 0;
		col->tex = walls[0];
		return ;
	}
	setup_column_wall(g, ray, col, walls);
}

static void	draw_column(t_game *g, t_column *c)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	rep;

	rep = WALL_TEX_REPEAT;
	if (c->is_door)
		rep = 1;
	y = 0;
	while (y < c->start)
		put_pixel(&g->frame, c->x, y++, g->ceiling_color);
	tex_x = (int)(c->wall_x * rep * c->tex->w) % c->tex->w;
	y = c->start;
	while (y < c->end)
	{
		tex_y = (y - (g->frame.h / 2 - c->wall_h / 2))
			* c->tex->h * rep / c->wall_h % c->tex->h;
		put_pixel(&g->frame, c->x, y++,
			get_pixel(c->tex, tex_x, tex_y));
	}
	while (y < g->frame.h)
		put_pixel(&g->frame, c->x, y++, g->floor_color);
	if (c->has_door)
		draw_door_layer(g, c);
}

void	render(t_game *g)
{
	int			x;
	t_ray		ray;
	t_column	col;

	if (g->finished)
		return (render_end_screen(g));
	if (!g->started)
		return (render_start_screen(g));
	clear_frame(&g->frame, 0x000000);
	x = 0;
	while (x < g->frame.w)
	{
		col.x = x;
		compute_ray(g, x, &ray);
		setup_column(g, &ray, &col);
		setup_door(g, &ray, &col);
		draw_column(g, &col);
		x++;
	}
	draw_player_hand(g);
	ft_draw_crosshair(g);
	render_minimap(g);
	render_hud(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}
