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

int	key_press(int k, t_game *g)
{
	if (k == KEY_ESC)
		exit_program(g);
	else if (k == KEY_E)
		ft_toggle_door(g);
	else if (k == KEY_M)
		toggle_mouse(g, !g->mouse_enable);
	else if (k < 65536)
		g->keys[k] = 1;
	return (0);
}

int	key_release(int k, t_game *g)
{
	if (k < 65536)
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
