/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:05:44 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 15:05:53 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_program(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	free_game(g);
	exit(0);
	return (0);
}
