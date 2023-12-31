/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/25 19:36:21 by gbohm            ###   ########.fr       */
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
		return (ft_error("Map is NULL"), false);
	if (map->colorf_found != 1 || map->colorc_found != 1
		|| map->textur_no_found != 1 || map->textur_so_found != 1
		|| map->textur_we_found != 1 || map->textur_ea_found != 1)
		return (ft_error("Invalid number of textures or colors params"),
			false);
	if (!check_walls(map))
		return (ft_error("Wall or tiles check failed."), false);
	if (!validate_components(map))
		return (ft_error("Components validation failed."), false);
	return (true);
}
