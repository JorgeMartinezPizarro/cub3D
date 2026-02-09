/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:50:32 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/09 21:16:47 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_print_errors(t_error err)
{
	static char *msg[] = {
	
		"Error\nMalloc Failed\n",
		"Error\nInvalid file extension\n",
		"Error\nFile can´t be open\n",
		"Error\nDuplicate texture\n",
		"Error\nLine can´t be empty\n",
		"Error\nDuplicate color\n",
		"Error\nColor out of range (0-255)\n",
		"Error\nMissing element\n",
		"Error\nInvaled character in map\n",
		"Error\nMap not closed\n",
		"Error\nInvalid spawn (need exactly one N/S/E/W)\n",
		"Error\nMap not found\n",
		"Error\nInvalid line in file\n"
	};
	if (err >= 0 && err < ERR_COUNT)
		ft_putstr_fd(msg[err], 2);
	return (1);
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
    if (config->no_flag && config->so_flag && config->we_flag
        && config->ea_flag && config->f_flag && config->c_flag)
        return (1);
    return (0);
}

t_config	*ft_inicialize_up_down(t_config *config)
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
		return  (NULL);
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
int	ft_parse_line(t_config *config, char *line)
{
    int	i;

    i = 0;
    while (line[i] && ft_isspace(line[i]))
        i++;
    if (line[i] == '\n' || line[i] == '\0')
        return (0);
    if (ft_strncmp(&line[i], "NO ", 3) == 0)
        return (ft_parse_texture(&config->no_texture, &config->no_flag, line + i + 3));
    if (ft_strncmp(&line[i], "SO ", 3) == 0)
        return (ft_parse_texture(&config->so_texture, &config->so_flag, line + i + 3));
    if (ft_strncmp(&line[i], "WE ", 3) == 0)
        return (ft_parse_texture(&config->we_texture, &config->we_flag, line + i + 3));
    if (ft_strncmp(&line[i], "EA ", 3) == 0)
        return (ft_parse_texture(&config->ea_texture, &config->ea_flag, line + i + 3));
    if (ft_strncmp(&line[i], "F ", 2) == 0)
        return (ft_parse_color(config->floor, &config->f_flag, line + i + 2));
    if (ft_strncmp(&line[i], "C ", 2) == 0)
        return (ft_parse_color(config->sky, &config->c_flag, line + i + 2));
    if (ft_check_all_flags(config) == 1)
        return (ft_add_map_line(config, line));
    ft_print_errors(ERR_INVALID_LINE);
    return (1);
}

int ft_process_file(int fd, t_config *config)
{
	char	*line;
	int		res;
	
	line = get_next_line(fd);
	while (line != NULL)
	{
		res = ft_parse_line(config, line);
		free (line);
		if (res == 1)
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}
int ft_validate_config(t_config *config)
{
	if (ft_check_all_flags(config) == 0)
		return (ft_print_errors(ERR_MISSING_ELEMENT));
	if (config->map == NULL || ft_validate_map(config))
		return (ft_print_errors(ERR_MALLOC));
	return (0);
}
t_config *ft_parse_cub_file(char *filename)
{
	int 		fd;
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
		close (fd);
		return (ft_free_config(config), NULL);
	}
	close (fd);
	if (ft_validate_config(config) == 1)
		return (ft_validate_config(config), NULL);
	return(config);
}

int	ft_parse_texture(char **texture, int *flag, char *line)
{
	int i;
	int end;

	i = 0;
	if (*flag == 1)
		return(ft_print_errors(ERR_DUP_TEXTURE));
	while(ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (ft_print_errors(ERR_EMPTY_LINE));
	end = i;
	while(line[end] && line[end] != '\n')
		end++;
	*texture = ft_substr(line, i, end - i);
	if (*texture == NULL)
		return (ft_print_errors(ERR_MALLOC));
	*flag = 1;
	return (0); 
}
int ft_is_valid_nummber(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i]  == '\0' || str[i] == '\n')
		return(0);
	while (str[i] && str[i] != '\n' && !ft_isspace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
	
}
int ft_parse_color(int *color, int *flag, char *line)
{
	char **values;
	int i;
	int count;
	int num;

	i = 0;
	if(*flag == 1)
		return (ft_print_errors(ERR_DUP_COLOR));
	while (ft_isspace(line[i]))
		i++;
	values = ft_split(line + i, ',');
	if (!values || !*values)
		return (free_strarr(values, i), ft_print_errors(ERR_MALLOC));
	count = 0;
	while(values[count])
		count++;
	if (count != 3)
		return (free_strarr(values, count -1), ft_print_errors(ERR_INVALID_COLOR));
	i = 0;
	while (i < 3)
	{
		if (!ft_is_valid_nummber(values[i]))
			return (free_strarr(values, count -1), ft_print_errors(ERR_INVALID_COLOR));
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_strarr(values, i), ft_print_errors(ERR_COLOR_RANGE));
		color[i] = num;
		i++;
	}
	free_strarr(values, i);
	*flag = 1;
	return (0);
}
int ft_add_map_line(t_config *config, char *line)
{
	int 	len;
	char 	*new_line;
	char	**new_map;
	int		i;
	
	len = 0;
	while (line[len] && line[len] != '\n')
	len++;
	new_line = ft_substr(line, 0, len);
	if (!new_line)
		return (ft_print_errors(ERR_MALLOC));
	new_map = malloc((config->height + 2) * sizeof(char *));
	if (!new_map)
		return (free(new_line), ft_print_errors(ERR_MALLOC));
	i = 0;
	while (i < config->height)
	{
		new_map[i] = config->map[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i+ 1] = NULL;
	if (config->map != NULL)
		free(config->map);
	config->map = new_map;
	config->height++;
	if (len > config->width)
	config->width = len;
	return (0);
}
int ft_is_border_or_space(t_config *config, int x, int y)
{
	int len;
	
	if (x == 0 || y == 0)
	return (1);
	if (y >= config->height -1)
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
void ft_set_spawn(t_config *config, int x, int y, char c)
{
	config->x_spawn = x;
	config->y_spawn = y;
	if (c == 'N')
		config->spawn_angle = -M_PI / 2;
	else if (c == 'S')
		config->spawn_angle = M_PI / 2;
	else if (c == 'E')
		config->spawn_angle = 0;
	else if (c == 'W')
		config->spawn_angle = M_PI;
}
int ft_check_cell(t_config *config, int x, int y, int *spawn_count)
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
int ft_validate_map(t_config *config)
{
	int spawn_count;
	int x;
	int y;
	
	y = 0;
	spawn_count = 0;
	while(y < config->height)
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

int	ft_config_to_game(t_config *config, t_game *game)
{
	int y;
	int x;
	int len;

	game->width = config->width;
	game->height = config->height;
	game->world = malloc(sizeof(int *) * config->height);
	if (!game->world)
		return (0);
	y = 0;
	while (y < config->height)
	{
		game->world[y] = malloc(sizeof(int) * config->width);
		if (!game->world[y])
		{
			game->height = y;
			free_game(game);
			return (0);
		}
		x = 0;
		 len = ft_strlen(config->map[y]);
		while (x < config->width)
		{
			if (x < len && config->map[y][x] == '1')
				game->world[y][x] = 1;
			else
				game->world[y][x] = 0;
			x++;
		}
		y++;
	}
	game->p.x = config->x_spawn + 0.5;
	game->p.y = config->y_spawn + 0.5;
	game->p.angle = config->spawn_angle;
	return (1);
}
