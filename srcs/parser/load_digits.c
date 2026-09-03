/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_digits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one_digit(t_game *g, int i)
{
	char	path[15];
	t_img	*d;

	ft_memcpy(path, "textures/0.xpm", 15);
	path[9] = '0' + i;
	d = &g->digits[i];
	d->img = mlx_xpm_file_to_image(g->mlx, path, &d->w, &d->h);
	if (!d->img)
		return (0);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line, &d->endian);
	return (1);
}

int	load_digits(t_game *g)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (!load_one_digit(g, i))
			return (0);
		i++;
	}
	return (1);
}

void	free_digits(t_game *g)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (g->digits[i].img)
			mlx_destroy_image(g->mlx, g->digits[i].img);
		i++;
	}
}
