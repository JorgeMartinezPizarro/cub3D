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
	destroy_wall_images(g);
	ft_memset(&g->wall_north, 0, sizeof(t_img));
	ft_memset(&g->wall_south, 0, sizeof(t_img));
	ft_memset(&g->wall_east, 0, sizeof(t_img));
	ft_memset(&g->wall_west, 0, sizeof(t_img));
}

static int	load_wall_textures(t_game *g, t_config *config)
{
	destroy_wall_textures(g);
	return (load_wall_texture_set(g, config));
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
	ft_set_map_messages(g, path, get_time() - t0);
	return (1);
}
