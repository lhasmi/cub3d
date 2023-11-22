/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:04 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/11 21:31:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// a function to initialize the structure t_maprqs
t_map	*init_map_struct(void)
{
	t_map	*new_map;

	new_map = (t_map *)malloc(sizeof(t_map));
	if (!new_map)
	{
		ft_error("Error: Memory allocation for map failed");
		exit(1);
	}
	new_map->tiles = NULL;
	new_map->no_texture = NULL;
	new_map->so_texture = NULL;
	new_map->we_texture = NULL;
	new_map->ea_texture = NULL;
	new_map->rows = 0;
	new_map->cols = 0;
	new_map->floor_color = NULL;
	new_map->ceiling_color = NULL;
	new_map->floor_color_hex = 0;
	new_map->ceiling_color_hex = 0;
	new_map->mapreqs = init_mapreqs();
	return (new_map);
}

t_mapreqs	init_mapreqs(void)
{
	t_mapreqs	mapreqs;

	mapreqs.pos_x = 0;
	mapreqs.pos_y = 0;
	mapreqs.orientation = 0;
	return (mapreqs);
}

t_color	*init_color_struct(void)
{
	t_color	*new_color;

	new_color = (t_color *)malloc(sizeof(t_color));
	if (!new_color)
	{
		ft_error("Error: Memory allocation for color failed");
		return (NULL);
	}
	new_color->red = -1;
	new_color->green = -1;
	new_color->blue = -1;
	return (new_color);
}

// mapreqs = (t_mapreqs *)malloc(sizeof(t_mapreqs));
// if (!mapreqs){
// 	ft_error("Error: Memory allocation for map requirements failed");
// 	if (mapreqs->map)
// 		free_map_exit(mapreqs->map,
			// "Error: Memory allocation for map requirements failed", 1);
// 	return (NULL);
// }

// fill the map with the map file, units are characters,
// space is allowed and is a valid part of the map.
// t_map	*fill_map_array(t_map *map_i, int fd)
// {
// 	int	i;

// 	i = 0;
// 	map_i->array[i] = get_next_line(fd);
// 	while (map_i->array[i] && is_map_line(map_i->array[i]) && i < map_i->height)
// 	{
// 		map_i->array[i] = get_next_line(fd);
// 		i++;
// 	}
// 	return (map_i);
// }

// t_map	init_map(char *map, t_map *map_i)
// {
// 	int		*fd;
// 	char	*line;
// 	size_t	len;

// 	map_i->mapreqs = init_mapreqs();
// 	fd = open_config_file(argv[1]);
// 	line = NULL;
// 	len = 0;

// 	while (/*FIXME: check if line is valid knowing i can use only get_next_line(fd) or custom f()*/)
// 	{
// 		parse_line(line);
// 	}

// 	free(line);
// 	fclose(fp);
// 	return (*map_i);
// }

// map_i = init_map_dimensions(map_i, fd);
// if (!map_i)
// {
// 	close(fd);
// 	free_map(map_i, "Could not initialize map dimensions");
// 	exit(1);
// }
// map_i = allocate_map_memory(map_i);
// if (!map_i)
// {
// 	close(fd);
// 	free_map(map_i,"Could not allocate memory for map");
// 	exit(1);
// }
// map_i = fill_map_array(map_i, fd);
// printf("Debug: HI\n");  // Debug print

// int	is_map_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	if (line == NULL)
// 		return (false);
// 	printf("Debug: line = '%s'\n", line);  // Debug print
// 	while (line[i] && is_space(line[i]))
// 		i++;
// 	if (line[i] == '\0')
// 		return (true);
// 	while (line[i])
// 	{
// 		if (!ft_strchr(" 01NESW", line[i++]))
// 			return (false);
// 	}
// 	return (true);
// }
