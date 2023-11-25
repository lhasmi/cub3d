/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:04 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/25 10:41:25 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_map_struct(t_map *map)
{
	map->tiles = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->rows = 0;
	map->cols = 0;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->floor_color_hex = 0;
	map->ceiling_color_hex = 0;
	map->mapreqs = init_mapreqs();
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

	new_color = NULL;
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
