/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:08:26 by jomarti3          #+#    #+#             */
/*   Updated: 2026/04/06 17:41:35 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

static int	key_press_menu(int k, t_game *g)
{
	if (k == KEY_ESC)
		exit_program(g);
	if (g->finished)
	{
		if (k == KEY_ENTER)
			ft_restart_map(g);
		return (0);
	}
	if ((k == KEY_LEFT || k == KEY_RIGHT)
		&& g->pending_switch_dir == (k == KEY_RIGHT) - (k == KEY_LEFT))
		g->pending_switch_dir = 0;
	if (k == KEY_ENTER)
	{
		g->started = 1;
		g->game_start = get_time();
	}
	return (0);
}

int	key_press(int k, t_game *g)
{
	if (g->finished || !g->started)
		return (key_press_menu(k, g));
	if (k == KEY_ESC)
		exit_program(g);
	else if (k == KEY_BACKSPACE)
		ft_return_to_menu(g);
	else if (k == KEY_E)
	{
		ft_toggle_door(g);
		ft_start_key_anim(g);
	}
	else if (k == KEY_M)
		toggle_mouse(g, !g->mouse_enable);
	else if (k < KEY_TABLE_SIZE)
		g->keys[k] = 1;
	return (0);
}

int	key_release(int k, t_game *g)
{
	if (!g->started && !g->finished && (k == KEY_LEFT || k == KEY_RIGHT))
	{
		g->pending_switch_dir = (k == KEY_RIGHT) - (k == KEY_LEFT);
		g->pending_switch_time = get_time();
	}
	if (k < KEY_TABLE_SIZE)
		g->keys[k] = 0;
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
