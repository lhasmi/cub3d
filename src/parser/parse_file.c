/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 17:36:59 by lhasmi           ###   ########.fr       */
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
        exit(1);
    }
    return NULL;
}

void parse_texture(char *line, t_map *map, const char *texture_id)
{
	char *tmp;
	char **texture_field;

	while (is_wspace(*line))
		line++;
	if (ft_strncmp(line, texture_id, ft_strlen(texture_id)) == 0) //skip texture identifier
		line += ft_strlen(texture_id);
	tmp = ft_strtok(line, " ");
	// printf("path = tmp: %s\n", tmp); //DEBUG
	// printf("is_path_valid(tmp): %d\n", is_path_valid(tmp)); //DEBUG
	// printf("Parsing texture: %s\n", texture_id); // Debug print
    // printf("Line content: %s\n", line); // Debug print
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
	// printf("Texture path: %s\n", *texture_field); // Debug print after copying the path
	assert(*texture_field != NULL); // Ensure that the texture path was copied successfully
	// printf("Texture path after assertion: %s\n", *texture_field); // Debug print
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
	
	t_color color;

	while (is_wspace(*line))
		line++;
	while(line[0] == color_id[0] && line[1] == ' ')
		line++;
	color.red = get_color(&line);
	color.green = get_color(&line);
	color.blue = get_color(&line);
	map->floor_color = &color;
}

void parse_line(char *line, t_map *map, int fd)
{
	if (is_wspace(line[0]) || line[0] == '\0')
		return;
	while (is_wspace(*line))
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
	else{
    	if (is_wspace(line[0]) || line[0] == '\0')
        	return;
		while (is_wspace(*line))
			line++;
		if (*line == '\0')
			return;
		fill_map_tiles(map, fd);
	}
}

t_map	*parse_config_file(int fd, t_map *map)
{
	char *line;

	// map = init_map_struct();
	// fd = open_file(char *file);//commented out during testing 
	while ((line = get_next_line(fd)))
	{
		parse_line(line, map, fd);
		free(line);
	}
	// printf("map->rows: %d\n", map->rows);//DEBUG
    // printf("map->cols: %d\n", map->cols);//DEBUG
	return map;
}
