/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:21:01 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/11 17:28:00 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_validate_config(t_config *config)
{
	if (ft_check_all_flags(config) == 0)
		return (ft_print_errors(ERR_MISSING_ELEMENT));
	if (config->map == NULL)
		return (ft_print_errors(ERR_MAP_NOT_FOUND));
	if (ft_validate_map(config) == 1)
		return (1);
	return (0);
}

int	ft_check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (1);
	return (0);
}

int	ft_check_all_flags(t_config *config)
{
	if (config->no_flag && config->so_flag && config->we_flag && config->ea_flag
		&& config->f_flag && config->c_flag)
		return (1);
	return (0);
}

static t_config	*ft_inicialize_up_down(t_config *config)
{
	config->floor[0] = -1;
	config->floor[1] = -1;
	config->floor[2] = -1;
	config->sky[0] = -1;
	config->sky[1] = -1;
	config->sky[2] = -1;
	return (config);
}

t_config	*ft_init_config(void)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->ea_texture = NULL;
	config->we_texture = NULL;
	config->map = NULL;
	config->height = 0;
	config->width = 0;
	ft_inicialize_up_down(config);
	config->x_spawn = -1;
	config->y_spawn = -1;
	config->spawn_angle = -1;
	config->no_flag = 0;
	config->so_flag = 0;
	config->we_flag = 0;
	config->ea_flag = 0;
	config->f_flag = 0;
	config->c_flag = 0;
	return (config);
}
