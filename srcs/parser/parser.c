/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:50:32 by guigonza          #+#    #+#             */
/*   Updated: 2026/04/08 17:12:32 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_errors(t_error err)
{
	static char	*errors[ERR_COUNT] = {
		"Error\nMalloc Failed\n",
		"Error\nInvalid file extension\n",
		"Error\nFile can't be open\n",
		"Error\nDuplicate texture\n",
		"Error\nLine can't be empty\n",
		"Error\nDuplicate color\n",
		"Error\nInvalid color value\n",
		"Error\nColor out of range (0-255)\n",
		"Error\nMissing element\n",
		"Error\nInvalid character in map\n",
		"Error\nInvalid spawn (need exactly one N/S/E/W)\n",
		"Error\nMap not found\n",
		"Error\nMap not closed\n",
		"Error\nInvalid line in file\n",
		"Error\nMap too large (max 100x100)\n"
	};

	if (err >= 0 && err < ERR_COUNT)
		ft_putstr_fd(errors[err], 2);
	return (1);
}

static int	ft_compare_symbols(t_config *config, char *line, int i)
{
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (ft_parse_texture(&config->no_texture, &config->no_flag, line + i
				+ 3));
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (ft_parse_texture(&config->so_texture, &config->so_flag, line + i
				+ 3));
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (ft_parse_texture(&config->we_texture, &config->we_flag, line + i
				+ 3));
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (ft_parse_texture(&config->ea_texture, &config->ea_flag, line + i
				+ 3));
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (ft_parse_color(config->floor, &config->f_flag, line + i + 2));
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (ft_parse_color(config->sky, &config->c_flag, line + i + 2));
	return (-1);
}

static int	ft_parse_line(t_config *config, char *line)
{
	int	i;
	int	result;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	result = ft_compare_symbols(config, line, i);
	if (result != -1)
		return (result);
	if (ft_check_all_flags(config) == 1)
		return (ft_add_map_line(config, line));
	return (ft_print_errors(ERR_INVALID_LINE));
}

static int	ft_process_file(int fd, t_config *config)
{
	char	*line;
	int		res;

	line = get_next_line(fd);
	while (line != NULL)
	{
		res = ft_parse_line(config, line);
		free(line);
		if (res == 1)
			return (drain_fd(fd), 1);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

t_config	*ft_parse_cub_file(char *filename)
{
	int			fd;
	t_config	*config;

	if (ft_check_extension(filename) == 1)
		return (ft_print_errors(ERR_EXTENSION), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_print_errors(ERR_OPEN_FILE), NULL);
	config = ft_init_config();
	if (config == NULL)
	{
		close(fd);
		return (ft_print_errors(ERR_MALLOC), NULL);
	}
	if (ft_process_file(fd, config) == 1)
	{
		close(fd);
		return (ft_free_config(config), NULL);
	}
	close(fd);
	if (ft_validate_config(config) == 1)
		return (ft_free_config(config), NULL);
	return (config);
}
