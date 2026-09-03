/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_font.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_font(t_game *g)
{
	t_img	*f;

	f = &g->font;
	f->img = mlx_xpm_file_to_image(g->mlx, FONT_PATH, &f->w, &f->h);
	if (!f->img)
		return (0);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line, &f->endian);
	return (1);
}

void	free_font(t_game *g)
{
	if (g->font.img)
		mlx_destroy_image(g->mlx, g->font.img);
}
