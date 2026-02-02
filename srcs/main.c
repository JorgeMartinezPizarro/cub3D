/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:44:19 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/02 15:23:47 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void free_map(int **map)
{
	for (int i = 0; i < 30; i++)
		free(map[i]);
	free(map);
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	return (*(unsigned int *)(tex->addr + y * tex->line + x * 4));
}

/* cast_ray devuelve también side: 0=vertical, 1=horizontal */
double cast_ray(t_game *g, double angle,
				double *hitx, double *hity, int *side)
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
	int dda_side; // 0 = vertical, 1 = horizontal

	if (raydir_x < 0)
	{
		step_x = -1;
		side_dist_x = (g->p.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - g->p.x) * delta_dist_x;
	}

	if (raydir_y < 0)
	{
		step_y = -1;
		side_dist_y = (g->p.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - g->p.y) * delta_dist_y;
	}

	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			dda_side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			dda_side = 1;
		}
		if (g->world[map_y][map_x] == 1)
			hit = 1;
	}

	double perp_dist;

	if (dda_side == 0)
		perp_dist = (map_x - g->p.x + (1 - step_x) / 2) / raydir_x;
	else
		perp_dist = (map_y - g->p.y + (1 - step_y) / 2) / raydir_y;

	*hitx = g->p.x + perp_dist * raydir_x;
	*hity = g->p.y + perp_dist * raydir_y;

	if (dda_side == 0)
		*side = (raydir_x > 0) ? 2 : 3; // E / W
	else
		*side = (raydir_y > 0) ? 1 : 0; // S / N

	return (perp_dist);
}

void	draw_column(t_game *g, int x, int start, int end,
				t_img *tex, double wall_x, int wall_h)
{
	int	y;
	int	tex_x = (int)(wall_x * TEX);

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX)
		tex_x = TEX - 1;

	y = 0;
	while (y < start)
		put_pixel(&g->frame, x, y++, CEILING_COLOR);

	while (y < end)
	{
		int tex_y = (y - start) * TEX / wall_h;
		int color = get_tex_pixel(tex, tex_x, tex_y);
		put_pixel(&g->frame, x, y++, color);
	}

	while (y < HEIGHT)
		put_pixel(&g->frame, x, y++, FLOOR_COLOR);
}

void	render(t_game *g)
{
	int		x;
	double	fov;
	
	fov = M_PI / 3.0;
	x = 0;

	while (x < WIDTH)
	{
		double	ray_angle = g->p.angle - fov / 2
			+ (double)x / WIDTH * fov;

		double	hx, hy;
		int		side;

		double	ray_dist = cast_ray(g, ray_angle, &hx, &hy, &side);
		double	cam_dist = ray_dist * cos(ray_angle - g->p.angle);

		if (cam_dist <= 0.0001)
			cam_dist = 0.0001;

		int wall_h = (int)(HEIGHT / cam_dist);

		int	start = HEIGHT / 2 - wall_h / 2;
		int	end = HEIGHT / 2 + wall_h / 2;

		if (start < 0)
			start = 0;
		if (end >= HEIGHT)
			end = HEIGHT - 1;

		t_img	*tex;
		double	wall_x;

		if (side == 0 || side == 1)
		{
			tex = (side == 0) ? &g->wall_north : &g->wall_south;
			wall_x = hx;
		}
		else
		{
			tex = (side == 2) ? &g->wall_east : &g->wall_west;
			wall_x = hy;
		}

		wall_x -= floor(wall_x);
		draw_column(g, x, start, end, tex, wall_x, wall_h);
		x++;
	}

	render_minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
}

int	game_loop(t_game *g)
{
	render(g);
	return (0);
}

int mouse_move(int x, int y, t_game *g)
{
	(void)y;

	g->mouse_dx += (x - WIDTH / 2);
	return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double	nx = g->p.x + dx;
	double	ny = g->p.y + dy;

	if (g->world[(int)g->p.y]
		[(int)(nx + (dx > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))] == 0)
		g->p.x = nx;
	if (g->world[(int)(ny + (dy > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))]
		[(int)g->p.x] == 0)
		g->p.y = ny;
}

int	key(int k, t_game *g)
{
	if (k == KEY_ESC)
	{
		free_map(g->world);
		exit(0);
	}
	if (k == KEY_LEFT)
		g->p.angle -= ROT_SPEED;
	else if (k == KEY_RIGHT)
		g->p.angle += ROT_SPEED;
	else if (k == KEY_W)
		move_player(g, cos(g->p.angle) * MOVE_SPEED,
			sin(g->p.angle) * MOVE_SPEED);
	else if (k == KEY_S)
		move_player(g, -cos(g->p.angle) * MOVE_SPEED,
			-sin(g->p.angle) * MOVE_SPEED);
	else if (k == KEY_A)
		move_player(g, -sin(g->p.angle) * MOVE_SPEED,
			cos(g->p.angle) * MOVE_SPEED);
	else if (k == KEY_D)
		move_player(g, sin(g->p.angle) * MOVE_SPEED,
			-cos(g->p.angle) * MOVE_SPEED);
	return (0);
}

void	load_tex(t_game *g, t_img *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
}

void	load_textures(t_game *g)
{
	load_tex(g, &g->wall_north, "textures/wall_north.xpm");
	load_tex(g, &g->wall_south, "textures/wall_south.xpm");
	load_tex(g, &g->wall_east, "textures/wall_east.xpm");
	load_tex(g, &g->wall_west, "textures/wall_west.xpm");
}

int	main(void)
{
	t_game	g;

	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Cub3D");
	
	g.frame.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	g.frame.addr = mlx_get_data_addr(g.frame.img,
		&g.frame.bpp, &g.frame.line, &g.frame.endian);

	if (!load_map("", &g))
		return (1);

	load_textures(&g);

	mlx_hook(g.win, 2, 1L << 0, key, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	
	mlx_loop(g.mlx);
	return (0);
}

/*
TODO (BONUS)
- add doors
- add animated arms (sprite)
- add minimap
- load map from file (validation from solong)
- refactor norm
- free on exit, check valgrind
- fix mouse camera movement (too fast, it beaks on fast movements)
*/