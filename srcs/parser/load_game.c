/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:15:26 by jomarti3          #+#    #+#             */
/*   Updated: 2026/04/09 00:33:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_tex(t_game *g, t_img *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
	if (!t->img)
	{
		ft_putstr_fd("Error loading texture\n", 2);
		return (0);
	}
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
	return (1);
}

static int	load_textures(t_game *g, t_config *config)
{
	if (!load_tex(g, &g->wall_north, config->no_texture)
		|| !load_tex(g, &g->wall_south, config->so_texture)
		|| !load_tex(g, &g->wall_east, config->ea_texture)
		|| !load_tex(g, &g->wall_west, config->we_texture)
		|| !load_tex(g, &g->hand_sheet, "textures/arms.xpm")
		|| !load_tex(g, &g->door_closed, "textures/door_closed.xpm")
		|| !load_tex(g, &g->door_half, "textures/door_half.xpm")
		|| !load_tex(g, &g->door_open, "textures/door_open.xpm"))
		return (0);
	return (1);
}

static void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
}

static int	load_images(t_game *g)
{
	if (!g->mlx)
		return (0);
	g->frame.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->frame.img)
		return (0);
	g->frame.w = WIDTH;
	g->frame.h = HEIGHT;
	g->frame.addr = mlx_get_data_addr(g->frame.img,
			&g->frame.bpp, &g->frame.line, &g->frame.endian);
	return (1);
}

int	load_game(char *filename, t_game *g)
{
	t_config	*config;

	config = ft_parse_cub_file(filename);
	if (!config)
		return (0);
	if (!ft_config_to_game(config, g))
		return (ft_free_config(config), 0);
	g->p.mouse_x = WIDTH / 2;
	g->p.mouse_y = HEIGHT / 2;
	g->current_hand_frame = 0;
	g->mouse_enable = 0;
	g->last_hand_time = get_time();
	g->last_time = 0;
	init_keys(g);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (ft_free_config(config), 0);
	if (!load_textures(g, config) || !load_images(g))
		return (ft_free_config(config), 0);
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!g->win)
		return (ft_free_config(config), 0);
	ft_free_config(config);
	return (1);
}
