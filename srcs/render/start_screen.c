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
	char	*l2;
	char	*l3;

	l2 = "Let's open all those dammit doors!";
	l3 = "Press any key to start.";
	clear_frame(&g->frame, 0x000000);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	put_centered(g, HEIGHT / 2 - 30, g->load_msg);
	put_centered(g, HEIGHT / 2, l2);
	put_centered(g, HEIGHT / 2 + 30, l3);
}
