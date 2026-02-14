/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:00:45 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 19:21:27 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_border_or_space(t_config *config, int x, int y)
{
	int	len;

	if (x == 0 || y == 0)
		return (1);
	if (y >= config->height - 1)
		return (1);
	len = ft_strlen(config->map[y]);
	if (x >= len - 1)
		return (1);
	if (config->map[y][x + 1] == '\0' || config->map[y][x + 1] == ' ')
		return (1);
	if (config->map[y][x - 1] == ' ')
		return (1);
	if ((int)ft_strlen(config->map[y - 1]) <= x || config->map[y - 1][x] == ' ')
		return (1);
	if ((int)ft_strlen(config->map[y + 1]) <= x || config->map[y + 1][x] == ' ')
		return (1);
	return (0);
}

static char	**ft_create_new_map(t_config *config, char *new_line)
{
	char	**new_map;
	int		i;

	new_map = malloc((config->height + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < config->height)
	{
		new_map[i] = config->map[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	return (new_map);
}

int	ft_check_cell(t_config *config, int x, int y, int *spawn_count)
{
	char	c;

	c = config->map[y][x];
	if (!ft_strchr("01NSEWD ", c))
		return (ft_print_errors(ERR_INVALID_CHAR));
	if (c == '0' || ft_strchr("NSEWD", c))
	{
		if (ft_is_border_or_space(config, x, y))
			return (ft_print_errors(ERR_MAP_NOT_CLOSED));
	}
	if (ft_strchr("NSEW", c))
	{
		(*spawn_count)++;
		ft_set_spawn(config, x, y, c);
	}
	return (0);
}

int	ft_validate_map(t_config *config)
{
	int	spawn_count;
	int	x;
	int	y;

	y = 0;
	spawn_count = 0;
	while (y < config->height)
	{
		x = 0;
		while (config->map[y][x])
		{
			if (ft_check_cell(config, x, y, &spawn_count) == 1)
				return (1);
			x++;
		}
		y++;
	}
	if (spawn_count != 1)
		return (ft_print_errors(ERR_INVALID_SPAWN));
	return (0);
}

int	ft_add_map_line(t_config *config, char *line)
{
	int		len;
	char	*new_line;
	char	**new_map;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		return (ft_print_errors(ERR_MALLOC));
	new_map = ft_create_new_map(config, new_line);
	if (!new_map)
		return (free(new_line), ft_print_errors(ERR_MALLOC));
	if (config->map != NULL)
		free(config->map);
	config->map = new_map;
	config->height++;
	if (len > config->width)
		config->width = len;
	return (0);
}
