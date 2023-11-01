/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:57:11 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/01 21:44:15 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
// The map must be composed of only 6 possible characters: 0 for an empty space,
// 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
// check is a particular x and y position is a wall
// using the mapreqs struct, that was initialized in init.c
int		is_wall(t_map *map, int x, int y)
{
	if (map->tiles[y][x] == '1')
		return (1);
	return (0);
}

// check player in a particular x and y position
// using the mapreqs struct, that was initialized in init.c
int		is_player_pos(t_map *map, int x, int y)
{
	if (map->tiles[y][x] == 'N' || map->tiles[y][x] == 'S' ||
		map->tiles[y][x] == 'E' || map->tiles[y][x] == 'W')
		return (1);
	return (0);
}
// check orientation of the player in a particular x and y position
// using the mapreqs struct, that was initialized in init.c
int    is_player_orientation(t_map *map, int x, int y, char orientation)
{
	if (map->tiles[y][x] == orientation)
		return (1);
	return (0);
}
