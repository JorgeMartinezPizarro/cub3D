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

void	ft_ms_to_clock(long long ms, int *min, int *sec, int *msec)
{
	*min = (int)(ms / 60000);
	*sec = (int)((ms / 1000) % 60);
	*msec = (int)(ms % 1000);
}

void	append_clock(char *buf, int *i, long long ms)
{
	int	min;
	int	sec;
	int	msec;

	ft_ms_to_clock(ms, &min, &sec, &msec);
	append_pad(buf, i, min, 2);
	append_str(buf, i, ":");
	append_pad(buf, i, sec, 2);
	append_str(buf, i, ".");
	append_pad(buf, i, msec, 3);
}

char	*ft_build_load_message(long long load_ms)
{
	char	buf[64];
	int		i;

	i = 0;
	append_str(buf, &i, "Game loaded in ");
	append_clock(buf, &i, load_ms);
	append_str(buf, &i, ".");
	buf[i] = '\0';
	return (ft_strdup(buf));
}
