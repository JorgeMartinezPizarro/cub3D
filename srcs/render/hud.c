/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_digits(int n)
{
	int	c;

	c = 1;
	n /= 10;
	while (n > 0)
	{
		c++;
		n /= 10;
	}
	return (c);
}

static void	draw_digit(t_game *g, int n, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < HUD_DIGIT_SIZE)
	{
		j = 0;
		while (j < HUD_DIGIT_SIZE)
		{
			color = get_pixel(&g->digits[n], i * g->digits[n].w
					/ HUD_DIGIT_SIZE, j * g->digits[n].h / HUD_DIGIT_SIZE);
			if (color != 0x00FFFFFF)
				put_pixel(&g->frame, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static int	draw_number(t_game *g, int n, int x, int y)
{
	int	digits;
	int	i;

	digits = count_digits(n);
	i = digits - 1;
	while (i >= 0)
	{
		draw_digit(g, n % 10, x + i * HUD_DIGIT_SIZE, y);
		n /= 10;
		i--;
	}
	return (x + digits * HUD_DIGIT_SIZE);
}

static void	draw_panel(t_game *g, int x, int y, int w)
{
	int	rx;
	int	ry;

	ry = y - HUD_PAD;
	while (ry < y + HUD_DIGIT_SIZE + HUD_PAD)
	{
		rx = x - HUD_PAD;
		while (rx < x + w + HUD_PAD)
			put_pixel(&g->frame, rx++, ry, 0x00FFFFFF);
		ry++;
	}
}

void	render_hud(t_game *g)
{
	int	x;
	int	total;
	int	i;

	total = count_digits(g->doors_opened) + 1 + count_digits(g->door_total);
	x = WIDTH - 10 - total * HUD_DIGIT_SIZE;
	draw_panel(g, x, 10, total * HUD_DIGIT_SIZE);
	x = draw_number(g, g->doors_opened, x, 10);
	i = 0;
	while (i < HUD_DIGIT_SIZE)
	{
		put_pixel(&g->frame, x + i, 10 + HUD_DIGIT_SIZE - 1 - i, 0x00000000);
		i++;
	}
	draw_number(g, g->door_total, x + HUD_DIGIT_SIZE, 10);
}
