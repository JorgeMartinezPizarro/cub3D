/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:47:57 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/02 18:54:39 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_minimap(t_game *g)
{
    int x;
    int y;
    int radius = 15;

    // Dibujamos un área relativa al jugador
    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            int map_x = (int)g->p.x + x;
            int map_y = (int)g->p.y + y;
            int color = 0x000000; // Fondo fuera del mapa o vacío

            // Solo dibujamos si estamos dentro de los límites del array world
            if (map_x >= 0 && map_x < g->width && map_y >= 0 && map_y < g->height)
            {
                if (g->world[map_y][map_x] == 1)
                    color = COLOR_WALL;
                else
                    color = COLOR_EMPTY;
            }

            // Dibujamos cada casilla del minimapa
            int py = 0;
            while (py < MM_SCALE)
            {
                int px = 0;
                while (px < MM_SCALE)
                {
                    put_pixel(&g->frame, 
                        MM_OFFSET_X + (x + radius) * MM_SCALE + px,
                        MM_OFFSET_Y + (y + radius) * MM_SCALE + py, 
                        color);
                    px++;
                }
                py++;
            }
            x++;
        }
        y++;
    }
    // Jugador siempre en el centro del minimapa local
    int p_size = 4;
    for (int i = -p_size/2; i < p_size/2; i++)
        for (int j = -p_size/2; j < p_size/2; j++)
            put_pixel(&g->frame, 
                MM_OFFSET_X + radius * MM_SCALE + i, 
                MM_OFFSET_Y + radius * MM_SCALE + j, 
                COLOR_PLAYER);
}