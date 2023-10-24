/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:52:02 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/24 23:13:38 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**allocate_map_d(t_map *map)
{
	char	**map_d;
	size_t	i;

	i = 0;
	map_d = (char **)ft_calloc((map->height + 1), sizeof(char *));
	if (map_d == NULL)
	{
		free_map(map, "Could not allocate memory for map_d");
		return (NULL);
	}
	while (i < map->height)
	{
		map_d[i] = ft_strdup(map->tiles[i]);
		i++;
	}
	map_d[map->height] = NULL;
	return (map_d);
}

void	path_fill(t_map *map, char **map_d, size_t y, size_t x)
{
	if (y >= map->height || x >= map->width)
		return ;
	if (map_d[y][x] != 'F')
	{
		map_d[y][x] = 'F';
		if (x + 1 < map->width)
			path_fill(map, map_d, y, x + 1);
		if (x > 0)
			path_fill(map, map_d, y, x - 1);
		if (y + 1 < map->height)
			path_fill(map, map_d, y + 1, x);
		if (y > 0)
			path_fill(map, map_d, y - 1, x);
	}
}

void	check_blocked_path(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width - 1)
		{
			if ((map->tiles[i][j] == 'P' && map->tiles[i + 1][j] == 'E'
					&& map->tiles[i + 2][j] == 'C') || (map->tiles[i][j] == 'C'
					&& map->tiles[i + 1][j] == 'E' && map->tiles[i
					+ 2][j] == 'P') || (map->tiles[i][j] == 'P'
					&& map->tiles[i][j + 1] == 'E' && map->tiles[i][j
					+ 2] == 'C') || (map->tiles[i][j] == 'C' && map->tiles[i][j
					+ 1] == 'E' && map->tiles[i][j + 2] == 'P'))
				free_map(map,
					"Player is blocked by exit and can't reach the collectible");
			j++;
		}
		i++;
	}
}

void	check_tiles_for_path(t_map *map, char **map_d)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map_d[i][j] && map_d[i][j] != '\n')
		{
			if (map_d[i][j] == 'C' || map_d[i][j] == 'E')
			{
				free_argv(map_d);
				free_map(map, "No valid path");
			}
			j++;
		}
		i++;
	}
	check_blocked_path(map);
}

void	check_path(t_map *map, t_req *pos)
{
	char	**map_d;

	map_d = allocate_map_d(map);
	path_fill(map, map_d, pos->py, pos->px);
	check_tiles_for_path(map, map_d);
	free_argv(map_d);
}
