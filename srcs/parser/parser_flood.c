/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 00:00:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/03 00:00:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_visited(int **visited, int rows)
{
	int	y;

	y = 0;
	while (y < rows)
		free(visited[y++]);
	free(visited);
}

static int	**ft_alloc_visited(t_game *g)
{
	int	**visited;
	int	y;

	visited = malloc(sizeof(int *) * g->height);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < g->height)
	{
		visited[y] = malloc(sizeof(int) * g->width);
		if (!visited[y])
			return (ft_free_visited(visited, y), NULL);
		ft_memset(visited[y], 0, sizeof(int) * g->width);
		y++;
	}
	return (visited);
}

static int	ft_flood_count(t_game *g, int x, int y)
{
	int	count;
	int	tile;

	if (x < 0 || x >= g->width || y < 0 || y >= g->height)
		return (0);
	if (g->flood_visited[y][x] || g->world[y][x] == TILE_WALL)
		return (0);
	g->flood_visited[y][x] = 1;
	tile = g->world[y][x];
	count = (tile == TILE_DOOR);
	count += ft_flood_count(g, x + 1, y);
	count += ft_flood_count(g, x - 1, y);
	count += ft_flood_count(g, x, y + 1);
	count += ft_flood_count(g, x, y - 1);
	return (count);
}

int	ft_check_doors_reachable(t_config *config, t_game *game)
{
	int	reached;

	game->flood_visited = ft_alloc_visited(game);
	if (!game->flood_visited)
		return (ft_print_errors(ERR_MALLOC), 0);
	reached = ft_flood_count(game, (int)config->x_spawn, (int)config->y_spawn);
	ft_free_visited(game->flood_visited, game->height);
	game->flood_visited = NULL;
	if (reached != game->door_total)
		return (ft_print_errors(ERR_DOOR_UNREACHABLE), 0);
	return (1);
}
