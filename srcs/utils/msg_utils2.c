/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_build_map_message(char *path)
{
	char	buf[512];
	int		i;

	i = 0;
	append_str(buf, &i, "You solved map ");
	append_str(buf, &i, path);
	buf[i] = '\0';
	return (ft_strdup(buf));
}

char	*ft_build_title_message(char *path)
{
	char	*base;
	char	buf[512];
	int		i;

	base = ft_strrchr(path, '/');
	if (base)
		base++;
	else
		base = path;
	i = 0;
	append_str(buf, &i, "<- ");
	append_str(buf, &i, base);
	append_str(buf, &i, " ->");
	buf[i] = '\0';
	return (ft_strdup(buf));
}

char	*ft_build_size_message(t_game *g)
{
	char	buf[128];
	int		i;

	i = 0;
	append_str(buf, &i, "Map size: ");
	append_pad(buf, &i, g->width, 1);
	append_str(buf, &i, " x ");
	append_pad(buf, &i, g->height, 1);
	append_str(buf, &i, "   Doors to open: ");
	append_pad(buf, &i, g->door_total, 1);
	buf[i] = '\0';
	return (ft_strdup(buf));
}

void	ft_set_map_messages(t_game *g, char *path, long long load_ms)
{
	char	*path_copy;

	path_copy = ft_strdup(path);
	g->load_ms = load_ms;
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
