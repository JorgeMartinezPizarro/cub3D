/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:05:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/12 19:47:55 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

void    draw_column(t_game *g, int x, int start, int end, t_img *tex,
	double wall_x, int wall_h)
{
	int y;
	int tex_x = (int)(wall_x * tex->w);
	y = 0;
	while (y < start)
		put_pixel(&g->frame, x, y++, CEILING_COLOR);
	while (y < end)
	{
		int tex_y = (y - (HEIGHT / 2 - wall_h / 2)) * tex->h / wall_h;
		put_pixel(&g->frame, x, y++, get_tex_pixel(tex, tex_x, tex_y));
	}
	while (y < HEIGHT)
		put_pixel(&g->frame, x, y++, FLOOR_COLOR);
}

void	draw_hand_frame(t_game *g, t_img *sheet, int frame_idx)
{
	int			x;
	int			y;
	t_charview	cv;
	int			color;

	cv.tex_x = (frame_idx % 2) * HAND_WIDTH;
	cv.tex_y = (frame_idx / 2) * HAND_HEIGHT;
	cv.screen_x = (WIDTH / 2) - (HAND_WIDTH / 2);
	cv.screen_y = HEIGHT - HAND_HEIGHT + 20;
	y = 0;
	while (y < HAND_HEIGHT)
	{
		x = 0;
		while (x < HAND_WIDTH)
		{
			color = get_tex_pixel(sheet, cv.tex_x + x, cv.tex_y + y);
			if (color != 0x000000 && color > 0)
				put_pixel(&g->frame, cv.screen_x + x, cv.screen_y + y, color);
			x++;
		}
		y++;
	}
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

/* --- HANDLERS DE EVENTOS --- */

int	mouse_move(int x, int y, t_game *g)
{
	(void)y;
	g->mouse_x = x;
	return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double	margin_x;
	double	margin_y;
	int		tile;

	if (get_time() % 7 == 0)
		g->current_hand_frame = (g->current_hand_frame + 1) % 4;
	if (dx > 0)
		margin_x = PLAYER_RADIUS;
	else
		margin_x = -PLAYER_RADIUS;
	if (dy > 0)
		margin_y = PLAYER_RADIUS;
	else
		margin_y = -PLAYER_RADIUS;
	tile = g->world[(int)g->p.y][(int)(g->p.x + dx + margin_x)];
	if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
		g->p.x += dx;
	tile = g->world[(int)(g->p.y + dy + margin_y)][(int)g->p.x];
	if (tile == TILE_EMPTY || tile == TILE_DOOR_OPEN)
		g->p.y += dy;
}

void	apply_movement(t_game *g)
{
	if (g->keys[KEY_W])
		move_player(g, cos(g->p.angle) * MOVE_SPEED,
			sin(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_S])
		move_player(g, -cos(g->p.angle) * MOVE_SPEED,
			-sin(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_A])
		move_player(g, sin(g->p.angle) * MOVE_SPEED,
			-cos(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_D])
		move_player(g, -sin(g->p.angle) * MOVE_SPEED,
			cos(g->p.angle) * MOVE_SPEED);
	if (g->keys[KEY_LEFT])
		g->p.angle -= ROT_SPEED;
	if (g->keys[KEY_RIGHT])
		g->p.angle += ROT_SPEED;
	normalize_angle(&g->p.angle);
}

int	game_loop(t_game *g)
{
	long long	now;
	int			delta_x;

	now = get_time();
	if (now - g->last_time < 1000 / FPS)
		return (0);
	g->last_time = now;
	apply_movement(g);
	if (g->old_mouse_x == 0)
		g->old_mouse_x = g->mouse_x;
	if (g->mouse_x != g->old_mouse_x)
	{
		delta_x = g->mouse_x - g->old_mouse_x;
		if (abs(delta_x) < 200)
		{
			g->p.angle += delta_x * SENSIBILITY;
			normalize_angle(&g->p.angle);
		}
		g->old_mouse_x = g->mouse_x;
	}
	render(g);
	return (0);
}

void	load_tex(t_game *g, t_img *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
	if (!t->img)
		exit((write(2, "Error texture\n", 14), 1));
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
}

int	exit_program(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	free_game(g);
	exit(0);
	return (0);
}

void	load_textures(t_game *g, t_config *config)
{
	load_tex(g, &g->wall_north, config->no_texture);
	load_tex(g, &g->wall_south, config->so_texture);
	load_tex(g, &g->wall_east, config->ea_texture);
	load_tex(g, &g->wall_west, config->we_texture);
	load_tex(g, &g->hand_sheet, "textures/arms.xpm");
	load_tex(g, &g->door_closed, "textures/door_closed.xpm");
	load_tex(g, &g->door_half, "textures/door_half.xpm");
	load_tex(g, &g->door_open, "textures/door_open.xpm");
}

int	load_game(char *filename, t_game *g, t_config *config)
{
	config = ft_parse_cub_file(filename);
	if (!config)
		return (0);
	if (!ft_config_to_game(config, g))
	{
		ft_free_config(config);
		exit_program(g);
		return (0);
	}
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "Cub3D");
	g->p.mouse_x = WIDTH / 2;
	g->p.mouse_y = HEIGHT / 2;
	g->current_hand_frame = 0;
	g->last_time = 0;
	g->frame.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->frame.addr = mlx_get_data_addr(g->frame.img, &g->frame.bpp,
			&g->frame.line, &g->frame.endian);
	load_textures(g, config);
	return (1);
}

void	load_handlers(t_game *g)
{
	mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(g->mlx, g->win);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_hook(g->win, 17, 0, exit_program, g);
	mlx_loop_hook(g->mlx, game_loop, g);
	mlx_loop(g->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	config;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	if (!load_game(argv[1], &game, &config))
		return (1);
	load_handlers(&game);
	ft_free_config(&config);
	return (0);
}

/*

TODO: 

- Después del testeo hemos visto que se gestina el error de textura,
	pero se abre la ventana, no debería.
- Revisar si todos los mensajes de error corresponden
- Mejorar las animaciones de las puertas
- Revisar interaccion de mouse.

*/