/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:28:07 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/11 19:18:41 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_toggle_door(t_game *g)
{
	int	map_x;
	int	map_y;
	
	map_x = (int)(g->p.x + cos(g->p.angle) * 1.5);
	map_y = (int)(g->p.y + sin(g->p.angle) * 1.5);
	if (map_x < 0 || map_x >= g->width || map_y < 0 || map_y >= g->height)
		return ;
	if (g->world[map_y][map_x] == TILE_DOOR)
		g->world[map_y][map_x] = TILE_DOOR_OPEN;
	else if (g->world[map_y][map_x] == TILE_DOOR_OPEN)
		g->world[map_y][map_x] = TILE_DOOR; 
}
