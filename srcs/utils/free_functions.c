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

void	destroy_wall_images(t_game *game)
{
	if (game->wall_north.img)
		mlx_destroy_image(game->mlx, game->wall_north.img);
	if (game->wall_south.img)
		mlx_destroy_image(game->mlx, game->wall_south.img);
	if (game->wall_east.img)
		mlx_destroy_image(game->mlx, game->wall_east.img);
	if (game->wall_west.img)
		mlx_destroy_image(game->mlx, game->wall_west.img);
}

static void	free_images(t_game *game)
{
	if (game->hand_sheet.img)
		mlx_destroy_image(game->mlx, game->hand_sheet.img);
	if (game->key_sheet.img)
		mlx_destroy_image(game->mlx, game->key_sheet.img);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	destroy_wall_images(game);
}

static void	free_door_images(t_game *game)
{
	if (game->door_open.img)
		mlx_destroy_image(game->mlx, game->door_open.img);
	if (game->door_half.img)
		mlx_destroy_image(game->mlx, game->door_half.img);
	if (game->door_closed.img)
		mlx_destroy_image(game->mlx, game->door_closed.img);
	if (game->fireworks.img)
		mlx_destroy_image(game->mlx, game->fireworks.img);
	if (game->fireworks2.img)
		mlx_destroy_image(game->mlx, game->fireworks2.img);
	if (game->key_icon.img)
		mlx_destroy_image(game->mlx, game->key_icon.img);
}

static void	close_window(t_game *game)
{
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free(game->win_msg);
	free(game->load_msg);
	free(game->map_msg);
	free(game->title_msg);
	free(game->score_msg);
	free(game->record_msg);
	free(game->size_msg);
	free(game->best_msg);
	free(game->map_path);
	free_world(game);
	if (game->mlx)
	{
		free_images(game);
		free_door_images(game);
		free_font(game);
		close_window(game);
	}
}
