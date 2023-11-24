/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:48:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 23:14:30 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_cub(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len >= 4 && filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (true);
	else
		return (false);
}

void	free_map_struct(t_map *map)
{
	if (map->tiles)
	{
		free(map->tiles);
		map->tiles = NULL;
	}
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
}

void	free_map_resources(t_map *map)
{
	int	i;

	i = 0;
	while (map->tiles && i < map->rows)
	{
		if (map->tiles[i])
		{
			free(map->tiles[i]);
			map->tiles[i] = NULL;
		}
		i++;
	}
	free_map_struct(map);
}

void	free_map_exit(t_map *map, char *error_message, int status)
{
	if (status != 0)
	{
		free_map_resources(map);
		ft_error(error_message);
		exit(status);
	}
	else
		ft_error(error_message);
}

int	rgb_to_hex(int r, int g, int b)
{
	int	alpha;

	alpha = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}
