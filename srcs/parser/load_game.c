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

int	load_tex(t_game *g, t_img *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
	if (!t->img)
	{
		ft_putstr_fd("Error\nCould not load a texture\n", 2);
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
		|| !load_tex(g, &g->key_sheet, "textures/arms_key.xpm")
		|| !load_tex(g, &g->door_closed, "textures/puerta_cerrada.xpm")
		|| !load_tex(g, &g->door_half, "textures/puerta_entornada.xpm")
		|| !load_tex(g, &g->door_open, "textures/puerta_abierta.xpm")
		|| !load_tex(g, &g->fireworks, "textures/fireworks.xpm")
		|| !load_tex(g, &g->fireworks2, "textures/fireworks2.xpm")
		|| !load_tex(g, &g->key_icon, "textures/key.xpm"))
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
	game->door_x = -1;
	game->key_anim_frame = -1;
}

static int	load_images(t_game *g)
{
	if (!g->mlx)
		return (0);
	g->frame.img = mlx_new_image(g->mlx, g->frame.w, g->frame.h);
	if (!g->frame.img)
		return (0);
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
	g->last_hand_time = get_time();
	init_keys(g);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (ft_free_config(config), 0);
	resolve_win_size(g, &g->frame.w, &g->frame.h);
	g->p.mouse_x = g->frame.w / 2;
	g->p.mouse_y = g->frame.h / 2;
	if (!load_textures(g, config) || !load_images(g) || !load_font(g))
		return (ft_free_config(config), 0);
	g->win = mlx_new_window(g->mlx, g->frame.w, g->frame.h, "Cub3D");
	if (!g->win)
		return (ft_free_config(config), 0);
	ft_free_config(config);
	return (1);
}
