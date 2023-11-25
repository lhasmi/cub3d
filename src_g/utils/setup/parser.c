/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 00:20:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 16:21:02 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "MLX42/../lodepng/lodepng.h"
#include "constdef.h"
#include "cub3d.h"
#include "scene.h"
#include "vec.h"
#include "ray.h"
#include "dda.h"
#include "hooks.h"
#include "player.h"
#include "setup.h"

static double	get_yaw(char orientation)
{
	if (orientation == 'E')
		return (0.0);
	if (orientation == 'S')
		return (PI_HALF);
	if (orientation == 'W')
		return (PI);
	if (orientation == 'N')
		return (-PI_HALF);
	else
		return (0.0);
}

static int	load_texture(char *path, mlx_texture_t **tex)
{
	*tex = mlx_load_png(path);
	return (*tex == NULL);
}

static int	load_textures(t_map *map, t_scene *scene)
{
	if (load_texture(map->no_texture, &scene->tex[0]))
		return (1);
	if (load_texture(map->ea_texture, &scene->tex[1]))
		return (1);
	if (load_texture(map->so_texture, &scene->tex[2]))
		return (1);
	if (load_texture(map->we_texture, &scene->tex[3]))
		return (1);
	if (load_texture("img/img.png", &scene->tex[4]))
		return (1);
	if (load_texture("img/clouds.png", &scene->tex[5]))
		return (1);
	return (0);
}

static int	parse_map(char *file_name, t_map *map)
{
	int		fd;

	if (is_cub_file_empty(file_name) == -1)
		return (ft_error("Unable to open file"), 1);
	else if (is_cub_file_empty(file_name) == 1)
		return (ft_error("Empty file"), 1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_error("Error opening file"), 1);
	init_map_struct(map);
	if (parse_config_file(fd, map))
	{
		close(fd);
		return (ft_error("Invalid config file"), 1);
	}
	close(fd);
	if (!map_valid(map))
		free_map_exit(map, "Invalid map", 1);
	return (0);
}

void	parse(char *file_name, t_scene *scene)
{
	t_map	map;

	if (parse_map(file_name, &map))
		exit(1);
	scene->map_size = vec_create(map.cols, map.rows, 0);
	if (get_padded_map(map.tiles, map.cols, map.rows, &scene->map))
		free_map_exit(&map, "Invalid map, map freed", 1);
	scene->color_floor = map.floor_color_hex;
	scene->color_ceiling = map.ceiling_color_hex;
	if (load_textures(&map, scene))
	{
		free_map_resources(&map);
		ft_error("Texture could not be loaded");
		mlx_terminate(scene->mlx);
		exit(1);
	}
	scene->player = player_create(vec_create(map.mapreqs.pos_x + 0.5,
				map.mapreqs.pos_y + 0.5, 0), get_yaw(map.mapreqs.orientation));
	scene->interact = 0;
	scene->cursor_locked = 0;
	scene->cloud_offset = 0;
	free_map_resources(&map);
}
