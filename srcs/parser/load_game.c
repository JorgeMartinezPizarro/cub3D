/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:26:51 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 15:29:11 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_tex(t_game *g, t_img *t, char *path)
{
	t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
	if (!t->img)
		exit((write(2, "Error texture\n", 14), 1));
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
}

static void	load_textures(t_game *g, t_config *config)
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
