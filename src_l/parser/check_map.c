/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 17:51:20 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
/*
1- No empty lines inside the map (only at the end)
2- No characters except 0 1 N S E W and spaces
3- No missing walls (1s) on the borders
4- Map must be the last element of the .cub file
5- Spaces can be present anywhere outside the map
6- Spaces can be inside the map and up to me to decide what to do with them
7- All error messages must be prefixed by "Error\n"
*/
bool	is_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || is_orientation(c) || c == ' ' || c == 'D');
}

bool	first_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool is_valid_middle_line(char *line)
{
	int	i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	if (len > 0 && (line[0] != '1' || line[len - 1] != '1'))
	{
		ft_error("Middle rows must start and end with '1'.");
		return (false);
	}
	while (line[i])
	{
		if (!is_valid_tile(line[i]) )
		{
			ft_error("Invalid tile in middle line");
			return (false);
		}
		i++;
	}
	return (true);
}

int		trim_leading_ws(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

bool check_space_adjacency(char *row)
{
    int len = ft_strlen(row);
	int i = 0;
    while ( i < len)
	{
        if (row[i] == ' ' && i > 0 && i < len - 1 &&
            !(row[i - 1] == '1' || row[i - 1] == ' ' || row[i + 1] == '1' || row[i + 1] == ' ' ||
			row[i + 1] == '0' || row[i - 1] == '0' || is_orientation(row[i + 1]) ||
			is_orientation(row[i - 1])))
		{
            return (false);
        }
		i++;
    }
    return (true);
}

bool check_wall_line (t_map *map, char *current_row, int row_index)
{
	current_row = current_row + trim_leading_ws(current_row);
	if (row_index == 0 || row_index == map->rows - 1)
	{
		if (!first_last_line(current_row))
		{
			free_map_exit(map, "First or last row contains invalid characters.", 0);
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
			free_map_exit(map, "Space not adjacent to '1' or space on right side", 0);
			return (false);
		}
	}
	return (true);
}

bool	check_walls(t_map *map)
{
	int		row_index;

	row_index = 0;
	while (row_index < map->rows)
	{
		if (!check_wall_line(map, map->tiles[row_index], row_index))
            return (false);
		row_index++;
	}
	return (true);
}

bool set_player_position(t_map *map, int i, int j, bool *player_found)
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
	if(!check_walls(map))
		free_map_exit(map, "Wall or tiles check failed.", 1);
	if (!validate_components(map))
		free_map_exit(map, "Components validation failed.", 1);
	return (true);
}
			// printf("current_row in row_index %d is : %s\n", row_index, current_row);//Debug
	// printf("current_row before trim in row_index %d is : %s\n", row_index, current_row);//Debug
	// printf("start_index in row_index %d is : %d\n", row_index, start_index);//Debug
	// printf("current_row after advancing pointer of current row in row_index %d is : %s\n", row_index, current_row);//Debug
