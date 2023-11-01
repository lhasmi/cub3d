/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/01 21:55:44 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_walls(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (i == 0 || i == map->rows - 1 || j == 0 || j == map->cols - 1)
				free_map_exit(&map_i, "Map is not srrounded by walls", 1);
			j++;
		}
		i++;
	}
}

void validate_components(t_map *map) 
{
    int i;
	int j;
    bool player_found = false;
	
	i = 0;
    while( i < map->rows) 
	{
		j = 0;
        while ( j < map->cols) 
		{
            if (!is_valid_tile(map->tiles[i][j]))
                ft_error("Invalid tile detected on the map.");
            if (is_orientation(map->tiles[i][j]))
				{
                if (player_found)
                    ft_error("Multiple player start positions detected.");
                player_found = true;
                map->mapreqs.pos_x = j;
                map->mapreqs.pos_y = i;
                map->mapreqs.orientation = map->tiles[i][j];
				printf("map->mapreqs.orientation: %c\n", map->mapreqs.orientation);// DEBUG
				assert(map->mapreqs.orientation == 'N' || map->mapreqs.orientation == 'S' ||
				map->mapreqs.orientation == 'E' || map->mapreqs.orientation == 'W');// DEBUG
				printf("map->mapreqs.orientation: %c\n", map->mapreqs.orientation);// DEBUG
            	}
			j++;
        }
		i++;
    }
    if (!player_found) {
        ft_error("No player start position detected.");
    }
}

bool is_orientation(char c) 
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool is_valid_tile(char c) 
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}



bool map_valid(t_map *map) 
{
    if (!map || !map->tiles) 
        ft_error("Map data is not initialized.");
    check_walls(map);
    validate_components(map);
    return true;
}
