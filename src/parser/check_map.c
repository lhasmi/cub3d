/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/05 18:38:16 by lhasmi           ###   ########.fr       */
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

bool	is_valid_wall_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
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
		return false;
	while (line[i])
	{
		if (!is_valid_tile(line[i]) )
			return (false);
		i++;
	}
	return (true);
}

int		trim_leading_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

void	check_walls(t_map *map)
{
	int row_index = 0;
	int col_index = 0;
	int current_row;

	while (row_index >= 0 && row_index < map->rows)// Iterate through each row in the map
	{
		current_row = map->tiles[row_index];
		current_row = trim_leading_whitespaces(current_row);// Ignore leading whitespaces
		if (row_index == 0 || row_index == map->rows - 1)// First and last rows should be validated with is_valid_wall_line
		{
			if (!is_valid_wall_line(current_row))
				free_map_exit(map, "First or last row contains invalid characters.", 1);
		}
		else // Middle rows 	: First and last character of a middle row must be '1'
		{
			if (!is_valid_middle_line(current_row))
				free_map_exit(map, "Middle rows must start and end with '1'.", 1);
			while (col_index >= 0 && col_index < map->cols)
			{
				if (current_row[col_index] == ' ')// Non-leading spaces must be adjacent to '1's or spaces
				{
					if (!(current_row[col_index - 1] == '1' || current_row[col_index - 1] == ' '))
						free_map_exit(map, "Space not adjacent to '1' or space on left side", 1);
					if (!(current_row[col_index + 1] == '1' || current_row[col_index + 1] == ' '))
						free_map_exit(map, "Space not adjacent to '1' or space on right side", 1);
				}
				else// Check for valid tiles
				{
					if (!is_valid_tile(current_row[col_index]))
						free_map_exit(map, "Invalid character in map", 1);
				}
				col_index++;
			}
		}
		row_index++;
	}
	return (true);
}

void	validate_components(t_map *map)
{
	int		i;
	int		j;
	bool	player_found;

	player_found = false;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (!is_valid_tile(map->tiles[i][j]))
				ft_error("Invalid tile detected on the map.");
			if (is_orientation(map->tiles[i][j]))
			{
				if (player_found)
					free_map_exit(map,
						"Multiple player start positions detected.", 1);
				player_found = true;
				map->mapreqs.pos_x = j;
				map->mapreqs.pos_y = i;
				map->mapreqs.orientation = map->tiles[i][j];
				printf("map->mapreqs.orientation: %c\n",
					map->mapreqs.orientation);// DEBUG
				assert(is_orientation(map->mapreqs.orientation)); // DEBUG
				printf("map->mapreqs.orientation: %c\n",
					map->mapreqs.orientation);// DEBUG
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		free_map_exit(map, "No player start position detected.", 1);
}

bool	map_valid(t_map *map)
{
	if (!map || !map->tiles)
		ft_error("Map data is not initialized.");
	check_walls(map);
	validate_components(map);
	return (true);
}

// Check if the current row is longer than the row above or below it
// if row_index > 0: // Skip this for the first row
// 	row_above = map->tiles[row_index - 1]
// 	if length(current_row) > length(row_above):
// 		for col_above from length(row_above) to length(current_row) - 1:
// 			if current_row[col_above] != '1':
// 				throw error "Invalid extension in current row above"

// if row_index < map->rows - 1: // Skip this for the last row
// 	row_below = map->tiles[row_index + 1]
// 	if length(current_row) > length(row_below):
// 		for col_below from length(row_below) to length(current_row) - 1:
// 			if current_row[col_below] != '1':
// 				throw error "Invalid extension in current row below"
