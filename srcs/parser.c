/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:50:32 by guigonza          #+#    #+#             */
/*   Updated: 2026/02/02 20:25:41 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
void	ft_free_all(char **res, int i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
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
    ft_putstr_fd("Error\nInvalid line\n", 2);
    return (1);
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
		ft_putstr_fd("Error\nMap not found\n", 2);
		free(config);
		return(NULL);
	}
	return(config);
	
}

int	ft_parse_texture(char **texture, int *flag, char *line)
{
	int i;
	int end;

	i = 0;
	if (*flag == 1)
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		return (1);
	}
	while(ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
	{
		ft_putstr_fd("Error\nLine cant be empty\n",2);
		return (1);
	}
	end = i;
	while(line[end] && line[end] != '\n')
		end++;
	*texture = ft_substr(line, i, end - i);
	if (*texture == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
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
	{
		ft_putstr_fd("Error\nDuplicate color\n", 2);
		return (1);
	}
	while (ft_isspace(line[i]))
		i++;
	values = ft_split(line + i, ',');
	if (!values || !*values)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		ft_free_all(values, i);
		return (1);
	}
	count = 0;
	while(values[count])
		count++;
	if (count != 3)
	{
		ft_putstr_fd("Error\nInvalid color value\n", 2);
		ft_free_all(values, count - 1);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_is_valid_nummber(values[i]))
		{
			ft_putstr_fd("Error\nInvalid color value\n", 2);
			ft_free_all(values, count - 1);
			return (1);
		}
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
		{
			ft_putstr_fd("Error\nColor out of range\n", 2);
			ft_free_all(values, i);
			return (1);
		}
		color[i] = num;
		i++;
	}
	ft_free_all(values, i);
	*flag = 1;
	return (0);
}

/*
TODO: implementar ft_addmap_line
TODO: implementar ft_validate_map
TODO: ft_stract_spawn
TODO: ft_free_config
*/