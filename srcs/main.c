/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:05:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/15 14:14:46 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	if (!load_game(argv[1], &game))
	{
		exit_program(&game);
		return (1);
	}
	load_handlers(&game);
	mlx_loop(game.mlx);
	exit_program(&game);
	return (0);
}
/*

TODO: 

- Revisar que la ventana no se carga al fallar el mapa.
- Revisar los mensajes de error.
- Mejorar las animaciones de las puertas.
- Revisar interaccion de mouse.
- Finalizar free_game y free_config.

*/