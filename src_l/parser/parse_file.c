/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/25 17:05:26 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**get_texture_field(t_map *map, const char *texture_id)
{
	if (ft_strcmp(texture_id, "NO") == 0 && map->textur_no_found == 0)
	{
		map->textur_no_found++;
		return (&map->no_texture);
	}
	else if (ft_strcmp(texture_id, "SO") == 0 && map->textur_so_found == 0)
	{
		map->textur_so_found++;
		return (&map->so_texture);
	}
	else if (ft_strcmp(texture_id, "WE") == 0 && map->textur_we_found == 0)
	{
		map->textur_we_found++;
		return (&map->we_texture);
	}
	else if (ft_strcmp(texture_id, "EA") == 0 && map->textur_ea_found == 0)
	{
		map->textur_ea_found++;
		return (&map->ea_texture);
	}
	else
	{
		free_map_exit(map, "Invalid or multiple texture identifier", 1);
		return (NULL);
	}
}

bool	parse_texture(char *line, t_map *map, const char *texture_id)
{
	char	*tmp;
	char	**texture_field;

	while (is_wspace(*line))
		line++;
	if (ft_strncmp(line, texture_id, ft_strlen(texture_id)) == 0)
		line += ft_strlen(texture_id);
	tmp = ft_strtok(line, " ");
	if (tmp == NULL || !is_path_valid(tmp))
		return (ft_error("Invalid path for texture"), false);
	texture_field = get_texture_field(map, texture_id);
	*texture_field = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!*texture_field)
		return (ft_error("Could not allocate memory for texture"), false);
	ft_strcpy(*texture_field, tmp);
	return (true);
}

bool	parse_line_bis(char *line, t_map *map, int fd)
{
	if (line[0] == 'F')
		return (parse_color(line, map, "F"));
	else if (line[0] == 'C')
		return (parse_color(line, map, "C"));
	else if (is_line_a_wall(line))
	{
		fill_map_tiles(map, fd, line);
		return (true);
	}
	else
	{
		free_map_exit(map, "Invalid line prefix in configuration file", 0);
		return (false);
	}
	return (true);
}

bool	parse_line(char *line, t_map *map, int fd)
{
	if ((is_wspace(line[0]) || line[0] == '\0') && !is_line_a_wall(line))
		return (true);
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (parse_texture(line, map, "NO") == false)
			return (false);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (parse_texture(line, map, "SO") == false)
			return (false);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (parse_texture(line, map, "WE") == false)
			return (false);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (parse_texture(line, map, "EA") == false)
			return (false);
	}
	else
		return (parse_line_bis(line, map, fd));
	return (true);
}

int	parse_config_file(int fd, t_map *map)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(line, map, fd) == false)
			return (1);
	}
	return (0);
}
