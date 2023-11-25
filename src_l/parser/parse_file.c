/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/25 10:43:52 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_line_bis(char *line, t_map *map, int fd)
{
	if (line[0] == 'F')
		parse_color(line, map, "F");
	else if (line[0] == 'C')
		parse_color(line, map, "C");
	else if (is_line_a_wall(line))
		fill_map_tiles(map, fd, line);
	else
		free_map_exit(map, "Invalid line prefix in configuration file", 1);
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
		parse_line_bis(line, map, fd);
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
