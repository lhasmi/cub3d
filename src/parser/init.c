/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:04 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/27 03:12:31 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// a function to initialize the structure t_maprqs
t_mapreqs	init_mapreqs(void)
{
	t_mapreqs	mapreqs;

	mapreqs.pos_x = 0;
	mapreqs.pos_y = 0;
	mapreqs.space = 0;
	mapreqs.wall = 0;
	mapreqs.orientation = 0;
	return (mapreqs);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (false);
	printf("Debug: line = '%s'\n", line);  // Debug print
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (true);
	while (line[i])
	{
		if (!ft_strchr(" 01NESW", line[i++]))
			return (false);
	}
	return (true);
}
// write a function to check if the line is a map line or a line with spaces or digits or other letters
bool is_space (char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

t_map	*init_map_dimensions(t_map *map_i, int fd)
{
	map_i->height = 0;
	map_i->width = 0;
	map_i->line = get_next_line(fd);

	while (map_i->line && is_map_line(map_i->line))
	{
		map_i->height++;
		map_i->width = ft_strlen(map_i->line);
		free(map_i->line);
		map_i->line = get_next_line(fd);
	}
	if (map_i->line)
		free(map_i->line);
	return (map_i);
}

t_map	*allocate_map_memory(t_map *map_i)
{
	map_i->tiles = malloc(sizeof(char *) * (map_i->height + 1));
	if (!map_i->tiles)
		ft_error("Could not allocate memory");
	return (map_i);
}

// fill the map with the map file, units are characters,
// space is allowed and is a valid part of the map.
t_map	*fill_map_tiles(t_map *map_i, int fd)
{
	int	i;

	i = 0;
	map_i->tiles[i] = get_next_line(fd);
	while (map_i->tiles[i] && is_map_line(map_i->tiles[i]) && i < map_i->height)
	{
		map_i->tiles[i] = get_next_line(fd);
		i++;
	}
	return (map_i);
}

// Rules for the map validation and parsing:
t_map	init_map(char *map, t_map *map_i)
{
	int	fd;

	map_i->mapreqs = init_mapreqs();
	fd = open(map, O_RDONLY);
	if (fd < 0){
		free_map(map_i, "Could not open the map file");
		return (*map_i);
	}
	map_i = init_map_dimensions(map_i, fd);
	if (!map_i)
	{
		close(fd);
		free_map(map_i, "Could not initialize map dimensions");
		return (*map_i);
	}
	map_i = allocate_map_memory(map_i);
	if (!map_i)
	{
		close(fd);
		free_map(map_i,"Could not allocate memory for map");
		return (*map_i);
	}
	// fd = open(map, O_RDONLY);
	// if (fd < 0)
	// 	free_map(map_i, "Could not open the map file");
	map_i = fill_map_tiles(map_i, fd);
	printf("Debug: HI\n");  // Debug print
	if (close(fd) < 0)
		free_map(map_i, "Could not close the map file");
	return (*map_i);
}
