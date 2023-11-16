/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/16 20:52:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<assert.h>
#include "../../include/cub3d.h"

char **get_texture_field(t_map *map, const char *texture_id)
{
	if (ft_strcmp(texture_id, "NO") == 0)
		return &map->no_texture;
	else if (ft_strcmp(texture_id, "SO") == 0)
		return &map->so_texture;
	else if (ft_strcmp(texture_id, "WE") == 0)
		return &map->we_texture;
	else if (ft_strcmp(texture_id, "EA") == 0)
		return &map->ea_texture;
	else {
		ft_error("Error: Invalid texture identifier");
		return NULL;
	}
	return NULL;
}

bool parse_texture(char *line, t_map *map, const char *texture_id)
{
	char *tmp;
	char **texture_field;

	while (is_wspace(*line))
		line++;
	if (ft_strncmp(line, texture_id, ft_strlen(texture_id)) == 0) //skip texture identifier
		line += ft_strlen(texture_id);
	tmp = ft_strtok(line, " ");
	if (tmp == NULL || !is_path_valid(tmp))
	{
		ft_error("Error: Invalid path for texture");
		return false;
	}
	texture_field = get_texture_field(map, texture_id);
	*texture_field = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!*texture_field)
	{
		ft_error("Error: Could not allocate memory for texture");
		return false;
	}
	ft_strcpy(*texture_field, tmp);
	return true;
}

int get_color(char **lineptr)
{
	char	*tmp;
	int		color;

	tmp = ft_strtok(*lineptr, ",");
	if (tmp == NULL) {
		ft_error("Error: Invalid color");
		exit(1);
	}
	color = ft_atoi(tmp);
	if (!is_color_valid(color)) {
		ft_error("Error: Invalid color");
		exit(1);
	}
	*lineptr = NULL;
	return color;
}

void parse_color(char *line, t_map *map, const char *color_id)
{

	while (is_wspace(*line))
		line++;
	while(line[0] == color_id[0] && line[1] == ' ')
		line++;
	if(color_id[0] == 'F')
	{
		map->floor_color = init_color_struct();
		map->floor_color->red = get_color(&line);
		map->floor_color->green = get_color(&line);
		map->floor_color->blue = get_color(&line);
		map->floor_color_hex = rgb_to_hex(map->floor_color->red, map->floor_color->green, map->floor_color->blue);
	}
	else if(color_id[0] == 'C')
	{
		map->ceiling_color = init_color_struct();
		map->ceiling_color->red = get_color(&line);
		map->ceiling_color->green = get_color(&line);
		map->ceiling_color->blue = get_color(&line);
		map->ceiling_color_hex = rgb_to_hex(map->ceiling_color->red, map->ceiling_color->green, map->ceiling_color->blue);
	}// Convert to hex before using in MLX42
}

bool parse_line(char *line, t_map *map, int fd)
{
	if ((is_wspace(line[0]) || line[0] == '\0') && !is_line_a_wall(line))
		return true;
	if (line[0] == 'N' && line[1] == 'O')
	{
		if(parse_texture(line, map, "NO") == false)
			return false;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if(parse_texture(line, map, "SO") == false)
			return false;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if(parse_texture(line, map, "WE") == false)
			return false;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if(parse_texture(line, map, "EA") == false)
			return false;
	}
	else if (line[0] == 'F')
		parse_color(line, map, "F");
	else if (line[0] == 'C')
		parse_color(line, map, "C");
	else if (ft_strchr("01NSEW ", line[0]))
		fill_map_tiles(map, fd, line);
	else
		free_map_exit(map, "Error\n Invalid line prefix in configuration file", 1);
	return true;
}

// void parse_line(char *line, t_map *map, int fd)
// {
// 	if ((is_wspace(line[0]) || line[0] == '\0') && !is_line_a_wall(line))
// 		return;
// 	// while (is_wspace(*line))
// 	// 	line++;
// 	// printf("line in parse_line() before the if conditions: %s\n", line);//DEBUG
// 	if (*line == '\0')
// 		return;
// 	if (line[0] == 'N' && line[1] == 'O')
// 		parse_texture(line, map, "NO");
// 	else if (line[0] == 'S' && line[1] == 'O')
// 		parse_texture(line, map, "SO");
// 	else if (line[0] == 'W' && line[1] == 'E')
// 		parse_texture(line, map, "WE");
// 	else if (line[0] == 'E' && line[1] == 'A')
// 		parse_texture(line, map, "EA");
// 	else if (line[0] == 'F')
// 		parse_color(line, map, "F");
// 	else if (line[0] == 'C')
// 		parse_color(line, map, "C");
// 	else
// 	{
// 		if (*line == '\0')
// 			return;
// 		fill_map_tiles(map, fd, line);
// 	}
// }

t_map	*parse_config_file(int fd, t_map *map)
{
	char *line;
	// map = init_map_struct();
	// fd = open_file(char *file);//commented out during testing
	while ((line = get_next_line(fd)))
	{
		// printf("line in parse_config_file(): %s\n", line);//DEBUG
		if (parse_line(line, map, fd) == false)
			return NULL;
	}
	return (map);
}
