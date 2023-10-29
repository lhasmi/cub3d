/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/30 00:14:53 by lhasmi           ###   ########.fr       */
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
    size_t i;
	size_t j;
    bool player_found = false;

    for (i = 0; i < map->rows; i++) 
	{
        for (j = 0; j < map->cols; j++) 
		{
            if (!is_valid_tile(map->tiles[i][j]))
                ft_error("Invalid tile detected on the map.");
            if (map->tiles[i][j] == 'N' || map->tiles[i][j] == 'S' ||
                map->tiles[i][j] == 'E' || map->tiles[i][j] == 'W') {
                if (player_found)
                    ft_error("Multiple player start positions detected.");
                player_found = true;
                // Set player position and orientation.
                map->mapreqs.pos_x = j;
                map->mapreqs.pos_y = i;
                map->mapreqs.orientation = map->tiles[i][j];
            }
        }
    }
    if (!player_found) {
        ft_error("No player start position detected.");
    }
}

bool is_valid_tile(char c) 
{
    return c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W';
}

bool	check_additional_conditions(t_map *map_i)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map_i->height)
	{
		j = 0;
		while (j < map_i->width)
		{
			if (ft_strchr("01CEP", map_i->tiles[i][j]) == NULL)
				return (false);
			j++;
		}
		i++;
	}
	if (map_i->tiles[0][0] != '1' || map_i->tiles[0][map_i->width - 1] != '1'
		|| map_i->tiles[map_i->height - 1][0] != '1'
		|| map_i->tiles[map_i->height - 1][map_i->width - 1] != '1')
		return (false);
	if (map_i->height < 3 || map_i->width < 3)
		return (false);
	return (true);
}

bool map_valid(t_map *map) 
{
    if (!map || !map->tiles) 
	{
        ft_error("Map data is not initialized.");
    }
    check_walls(map);
    validate_components(map);
    return true;
}

// int main() {
//     t_map map;
//     // Assume map is already populated with the parsed .cub data.
//     // For testing, you would set up the map structure with test data.

//     if (map_valid(&map)) {
//         printf("Map is valid!\n");
//     } else {
//         printf("Map is invalid!\n");
//     }
//     return 0;
// }