/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:00:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/12 19:20:29 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height)
		free(game->world[i++]);
	free(game->world);
}

void	free_strarr(char **res, int i)
{
	int	j;

	j = 0;
	if (!res)
		return ;
	while (j < i && res[j])
		free(res[j++]);
	free(res);
}

void	ft_free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free (config->we_texture);
	if (config->ea_texture)
		free (config->ea_texture);
	if (config->map)
		free_strarr(config->map, 0);
	free (config);
}
