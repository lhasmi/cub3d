/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/09 19:57:41 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || is_orientation(c) || c == ' ');
}

bool	first_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			printf("line in first last tfou %s   line[%d]: %c\n", line, i, line[i]);
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
		return (false);
	while (line[i])
	{
		if (!is_valid_tile(line[i]) )
			return (false);
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

// free_map_exit(map, "Space not adjacent to '1' or space on right side", 1);
// free_map_exit(map, "Invalid character in map", 1);
bool check_space_adjacency(char *row, t_map *map) 
{
	int col_index;
	int current_row_len;

	current_row_len = ft_strlen(row);
	(void)map;
	col_index = 0;
    while (col_index < current_row_len)
	{
        if (row[col_index] == ' ') // spaces must be adjacent to '1's or spaces
		{
            if (col_index > 0 && !(row[col_index - 1] == '1' || row[col_index - 1] == ' '))
			{
				printf("Invalid left adjacency at index %d\n", col_index);
				return (false);
			}
            else if (col_index < current_row_len - 1 && !(row[col_index + 1] == '1' || row[col_index + 1] == ' '))
			{
				printf("Invalid right adjacency at index %d\n", col_index);
				return (false);
			}
        }
		else 
		{
            if (!is_valid_tile(row[col_index])){
				printf("Invalid tile at index %d: '%c'\n", col_index, row[col_index]);
				return (false);
			}
        }
		++col_index;
    }
    return (true);
}

bool	check_walls(t_map *map)
{
	int		row_index = 0;
	int		start_index = 0;
	char	*current_row;

	while (row_index < map->rows)// Iterate through each row in the map
	{
		current_row = map->tiles[row_index];
		start_index = trim_leading_ws(current_row);
		current_row += start_index;// Move the pointer to the first non-whitespace char
		if (row_index == 0 || row_index == map->rows - 1)// First and last rows should be validated with is_valid_wall_line
		{
			if (!first_last_line(current_row)){
				free_map_exit(map, "First or last row contains invalid characters.", 0);
				return (false);
			}
		}
		else
		{
			if (!is_valid_middle_line(current_row)){
				free_map_exit(map, "Middle rows must start and end with '1'.", 0);
				return (false);
			}
			else if (!check_space_adjacency(current_row, map)){
				free_map_exit(map, "Space not adjacent to '1' or space on right side", 0);
				return (false);
			}
		}
		row_index++;
	}
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
				if (player_found)
					return (false);
					// free_map_exit(map,
					// 	"Multiple player start positions detected.", 1);
				player_found = true;
				map->mapreqs.pos_x = j;
				map->mapreqs.pos_y = i;
				map->mapreqs.orientation = map->tiles[i][j];
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		return (false);
		// free_map_exit(map, "No player start position detected.", 1);
	return (true);
}

bool	map_valid(t_map *map)
{
	if (!map || !map->tiles)
		free_map_exit(map, "Map is NULL", 1);
	if(!check_walls(map))
		free_map_exit(map, "Wall or tiles check failed", 1);
	if (!validate_components(map))
		free_map_exit(map, "Components validation failed", 1);
	return (true);
}
