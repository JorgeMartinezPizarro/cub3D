/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_codec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_hash_file(char *path)
{
	int				fd;
	char			*line;
	unsigned int	hash;
	int				i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	hash = 5381;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i])
			hash = hash * 33 + (unsigned char)line[i++];
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (hash & 0x7FFFFFFF);
}

void	ft_xor_buf(char *buf, int len, int key)
{
	int	i;

	i = 0;
	while (i < len)
	{
		buf[i] = buf[i] ^ key;
		i++;
	}
}

char	*ft_hex_encode(char *buf, int len)
{
	static char	hex[] = "0123456789abcdef";
	char		*out;
	int			i;

	out = malloc(len * 2 + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i * 2] = hex[(unsigned char)buf[i] / 16];
		out[i * 2 + 1] = hex[(unsigned char)buf[i] % 16];
		i++;
	}
	out[len * 2] = '\0';
	return (out);
}

int	ft_hex_decode(char *hex, char *out)
{
	int	i;
	int	len;
	int	hi;
	int	lo;

	len = ft_strlen(hex) / 2;
	i = 0;
	while (i < len)
	{
		hi = hex[i * 2];
		lo = hex[i * 2 + 1];
		if (hi >= 'a')
			hi = hi - 'a' + 10;
		else
			hi = hi - '0';
		if (lo >= 'a')
			lo = lo - 'a' + 10;
		else
			lo = lo - '0';
		out[i] = (char)(hi * 16 + lo);
		i++;
	}
	return (len);
}

char	*ft_score_encode(t_score *s)
{
	char	plain[64];
	int		i;

	i = 0;
	append_str(plain, &i, s->name);
	append_str(plain, &i, " ");
	append_pad(plain, &i, s->hash, 1);
	append_str(plain, &i, " ");
	append_pad(plain, &i, s->best_ms, 1);
	ft_xor_buf(plain, i, SCORE_XOR_KEY);
	return (ft_hex_encode(plain, i));
}
