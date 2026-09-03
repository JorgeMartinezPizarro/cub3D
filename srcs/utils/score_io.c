/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	score_default(t_score *s, char *name)
{
	ft_strlcpy(s->name, name, sizeof(s->name));
	s->hash = 0;
	s->best_ms = 0;
}

static int	score_decode_line(char *hexline, t_score *out)
{
	char	plain[64];
	char	**tok;
	int		len;

	len = ft_strlen(hexline);
	if (len > 0 && hexline[len - 1] == '\n')
		hexline[--len] = '\0';
	len = len / 2;
	if (len <= 0 || len >= 64 || (ft_strlen(hexline) % 2) != 0)
		return (0);
	ft_hex_decode(hexline, plain);
	ft_xor_buf(plain, len, SCORE_XOR_KEY);
	plain[len] = '\0';
	tok = ft_split(plain, ' ');
	if (!tok || !tok[0] || !tok[1] || !tok[2])
		return (free_strarr(tok, 3), 0);
	ft_strlcpy(out->name, tok[0], sizeof(out->name));
	out->hash = ft_atoi(tok[1]);
	out->best_ms = ft_atoi(tok[2]);
	return (free_strarr(tok, 3), 1);
}

static void	score_init_defaults(t_score *scores, char **names)
{
	int	i;

	i = 0;
	while (i < SCORE_MAP_COUNT)
	{
		score_default(&scores[i], names[i]);
		i++;
	}
}

void	ft_load_scores(t_score *scores)
{
	static char	*names[SCORE_MAP_COUNT] = {
		"level1.cub", "level2.cub", "level3.cub", "level4.cub",
		"level5.cub", "level6.cub", "level7.cub", "level8.cub",
		"level9.cub"};
	int			fd;
	char		*line;
	int			i;

	score_init_defaults(scores, names);
	fd = open(SCORES_PATH, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i < SCORE_MAP_COUNT)
			score_decode_line(line, &scores[i]);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_save_scores(t_score *scores)
{
	int		fd;
	int		i;
	char	*hex;

	fd = open(SCORES_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	i = 0;
	while (i < SCORE_MAP_COUNT)
	{
		hex = ft_score_encode(&scores[i]);
		if (hex)
		{
			write(fd, hex, ft_strlen(hex));
			write(fd, "\n", 1);
			free(hex);
		}
		i++;
	}
	close(fd);
}
