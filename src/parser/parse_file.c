/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/27 20:32:52 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// File reading and map initialization:
// 1. Open the file
ft_openfile(char *file, int i, char *err_message);
FILE *open_file(char *file);

//2. Line-by-Line Parsing
//Parse each line according to the identifiers ("NO", "SO", "WE", "EA", "F", "C").
//If the line is not an identifier, it is a map line or an edge case (empty line, space, etc.).
// Parse Textures path and colors
bool is_path_valid(char *path);

char **get_texture_field(t_map *map, const char *texture_id) 
{
    if (ft_strcmp(texture_id, "NO") == 0)
        return &map->nor_texture;
    else if (ft_strcmp(texture_id, "SO") == 0)
        return &map->sou_texture;
    else if (ft_strcmp(texture_id, "WE") == 0)
        return &map->we_texture;
    else if (ft_strcmp(texture_id, "EA") == 0)
        return &map->ea_texture;
    else {
        ft_error("Error: Invalid texture identifier");
        exit(1);
    }
    return NULL;
}

void parse_texture(char *line, t_map *map, const char *texture_id)
{
	char *tmp;
	char **texture_field;

	while (is_space(*line))
		line++;
	if (ft_strncmp(line, texture_id, ft_strlen(texture_id)) == 0) //skip texture identifier
		line += ft_strlen(texture_id);
	tmp = ft_strtok(line, " ");
	if (tmp == NULL || !is_path_valid(tmp)) {
		ft_error("Error: Invalid path for texture");
		exit(1);
	}
	texture_field = get_texture_field(map, texture_id);
	*texture_field = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!*texture_field) {
		ft_error("Error: Could not allocate memory for texture");
		exit(1);
	}
	ft_strcpy(*texture_field, tmp);
}
// char 		*floor_color;
// char 		*ceiling_color;
int get_color(char **lineptr)
{
	char *tmp;
	int color;
	
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
	
	t_color color;

	while (is_space(*line))
		line++;
	while(line[0] == 'F' || line[0] == 'C')
		line++;
	color.red = get_color(&line);
	color.green = get_color(&line);
	color.blue = get_color(&line);
	map->floor_color = color;
}

void parse_line(char *line, t_map *map)
{
	if (is_space(line[0]) || line[0] == '\0')
		return;
	while (is_space(*line))
		line++;
	if (*line == '\0')
		return;
	if (line[0] == 'N' && line[1] == 'O')
		parse_texture(line, map, "NO");
	else if (line[0] == 'S' && line[1] == 'O')
		parse_texture(line, map, "SO");
	else if (line[0] == 'W' && line[1] == 'E')
		parse_texture(line, map, "WE");
	else if (line[0] == 'E' && line[1] == 'A')
		parse_texture(line, map, "EA");
	else if (line[0] == 'F')
		parse_color(line, map, "F");
	else if (line[0] == 'C')
		parse_color(line, map, "C");
	else
		parse_map_layout(line, map);
}

