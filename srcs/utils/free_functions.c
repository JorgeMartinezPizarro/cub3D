/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:00:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/15 15:55:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_image(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx, img->img);
}

static void	free_images(t_game *game)
{
	if (game->hand_sheet.img)
		free_image(game, &game->hand_sheet);
	if (game->frame.img)
		free_image(game, &game->frame);
	if (game->wall_north.img)
		free_image(game, &game->wall_north);
	if (game->wall_south.img)
		free_image(game, &game->wall_south);
	if (game->wall_east.img)
		free_image(game, &game->wall_east);
	if (game->wall_west.img)
		free_image(game, &game->wall_west);
	if (game->door_open.img)
		free_image(game, &game->door_open);
	if (game->door_half.img)
		free_image(game, &game->door_half);
	if (game->door_closed.img)
		free_image(game, &game->door_closed);
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->world)
	{
		i = 0;
		while (i < game->height)
			free(game->world[i++]);
		free(game->world);
	}
	if (game->mlx)
		free_images(game);
	if (game->mlx && game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
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
