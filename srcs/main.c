/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:05:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/03/12 21:12:04 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

static void	build_messages(t_game *game, char *path, long long load_ms)
{
	game->load_ms = load_ms;
	game->load_msg = ft_build_load_message(load_ms);
	game->map_msg = ft_build_map_message(path);
	game->map_path = path;
	game->map_hash = ft_hash_file(path);
	game->size_msg = ft_build_size_message(game);
	game->best_msg = ft_build_record_message(game);
}

int	main(int argc, char **argv)
{
	t_game		game;
	long long	t0;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	t0 = get_time();
	if (!load_game(argv[1], &game))
	{
		exit_program(&game);
		return (1);
	}
	build_messages(&game, argv[1], get_time() - t0);
	load_handlers(&game);
	mlx_loop(game.mlx);
	exit_program(&game);
	return (0);
}
