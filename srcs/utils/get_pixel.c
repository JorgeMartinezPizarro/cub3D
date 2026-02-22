/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:18:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/22 15:18:51 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(t_img *tex, int x, int y)
{
	if (x < 0 || x >= tex->w || y < 0 || y >= tex->h)
		return (0);
	return (*(unsigned int *)(tex->addr + y * tex->line + x * (tex->bpp / 8)));
}
