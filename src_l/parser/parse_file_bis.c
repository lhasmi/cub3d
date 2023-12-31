/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:09:34 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/25 19:44:13 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/cub3d.h"

int	get_color(char **lineptr)
{
	char	*tmp;
	int		color;

	tmp = ft_strtok(*lineptr, ",");
	if (tmp == NULL)
	{
		return (ft_error("Invalid color"), -1);
	}
	color = ft_atoi(tmp);
	if (!is_color_valid(color))
	{
		return (ft_error("Invalid color"), -1);
	}
	*lineptr = NULL;
	return (color);
}

void	parse_color_bisf(char *line, t_map *map)
{
	map->colorf_found++;
	if (map->floor_color == NULL)
		map->floor_color = init_color_struct();
	map->floor_color->red = get_color(&line);
	map->floor_color->green = get_color(&line);
	map->floor_color->blue = get_color(&line);
	map->floor_color_hex = rgb_to_hex(map->floor_color->red,
			map->floor_color->green, map->floor_color->blue);
}

void	parse_color_bisc(char *line, t_map *map)
{
	map->colorc_found++;
	if (map->ceiling_color == NULL)
		map->ceiling_color = init_color_struct();
	map->ceiling_color->red = get_color(&line);
	map->ceiling_color->green = get_color(&line);
	map->ceiling_color->blue = get_color(&line);
	map->ceiling_color_hex = rgb_to_hex(map->ceiling_color->red,
			map->ceiling_color->green, map->ceiling_color->blue);
}

bool	parse_color(char *line, t_map *map, const char *color_id)
{
	char	*start_line;

	start_line = line;
	while (is_wspace(*line))
		line++;
	while (line[0] == color_id[0] && line[1] == ' ')
		line++;
	if (color_id[0] == 'F')
		parse_color_bisf(line, map);
	else if (color_id[0] == 'C')
		parse_color_bisc(line, map);
	free(start_line);
	return (true);
}
