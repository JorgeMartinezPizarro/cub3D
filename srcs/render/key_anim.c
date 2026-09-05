/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_anim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/05 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_start_key_anim(t_game *g)
{
	g->key_anim_frame = 0;
	g->key_anim_time = get_time();
}

void	ft_update_key_anim(t_game *g)
{
	if (g->key_anim_frame < 0)
		return ;
	if (get_time() - g->key_anim_time >= 75)
	{
		g->key_anim_frame++;
		g->key_anim_time = get_time();
		if (g->key_anim_frame >= 4)
			g->key_anim_frame = -1;
	}
}
