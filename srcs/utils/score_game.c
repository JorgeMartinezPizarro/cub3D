/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_level_name(int idx)
{
	static char	*names[SCORE_MAP_COUNT] = {
		"level1.cub", "level2.cub", "level3.cub", "level4.cub",
		"level5.cub", "level6.cub", "level7.cub", "level8.cub",
		"level9.cub"};

	if (idx < 0 || idx >= SCORE_MAP_COUNT)
		return (NULL);
	return (names[idx]);
}

int	ft_find_map_index(char *path)
{
	char	*base;
	int		i;

	base = ft_strrchr(path, '/');
	if (base)
		base++;
	else
		base = path;
	i = 0;
	while (i < SCORE_MAP_COUNT)
	{
		if (ft_strcmp(base, ft_level_name(i)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*build_time_msg(char *prefix, long long ms)
{
	char	buf[64];
	int		i;
	int		min;
	int		sec;
	int		msec;

	ft_ms_to_clock(ms, &min, &sec, &msec);
	i = 0;
	append_str(buf, &i, prefix);
	append_clock(buf, &i, min, sec, msec);
	buf[i] = '\0';
	return (ft_strdup(buf));
}

void	ft_check_score(t_game *g, long long elapsed)
{
	t_score	scores[SCORE_MAP_COUNT];
	int		idx;

	g->score_msg = NULL;
	g->record_msg = NULL;
	idx = ft_find_map_index(g->map_path);
	if (idx < 0)
		return ;
	ft_load_scores(scores);
	if (scores[idx].hash != g->map_hash || scores[idx].best_ms == 0
		|| elapsed < scores[idx].best_ms)
	{
		scores[idx].hash = g->map_hash;
		scores[idx].best_ms = (int)elapsed;
		ft_save_scores(scores);
		g->record_msg = build_time_msg("New record! Time: ", elapsed);
	}
	g->score_msg = build_time_msg("Best time: ", scores[idx].best_ms);
}

char	*ft_build_record_message(t_game *g)
{
	t_score	scores[SCORE_MAP_COUNT];
	int		idx;

	idx = ft_find_map_index(g->map_path);
	if (idx < 0)
		return (ft_strdup("No record: map not recognized."));
	ft_load_scores(scores);
	if (scores[idx].hash != g->map_hash || scores[idx].best_ms == 0)
		return (ft_strdup("No record yet for this map."));
	return (build_time_msg("Current record: ", scores[idx].best_ms));
}
