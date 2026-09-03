/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	append_str(char *buf, int *i, char *s)
{
	while (*s)
		buf[(*i)++] = *s++;
}

void	append_pad(char *buf, int *i, int n, int width)
{
	char	tmp[16];
	int		len;

	len = 0;
	if (n == 0)
		tmp[len++] = '0';
	while (n > 0)
	{
		tmp[len++] = '0' + n % 10;
		n /= 10;
	}
	while (len < width)
		tmp[len++] = '0';
	while (len > 0)
		buf[(*i)++] = tmp[--len];
}

char	*ft_build_load_message(long long load_ms)
{
	char	buf[64];
	int		i;
	int		min;
	int		sec;

	min = (int)(load_ms / 60000);
	sec = (int)((load_ms / 1000) % 60);
	i = 0;
	append_str(buf, &i, "Game loaded in ");
	append_pad(buf, &i, min, 2);
	append_str(buf, &i, ":");
	append_pad(buf, &i, sec, 2);
	append_str(buf, &i, ".");
	append_pad(buf, &i, (int)(load_ms % 1000), 3);
	append_str(buf, &i, ".");
	buf[i] = '\0';
	return (ft_strdup(buf));
}

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
