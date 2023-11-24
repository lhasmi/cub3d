/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:57:11 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 21:29:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_line_a_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_tile(line[i]) && !is_orientation(line[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

int	is_wall(t_map *map, int x, int y)
{
	if (map->tiles[y][x] == '1')
		return (1);
	return (0);
}

int	is_player_pos(t_map *map, int x, int y)
{
	if (map->tiles[y][x] == 'N' || map->tiles[y][x] == 'S'
		|| map->tiles[y][x] == 'E' || map->tiles[y][x] == 'W')
		return (1);
	return (0);
}

int	is_player_orientation(t_map *map, int x, int y, char orientation)
{
	if (map->tiles[y][x] == orientation)
		return (1);
	return (0);
}

bool	is_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
