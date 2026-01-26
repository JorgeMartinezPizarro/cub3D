/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:44:19 by jomarti3          #+#    #+#             */
/*   Updated: 2026/01/26 11:53:33 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define TEX 64

#define KEY_W 119
#define KEY_S 115
#define KEY_A 100
#define KEY_D 97
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define PLAYER_RADIUS 0.2
#define MOVE_SPEED 0.2
#define ROT_SPEED  0.1

#define FLOOR_COLOR 0x444444   // gris oscuro
#define CEILING_COLOR 0xAAAAAA // gris claro

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
	t_player	p;
}	t_game;

int world[9][9] = {
	{1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1},
};

void	put_pixel(t_img *img, int x, int y, int c)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	*(unsigned int *)(img->addr + y * img->line + x * 4) = c;
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	return (*(unsigned int *)(tex->addr + y * tex->line + x * 4));
}

/* cast_ray devuelve también side: 0=vertical, 1=horizontal */
double  cast_ray(t_player *p, double angle,
				 double *hitx, double *hity, int *side)
{
	double  raydir_x = cos(angle);
	double  raydir_y = sin(angle);

	int map_x = (int)p->x;
	int map_y = (int)p->y;

	double  delta_dist_x = fabs(1.0 / raydir_x);
	double  delta_dist_y = fabs(1.0 / raydir_y);

	double  side_dist_x;
	double  side_dist_y;

	int step_x;
	int step_y;
	int hit = 0;
	int dda_side; // 0 = vertical, 1 = horizontal

	if (raydir_x < 0)
	{
		step_x = -1;
		side_dist_x = (p->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - p->x) * delta_dist_x;
	}

	if (raydir_y < 0)
	{
		step_y = -1;
		side_dist_y = (p->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - p->y) * delta_dist_y;
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
		if (world[map_y][map_x] == 1)
			hit = 1;
	}

	double perp_dist;

	if (dda_side == 0)
		perp_dist = (map_x - p->x + (1 - step_x) / 2) / raydir_x;
	else
		perp_dist = (map_y - p->y + (1 - step_y) / 2) / raydir_y;

	*hitx = p->x + perp_dist * raydir_x;
	*hity = p->y + perp_dist * raydir_y;

	if (dda_side == 0)
		*side = (raydir_x > 0) ? 2 : 3; // E / W
	else
		*side = (raydir_y > 0) ? 1 : 0; // S / N

	return (perp_dist);
}

void	render(t_game *g)
{
	double	fov = M_PI / 3.0;

	for (int x = 0; x < WIDTH; x++)
	{
		double	ray_angle = g->p.angle - fov / 2
			+ (double)x / WIDTH * fov;

		double	hx, hy;
		int		side;
		double	dist = cast_ray(&g->p, ray_angle, &hx, &hy, &side);
		dist *= cos(ray_angle - g->p.angle);

		int	wall_h = (int)(HEIGHT / dist);
		int	start = HEIGHT / 2 - wall_h / 2;
		int	end   = HEIGHT / 2 + wall_h / 2;

		if (start < 0)
			start = 0;
		if (end >= HEIGHT)
			end = HEIGHT;

		t_img *tex;
		if (side == 0)
			tex = &g->wall_north;
		else if (side == 1)
			tex = &g->wall_south;
		else if (side == 2)
			tex = &g->wall_east;
		else
			tex = &g->wall_west;

		double wall_x;

		if (side == 0 || side == 1)
			wall_x = hx;
		else
			wall_x = hy;

		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * TEX);

		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= TEX)
			tex_x = TEX - 1;

		/* ceiling */
		for (int y = 0; y < start; y++)
			put_pixel(&g->frame, x, y, CEILING_COLOR);

		/* wall */
		for (int y = start; y < end; y++)
		{
			int tex_y = (y - start) * TEX / wall_h;
			int color = get_tex_pixel(tex, tex_x, tex_y);
			put_pixel(&g->frame, x, y, color);
		}

		/* floor */
		for (int y = end; y < HEIGHT; y++)
			put_pixel(&g->frame, x, y, FLOOR_COLOR);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

int mouse_move(int x, int y, t_game *g)
{
	static int last_x = -1;
	double sensitivity = 0.004;
	int dx;

	(void)y;

	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}

	dx = x - last_x;

	/* IGNORA saltos grandes (salir / entrar de ventana) */
	if (dx > 100 || dx < -100)
	{
		last_x = x;
		return (0);
	}

	g->p.angle += dx * sensitivity;
	last_x = x;

	render(g);
	return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double nx = g->p.x + dx;
	double ny = g->p.y + dy;

	/* eje X */
	if (world[(int)g->p.y]
		[(int)(nx + (dx > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))] == 0)
		g->p.x = nx;

	/* eje Y */
	if (world[(int)(ny + (dy > 0 ? PLAYER_RADIUS : -PLAYER_RADIUS))]
		[(int)g->p.x] == 0)
		g->p.y = ny;
}

/* Movimientos relativos a la dirección de la cámara */
int	key(int k, t_game *g)
{
	if (k == KEY_ESC)
		exit(0);

	if (k == KEY_LEFT)
		g->p.angle -= ROT_SPEED;
	if (k == KEY_RIGHT)
		g->p.angle += ROT_SPEED;

	if (k == KEY_W)
		move_player(g,
			cos(g->p.angle) * MOVE_SPEED,
			sin(g->p.angle) * MOVE_SPEED);

	if (k == KEY_S)
		move_player(g,
			-cos(g->p.angle) * MOVE_SPEED,
			-sin(g->p.angle) * MOVE_SPEED);

	if (k == KEY_A)
		move_player(g,
			-sin(g->p.angle) * MOVE_SPEED,
			cos(g->p.angle) * MOVE_SPEED);

	if (k == KEY_D)
		move_player(g,
			sin(g->p.angle) * MOVE_SPEED,
			-cos(g->p.angle) * MOVE_SPEED);

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
	load_tex(g, &g->wall_east,  "textures/wall_east.xpm");
	load_tex(g, &g->wall_west,  "textures/wall_west.xpm");
}

int	main(void)
{
	t_game	g;

	g.mlx = mlx_init();
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Cub3D");
	g.frame.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	g.frame.addr = mlx_get_data_addr(
		g.frame.img, &g.frame.bpp, &g.frame.line, &g.frame.endian);

	load_textures(&g);

	g.p.x = 4.5;
	g.p.y = 7.5;
	g.p.angle = -M_PI / 2;

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

*/