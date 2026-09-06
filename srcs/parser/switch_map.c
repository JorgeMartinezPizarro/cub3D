/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*level_path(int idx)
{
	static char	path[32];

	ft_strlcpy(path, "maps/", sizeof(path));
	ft_strlcat(path, ft_level_name(idx), sizeof(path));
	return (path);
}

void	ft_switch_map(t_game *g, int dir)
{
	int	idx;

	idx = g->map_idx;
	if (idx < 0)
		idx = 0;
	idx = (idx + dir + SCORE_MAP_COUNT) % SCORE_MAP_COUNT;
	if (!reload_map(g, level_path(idx)))
		exit_program(g);
}

void	ft_apply_pending_switch(t_game *g)
{
	if (g->pending_switch_dir == 0)
		return ;
	if (get_time() - g->pending_switch_time < MAP_SWITCH_DEBOUNCE_MS)
		return ;
	if (!g->started && !g->finished)
		ft_switch_map(g, g->pending_switch_dir);
	g->pending_switch_dir = 0;
}

void	ft_restart_map(t_game *g)
{
	free(g->win_msg);
	g->win_msg = NULL;
	free(g->score_msg);
	g->score_msg = NULL;
	free(g->record_msg);
	g->record_msg = NULL;
	g->finished = 0;
	g->started = 0;
	if (!reload_map(g, g->map_path))
		exit_program(g);
}

void	ft_return_to_menu(t_game *g)
{
	g->started = 0;
	if (!reload_map(g, g->map_path))
		exit_program(g);
}
