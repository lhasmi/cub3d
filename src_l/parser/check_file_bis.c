/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:09:34 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 22:53:05 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <assert.h>

char	**get_texture_field(t_map *map, const char *texture_id)
{
	if (ft_strcmp(texture_id, "NO") == 0)
		return (&map->no_texture);
	else if (ft_strcmp(texture_id, "SO") == 0)
		return (&map->so_texture);
	else if (ft_strcmp(texture_id, "WE") == 0)
		return (&map->we_texture);
	else if (ft_strcmp(texture_id, "EA") == 0)
		return (&map->ea_texture);
	else
	{
		ft_error("Error: Invalid texture identifier");
		return (NULL);
	}
	return (NULL);
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
	{
		ft_error("Error: Invalid path for texture");
		return (false);
	}
	texture_field = get_texture_field(map, texture_id);
	*texture_field = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!*texture_field)
	{
		ft_error("Error: Could not allocate memory for texture");
		return (false);
	}
	ft_strcpy(*texture_field, tmp);
	return (true);
}

int	get_color(char **lineptr)
{
	char	*tmp;
	int		color;

	tmp = ft_strtok(*lineptr, ",");
	if (tmp == NULL)
	{
		ft_error("Error: Invalid color");
		exit(1);
	}
	color = ft_atoi(tmp);
	if (!is_color_valid(color))
	{
		ft_error("Error: Invalid color");
		exit(1);
	}
	*lineptr = NULL;
	return (color);
}

void	parse_color(char *line, t_map *map, const char *color_id)
{
	while (is_wspace(*line))
		line++;
	while (line[0] == color_id[0] && line[1] == ' ')
		line++;
	if (color_id[0] == 'F')
	{
		map->floor_color = init_color_struct();
		map->floor_color->red = get_color(&line);
		map->floor_color->green = get_color(&line);
		map->floor_color->blue = get_color(&line);
		map->floor_color_hex = rgb_to_hex(map->floor_color->red,
				map->floor_color->green, map->floor_color->blue);
	}
	else if (color_id[0] == 'C')
	{
		map->ceiling_color = init_color_struct();
		map->ceiling_color->red = get_color(&line);
		map->ceiling_color->green = get_color(&line);
		map->ceiling_color->blue = get_color(&line);
		map->ceiling_color_hex = rgb_to_hex(map->ceiling_color->red,
				map->ceiling_color->green, map->ceiling_color->blue);
	}
}

// bool	parse_texture_line(char *line, t_map *map, const char *prefix)
// {
// 	if (line[0] == prefix[0] && line[1] == prefix[1])
// 		return (parse_texture(line, map, prefix));
// 	else
// 		return (true);
// }
