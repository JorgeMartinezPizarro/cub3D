/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:00:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/04 20:34:20 by guigonza         ###   ########.fr       */
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

void	free_strarr(char **res, int i)
{
	
	int j;
	
	(void)i;
	j = 0;
	if (!res)
		return ;
	while (res[j])
		free(res[j++]);
	free(res);
}
void ft_free_config(t_config *config)
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
/*He cambiado esta función para que recorra hasta NULL*/