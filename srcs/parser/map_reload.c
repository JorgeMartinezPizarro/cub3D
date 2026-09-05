/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reload.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_wall_textures(t_game *g)
{
	if (g->wall_north.img)
		mlx_destroy_image(g->mlx, g->wall_north.img);
	if (g->wall_south.img)
		mlx_destroy_image(g->mlx, g->wall_south.img);
	if (g->wall_east.img)
		mlx_destroy_image(g->mlx, g->wall_east.img);
	if (g->wall_west.img)
		mlx_destroy_image(g->mlx, g->wall_west.img);
	ft_memset(&g->wall_north, 0, sizeof(t_img));
	ft_memset(&g->wall_south, 0, sizeof(t_img));
	ft_memset(&g->wall_east, 0, sizeof(t_img));
	ft_memset(&g->wall_west, 0, sizeof(t_img));
}

static int	load_wall_textures(t_game *g, t_config *config)
{
	destroy_wall_textures(g);
	if (!load_tex(g, &g->wall_north, config->no_texture)
		|| !load_tex(g, &g->wall_south, config->so_texture)
		|| !load_tex(g, &g->wall_east, config->ea_texture)
		|| !load_tex(g, &g->wall_west, config->we_texture))
		return (0);
	return (1);
}

static void	reset_run_state(t_game *g)
{
	g->doors_opened = 0;
	g->door_opening = 0;
	g->door_x = -1;
	g->door_y = -1;
	g->door_time = 0;
	g->win_pending = 0;
	g->win_pending_since = 0;
	g->current_hand_frame = 0;
	g->last_hand_time = get_time();
	g->key_anim_frame = -1;
}

static void	rebuild_messages(t_game *g, char *path, long long load_ms)
{
	char	*path_copy;

	path_copy = ft_strdup(path);
	free(g->load_msg);
	g->load_msg = ft_build_load_message(load_ms);
	free(g->map_msg);
	g->map_msg = ft_build_map_message(path);
	free(g->title_msg);
	g->title_msg = ft_build_title_message(path);
	free(g->map_path);
	g->map_path = path_copy;
	g->map_hash = ft_hash_file(g->map_path);
	g->map_idx = ft_find_map_index(g->map_path);
	free(g->size_msg);
	g->size_msg = ft_build_size_message(g);
	free(g->best_msg);
	g->best_msg = ft_build_record_message(g);
}

int	reload_map(t_game *g, char *path)
{
	t_config	*config;
	long long	t0;

	t0 = get_time();
	config = ft_parse_cub_file(path);
	if (!config)
		return (0);
	free_world(g);
	if (!ft_config_to_game(config, g))
		return (ft_free_config(config), 0);
	if (!load_wall_textures(g, config))
		return (ft_free_config(config), 0);
	ft_free_config(config);
	reset_run_state(g);
	rebuild_messages(g, path, get_time() - t0);
	return (1);
}
