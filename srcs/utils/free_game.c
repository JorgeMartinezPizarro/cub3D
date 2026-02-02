/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:00:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/02 16:07:27 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(game->world[i]);
		i++;
	}
	free(game->world);
}
