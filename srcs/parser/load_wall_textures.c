/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/06 00:00:00 by jomarti3         ###   ########.fr       */
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

int	load_wall_texture_set(t_game *g, t_config *config)
{
	if (!load_tex(g, &g->wall_north, config->no_texture)
		|| !load_tex(g, &g->wall_south, config->so_texture)
		|| !load_tex(g, &g->wall_east, config->ea_texture)
		|| !load_tex(g, &g->wall_west, config->we_texture))
		return (0);
	return (1);
}
