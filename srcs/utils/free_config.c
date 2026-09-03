/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_world(t_game *game)
{
	int	i;

	if (!game->world)
		return ;
	i = 0;
	while (i < game->height)
		free(game->world[i++]);
	free(game->world);
	game->world = NULL;
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
	ft_printf("Clean up config.\n");
	if (!config)
		return ;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
		free(config->ea_texture);
	free_strarr(config->map, config->height);
	free(config);
}
