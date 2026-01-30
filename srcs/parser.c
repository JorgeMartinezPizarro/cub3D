/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:50:32 by guigonza          #+#    #+#             */
/*   Updated: 2026/01/30 13:45:57 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_config	*ft_init_config(void)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return  (NULL);
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->ea_texture = NULL;
	config->we_texture = NULL;
	config->floor[0] = -1;
	config->floor[1] = -1;
	config->floor[2] = -1;
	config->sky[0] = -1;
	config->sky[1] = -1;
	config->sky[2] = -1;
	config->map = NULL;
	config->height = 0;
	config->width = 0;
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
t_config *ft_parse_cub_file(char *filename)
{
	int 		fd;
	char 		*line;
	int			result;
	t_config	*config;

	if (ft_check_extension(filename) == 1)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return(NULL);		
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		perror(filename);
		return (NULL);
	}
	
	config = ft_init_config();
	if (config == NULL)
	{
		ft_putstr_fd("Error\nMalloc failled\n", 2);
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = ft_parse_line(config, line);
		if (result == 1)
		{
			free(line);
			close(fd);
			free(config);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (config->c_flag == 0 || config->f_flag == 0 || config->ea_flag == 0 || config->no_flag == 0 || config->so_flag == 0 || config->we_flag == 0)
	{
		ft_putstr_fd("Error\nMissing element\n", 2);
		free(config);
		return (NULL);
	}
	if (config->map == NULL)
	{
		free(config);
		return(NULL);
	}
	return(config);
	
}