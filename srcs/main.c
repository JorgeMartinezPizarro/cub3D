/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:05:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/02/14 16:41:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

/* --- HANDLERS DE EVENTOS --- */

int	main(int argc, char **argv)
{
	t_game		game;
	t_config	config;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	if (!load_game(argv[1], &game, &config))
		return (1);
	load_handlers(&game);
	ft_free_config(&config);
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