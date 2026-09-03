/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_start_screen(t_game *g)
{
	char	*l1;
	char	*l2;

	l1 = "Let's open the doors!";
	l2 = "Press any key to start.";
	clear_frame(&g->frame, 0x000000);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	mlx_string_put(g->mlx, g->win, WIDTH / 2 - ft_strlen(l1) * FONT_CHAR_W / 2,
		HEIGHT / 2 - 10, 0x00FFFFFF, l1);
	mlx_string_put(g->mlx, g->win, WIDTH / 2 - ft_strlen(l2) * FONT_CHAR_W / 2,
		HEIGHT / 2 + 10, 0x00FFFFFF, l2);
}
