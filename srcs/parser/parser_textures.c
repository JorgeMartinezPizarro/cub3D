/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:33:54 by guigonza          #+#    #+#             */
/*   Updated: 2026/04/08 17:16:52 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_validate_color_values(char **values, int *color, int count)
{
	int	i;
	int	num;

	i = 0;
	while (i < 3)
	{
		if (values[i][ft_strlen(values[i]) - 1] == '\n')
			values[i][ft_strlen(values[i]) - 1] = '\0';
		if (!ft_valid_int(values[i]))
			return (free_strarr(values, count), 1);
		num = ft_atoi(values[i]);
		if (num < 0 || num > 255)
			return (free_strarr(values, count), 2);
		color[i] = num;
		i++;
	}
	free_strarr(values, count);
	return (0);
}

int	ft_parse_texture(char **texture, int *flag, char *line)
{
	int	i;
	int	end;

	i = 0;
	if (*flag == 1)
		return (ft_print_errors(ERR_DUP_TEXTURE));
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || (line[i] == '\0' && line[0] == '.'))
	{
		ft_print_errors(ERR_EMPTY_LINE);
		return (0);
	}
	end = i;
	while (line[end] && line[end] != '\n')
		end++;
	*texture = ft_substr(line, i, end - i);
	if (*texture == NULL)
		return (ft_print_errors(ERR_MALLOC));
	*flag = 1;
	return (0);
}

int	ft_parse_color(int *color, int *flag, char *line)
{
	char	**values;
	int		i;
	int		count;
	int		num;

	i = 0;
	if (*flag == 1)
		return (ft_print_errors(ERR_DUP_COLOR));
	while (ft_isspace(line[i]))
		i++;
	values = ft_split(line + i, ',');
	if (!values || !*values)
		return (free_strarr(values, 0), ft_print_errors(ERR_MALLOC));
	count = 0;
	while (values[count])
		count++;
	if (count != 3)
		return (free_strarr(values, count), ft_print_errors(ERR_BAD_COLOR));
	num = ft_validate_color_values(values, color, count);
	if (num == 1)
		return (ft_print_errors(ERR_BAD_COLOR));
	if (num == 2)
		return (ft_print_errors(ERR_COLOR_RANGE));
	*flag = 1;
	return (0);
}
