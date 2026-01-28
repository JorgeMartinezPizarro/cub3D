/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:44:19 by jomarti3          #+#    #+#             */
/*   Updated: 2026/01/28 15:41:38 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdlib.h>

// Ejemplo hardcodeado de mapa. Reemplazar por leer de fichero.
// Falta agregar a las variables globales:
// - height, width, leer el angulo y la posicion inicial del player.
// Load map from file. Move to separate file. Validate the map.
int **load_map(void) {
    int template[30][30] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int **world = malloc(30 * sizeof(int *));
    if (!world) return NULL;

    for (int i = 0; i < 30; i++) {
        world[i] = malloc(30 * sizeof(int));
        if (!world[i]) {
            // liberar memoria ya asignada en caso de error
            for (int j = 0; j < i; j++) free(world[j]);
            free(world);
            return NULL;
        }
        for (int j = 0; j < 30; j++) {
            world[i][j] = template[i][j];
        }
    }

    return world;
}


void	put_pixel(t_img *img, int x, int y, int c)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	*(unsigned int *)(img->addr + y * img->line + x * 4) = c;
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

    /* Coordenadas exactas del impacto */
    *hitx = g->p.x + perp_dist * raydir_x;
    *hity = g->p.y + perp_dist * raydir_y;

    if (dda_side == 0)
        *side = (raydir_x > 0) ? 2 : 3; // E / W
    else
        *side = (raydir_y > 0) ? 1 : 0; // S / N

    return (perp_dist);
}

void	draw_column(t_game *g, int x, int start, int end, t_img *tex, double wall_x, int wall_h)
{
	int	y;

	int	tex_x = (int)(wall_x * TEX);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEX)
		tex_x = TEX - 1;

	y = 0;
	while (y < start)
	{
		put_pixel(&g->frame, x, y, CEILING_COLOR);
		y++;
	}
	while (y < end)
	{
		int	tex_y = (y - start) * TEX / wall_h;
		int	color = get_tex_pixel(tex, tex_x, tex_y);
		put_pixel(&g->frame, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(&g->frame, x, y, FLOOR_COLOR);
		y++;
	}
}

void	render(t_game *g)
{
	int		x;
	double	fov = M_PI / 3.0;

	x = 0;
	while (x < WIDTH)
	{
		double	ray_angle = g->p.angle - fov / 2 + (double)x / WIDTH * fov;
		double	hx, hy;
		int		side;
		double	dist = cast_ray(g, ray_angle, &hx, &hy, &side);
		dist *= cos(ray_angle - g->p.angle);

		int		wall_h = (int)(HEIGHT / dist);
		int		start = HEIGHT / 2 - wall_h / 2;
		int		end = HEIGHT / 2 + wall_h / 2;
		if (start < 0)
			start = 0;
		if (end >= HEIGHT)
			end = HEIGHT - 1;

		t_img	*tex;
		double	wall_x;

		/* corregimos wall_x según side */
		if (side == 0) // N
		{
			tex = &g->wall_north;
			wall_x = g->p.x + dist * cos(ray_angle);
		}
		else if (side == 1) // S
		{
			tex = &g->wall_south;
			wall_x = g->p.x + dist * cos(ray_angle);
		}
		else if (side == 2) // E
		{
			tex = &g->wall_east;
			wall_x = g->p.y + dist * sin(ray_angle);
		}
		else // W
		{
			tex = &g->wall_west;
			wall_x = g->p.y + dist * sin(ray_angle);
		}

		wall_x -= floor(wall_x);

		draw_column(g, x, start, end, tex, wall_x, wall_h);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

int	mouse_move(int x, int y, t_game *g)
{
	static int last_x = -1;
	double	sens = 0.004;
	int	dx;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	if (dx > 100 || dx < -100)
	{
		last_x = x;
		return (0);
	}
	g->p.angle += dx * sens;
	last_x = x;
	render(g);
	return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double	nx = g->p.x + dx;
	double	ny = g->p.y + dy;
	if (g->world[(int)g->p.y][(int)(nx + (dx > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))] == 0)
		g->p.x = nx;
	if (g->world[(int)(ny + (dy > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))][(int)g->p.x] == 0)
		g->p.y = ny;
}

int	key(int k, t_game *g)
{
	if (k == KEY_ESC)
		exit(0);
	if (k == KEY_LEFT)
		g->p.angle -= ROT_SPEED;
	if (k == KEY_RIGHT)
		g->p.angle += ROT_SPEED;
	if (k == KEY_W)
		move_player(g, cos(g->p.angle) * MOVE_SPEED, sin(g->p.angle) * MOVE_SPEED);
	if (k == KEY_S)
		move_player(g, -cos(g->p.angle) * MOVE_SPEED, -sin(g->p.angle) * MOVE_SPEED);
	if (k == KEY_A)
		move_player(g, -sin(g->p.angle) * MOVE_SPEED, cos(g->p.angle) * MOVE_SPEED);
	if (k == KEY_D)
		move_player(g, sin(g->p.angle) * MOVE_SPEED, -cos(g->p.angle) * MOVE_SPEED);
	render(g);
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
	g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp, &g.frame.line, &g.frame.endian);
	g.world = load_map();
	load_textures(&g);

	g.p.x = 1.5;
	g.p.y = 1.5;
	g.p.angle = -M_PI / 3;

	render(&g);
	mlx_hook(g.win, 2, 1L << 0, key, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop(g.mlx);
}

/*

TODO

- add doors
- add animated sprite
- add minimap
- load map from file (validation from solong)
- refactor norm
- move defines to header
- free on exit, check valgrind
- fix mouse camera movement

*/
