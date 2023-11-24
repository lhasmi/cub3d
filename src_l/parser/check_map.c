/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 21:26:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	check_wall_line(t_map *map, char *current_row, int row_index)
{
	current_row = current_row + trim_leading_ws(current_row);
	if (row_index == 0 || row_index == map->rows - 1)
	{
		if (!first_last_line(current_row))
		{
			free_map_exit(map, "First/last row has invalid characters.", 0);
			return (false);
		}
	}
	else
	{
		if (!is_valid_middle_line(current_row))
		{
			free_map_exit(map, "Error in middle lines", 0);
			return (false);
		}
		if (!check_space_adjacency(current_row))
		{
			free_map_exit(map, "Space on falsh side", 0);
			return (false);
		}
	}
	return (true);
}

bool	check_walls(t_map *map)
{
	int	row_index;

	row_index = 0;
	while (row_index < map->rows)
	{
		if (!check_wall_line(map, map->tiles[row_index], row_index))
			return (false);
		row_index++;
	}
	return (true);
}

bool	set_player_position(t_map *map, int i, int j, bool *player_found)
{
	if (*player_found)
		return (false);
	*player_found = true;
	map->mapreqs.pos_x = j;
	map->mapreqs.pos_y = i;
	map->mapreqs.orientation = map->tiles[i][j];
	map->tiles[i][j] = '0';
	return (true);
}

bool	validate_components(t_map *map)
{
	int		i;
	int		j;
	bool	player_found;
	int		current_row_len;

	player_found = false;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		current_row_len = ft_strlen(map->tiles[i]);
		while (j < current_row_len)
		{
			if (is_orientation(map->tiles[i][j]))
			{
				if (!set_player_position(map, i, j, &player_found))
					return (false);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (false);
	return (true);
}

bool	map_valid(t_map *map)
{
	if (!map || !map->tiles)
		free_map_exit(map, "Map is NULL", 1);
	if (!check_walls(map))
		free_map_exit(map, "Wall or tiles check failed.", 1);
	if (!validate_components(map))
		free_map_exit(map, "Components validation failed.", 1);
	return (true);
}
