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
