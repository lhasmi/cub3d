/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/22 07:17:16 by gbohm            ###   ########.fr       */
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
			// printf("line in first_last() %s char found in line[%d]: %c\n", line, i, line[i]);//Debug
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

// free_map_exit(map, "Space not adjacent to '1' or space on right side", 1);
// free_map_exit(map, "Invalid character in map", 1);
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
// bool check_space_adjacency(char *row, t_map *map)
// {
// 	int col_index;
// 	int current_row_len;

// 	current_row_len = ft_strlen(row);
// 	(void)map;
// 	col_index = 0;
//     while (col_index < current_row_len)
// 	{
// 		if (row[col_index] == ' ') // spaces must be adjacent to '1's or spaces
// 		{
// 			if (col_index > 0 && !(row[col_index - 1] == '1' || row[col_index - 1] == ' '))
// 			{
// 				printf("Invalid left adjacency at index %d\n", col_index);//Debug
// 				return (false);
// 			}
// 			else if (col_index < current_row_len - 1 && !(row[col_index + 1] == '1' || row[col_index + 1] == ' '))
// 			{
// 				printf("Invalid right adjacency at index %d\n", col_index);//Debug
// 				return (false);
// 			}
// 		}
// 		else
// 		{
// 			if (!is_valid_tile(row[col_index]))
// 			{
// 				printf("Invalid tile at index %d: '%c'\n", col_index, row[col_index]);//Debug
// 				return (false);
// 			}
// 		}
// 		++col_index;
// 	}
// 	return (true);
// }

bool	check_walls(t_map *map)
{
	int		row_index = 0;
	int		start_index = 0;
	char	*current_row;

	while (row_index < map->rows)// Iterate through each row in the map
	{
		current_row = map->tiles[row_index];
		// printf("current_row before trim in row_index %d is : %s\n", row_index, current_row);//Debug
		start_index = trim_leading_ws(current_row);
		// printf("start_index in row_index %d is : %d\n", row_index, start_index);//Debug
		current_row += start_index;// Move the pointer to the first non-whitespace char
		// printf("current_row after advancing pointer of current row in row_index %d is : %s\n", row_index, current_row);//Debug
		if (row_index == 0 || row_index == map->rows - 1)// First and last rows should be validated with is_valid_wall_line
		{
			if (!first_last_line(current_row))
			{
				free_map_exit(map, "First or last row contains invalid characters.", 0);
				// printf("current_row in row_index %d is : %s\n", row_index, current_row);//Debug
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
			else if (!check_space_adjacency(current_row)){
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
				map->tiles[i][j] = '0';
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
		free_map_exit(map, "Wall or tiles check failed.", 1);
	if (!validate_components(map))
		free_map_exit(map, "Components validation failed.", 1);
	return (true);
}
