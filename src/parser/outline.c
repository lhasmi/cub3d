/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:53:06 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/25 22:47:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ◦ The use of images of the minilibX is strongly recommended.
bool is_cub(char *filename)
{
	// • Your program must take as a first argument a scene description file with the .cub extension.
	int len = ft_strlen(filename);
	if (len >= 4 && filename[len - 4] == '.' && filename[len - 3] == 'c'
				&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return true;
	else
		return false;
}

void	set_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_img	*img;

	//  The left and right arrow keys of the keyboard must allow you to look left and
	// right in the maze.
	if (keydata.keycode == KEY_LEFT)
	{
		img->angle -= 0.1;
		if (img->angle < 0)
			img->angle += 2 * PI;
	}
	if (keydata.keycode == KEY_RIGHT)
	{
		img->angle += 0.1;
		if (img->angle > 2 * PI)
			img->angle -= 2 * PI;
	}
	// ◦ Pressing ESC must close the window and quit the program cleanly.
	// ◦ Clicking on the red cross on the window’s frame must close the window and
	// quit the program cleanly.
	if (keydata.keycode == KEY_ESC)
	{
		mlx_destroy_window(param, img->win_ptr);
		// implement a function that frees all the allocated memory and call it here
		exit(0);
	}
}

// ◦ The W, A, S, and D keys must allow you to move the point of view through
// the maze.
void	set_keyhooks_bis(mlx_key_data_t keydata, void *param)
{
	t_img	*img;

	if (keydata.keycode == KEY_W)
	{
		img->x += 10 * cos(img->angle);
		img->y += 10 * sin(img->angle);
	}
	if (keydata.keycode == KEY_S)
	{
		img->x -= 10 * cos(img->angle);
		img->y -= 10 * sin(img->angle);
	}
	if (keydata.keycode == KEY_A)
	{
		img->x += 10 * cos(img->angle + PI / 2);
		img->y += 10 * sin(img->angle + PI / 2);
	}
	if (keydata.keycode == KEY_D)
	{
		img->x += 10 * cos(img->angle - PI / 2);
		img->y += 10 * sin(img->angle - PI / 2);
	}
}

t_map	*init_map_dimensions(t_map *map_i, int fd)
{
	char	*line;

	map_i->height = 0;
	map_i->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		map_i->height++;
		map_i->width = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (map_i);
}

t_map	*allocate_map_memory(t_map *map_i)
{
	map_i->tiles = malloc(sizeof(char *) * (map_i->height + 1));
	if (!map_i->tiles)
		ft_error("Could not allocate memory");
	return (map_i);
}

// fill the map with the map file, units are characters,
	space is allowed and is a valid part of the map.
t_map	*fill_map_tiles(t_map *map_i, int fd)
{
	int	i;

	i = 0;
	map_i->tiles[i] = get_next_line(fd);
	while (map_i->tiles[i])
		map_i->tiles[++i] = get_next_line(fd);
	return (map_i);
}

// Rules for the map validation and parsing:
t_map	init_map(char *map, t_map *map_i)
{
	int	fd;

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
// This is a simple valid map:
// 111111
// 100101
// 101001
// 1100N1
// 111111

// ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
// 1 for a wall, and N,S,E or W for the player’s start position and spawning
// orientation.
bool	check_map_characters(t_map map_i)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map_i.height)
	{
		j = 0;
		while (j < map_i.width)
		{
			if (map_i.tiles[i][j] != '0' && map_i.tiles[i][j] != '1'
				&& map_i.tiles[i][j] != 'N' && map_i.tiles[i][j] != 'S'
				&& map_i.tiles[i][j] != 'E' && map_i.tiles[i][j] != 'W')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
// ◦ The map must be closed/surrounded by walls, if not the program must return
// an error.
bool	map_closed(t_map map_i)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map_i.height)
	{
		j = 0;
		while (j < map_i.width)
		{
			if (i == 0 || i == map_i.height - 1)
			{
				if (map_i.tiles[i][j] != '1')
					return (false);
			}
			if (j == 0 || j == map_i.width - 1)
			{
				if (map_i.tiles[i][j] != '1')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

// ◦ Except for the map content, each type of element can be separated by one or
// more empty line(s).
// ◦ Except for the map content which always has to be the last, each type of
// element can be set in any order in the file.
// ◦ Except for the map,
	// each type of information from an element can be separated
// by one or more space(s).
// ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
// map and are up to you to handle. You must be able to parse any kind of map,
// as long as it respects the rules of the map.
// Each element (except the map) firsts information is the type identifier (com-
// posed by one or two character(s)),
	// followed by all specific informations for each
// object in a strict order such as :
// ∗ North texture:
// NO ./path_to_the_north_texture
// · identifier: NO
// · path to the north texure
// ∗ South texture:
// SO ./path_to_the_south_texture
// · identifier: SO
// · path to the south texure
// ∗ West texture:
// WE ./path_to_the_west_texture
// · identifier: WE
// · path to the west texure
// ∗ East texture:
// EA ./path_to_the_east_texture
// · identifier: EA
// · path to the east texure
// ∗ Floor color:
// F 220,100,0
// · identifier: F
// · R,G,B colors in range [0,255]: 0, 255, 255
void	free_map(t_map *map, char *str)
{
	int	i;

	i = 0;
	while ((*map).tiles && (*map).tiles[i])
	{
		free((*map).tiles[i]);
		i++;
	}
	free((*map).tiles);
	ft_error(str);
}
void	free_and_delete(char **arr, t_img *img)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	mlx_delete_image(img->mlx, img->pi);
	mlx_delete_image(img->mlx, img->wi);
	mlx_delete_image(img->mlx, img->ci);
	mlx_delete_image(img->mlx, img->ei);
	mlx_delete_image(img->mlx, img->bi);
	mlx_delete_texture(img->bt);
	mlx_delete_texture(img->pt);
	mlx_delete_texture(img->wt);
	mlx_delete_texture(img->ct);
	mlx_delete_texture(img->et);
}
