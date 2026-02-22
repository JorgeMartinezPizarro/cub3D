/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:50:12 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/22 14:29:10 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int c)
{
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	*(unsigned int *)(img->addr + y * img->line + x * (img->bpp / 8)) = c;
}
