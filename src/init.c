/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:53:18 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/21 16:21:05 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_map *init_map_dimensions(t_map *map_i, int fd)
{
    char *line;
    map_i->height = 0;
    map_i->width = 0;
    line = get_next_line(fd);
    while (line)
    {
        map_i->height++;
        map_i->width = ft_strlen(line);
        free(line);
        line = get_next_line(fd);
        if (line && ft_strlen(line) != map_i->width)
            ft_error("Non-rectangular map");
    }
    if (line)
        free(line);
    return (map_i);
}

t_map *allocate_map_memory(t_map *map_i)
{
    map_i->tiles = malloc(sizeof(char *) * (map_i->height + 1));
    if (!map_i->tiles)
        ft_error("Could not allocate memory");
    return (map_i);
}

t_map *fill_map_tiles(t_map *map_i, int fd)
{
    int i = 0;
    map_i->tiles[i] = get_next_line(fd);
    while (map_i->tiles[i])
        map_i->tiles[++i] = get_next_line(fd);
    return (map_i);
}

// void	init_map(t_map *map)
// {
// 	map->map = NULL;
// 	map->height = 0;
// 	map->max_width = 0;
// 	map->widths = NULL;
// }

t_map init_map(char *map, t_map *map_i)
{
    int fd;

    fd = open(map, O_RDONLY);
    if (fd < 0)
        ft_error("Could not open the map file");

    map_i = init_map_dimensions(map_i, fd);

    map_i = allocate_map_memory(map_i);

    fd = open(map, O_RDONLY);
    if (fd < 0)
        free_map(map_i, "Could not open the map file");

    map_i = fill_map_tiles(map_i, fd);

    if (close(fd) < 0)
        free_map(map_i, "Could not close the map file");

    return (*map_i);
}

void	init_img(mlx_t *mlx, t_img *img)
{
	img->bt = mlx_load_png("./img/bg.png");
	img->bi = mlx_texture_to_image(mlx, img->bt);
	img->pt = mlx_load_png("./img/player.png");
	img->pi = mlx_texture_to_image(mlx, img->pt);
	img->wt = mlx_load_png("./img/wall.png");
	img->wi = mlx_texture_to_image(mlx, img->wt);
	img->ct = mlx_load_png("./img/collectible.png");
	img->ci = mlx_texture_to_image(mlx, img->ct);
	img->et = mlx_load_png("./img/exit.png");
	img->ei = mlx_texture_to_image(mlx, img->et);
    if (!img->bt || !img->bi || !img->pt || !img->pi ||!img->wt 
            || !img->wi || !img->ct || !img->ci || !img->et 
            || !img->ei)
        ft_error("Failed to load or convert one or more textures to images");
}
