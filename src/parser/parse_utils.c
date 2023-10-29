/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:48:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 01:28:20 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool is_space (char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

int	ft_openfile(char *file, int i, char *err_message);
int *open_file(char *file)
{
	int *fd;

	fd = ft_openfile(file, 0, "Could not open the map file");
	return (fd);
}

bool is_path_valid(char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		return false;
	} else {
		close(fd);
		return true;
	}
}

//  the is_color_valid() function would check that each of color.red, color.green, and color.blue is between 0 and 255.
bool is_color_valid(t_color color)
{
	if (color.red < 0 || color.red > 255)
		return false;
	if (color.green < 0 || color.green > 255)
		return false;
	if (color.blue < 0 || color.blue > 255)
		return false;
	return true;
}
bool	is_cub(char *filename)
{
	int	len;

	// • Your program must take as a first argument a scene description file with the .cub extension.
	len = ft_strlen(filename);
	if (len >= 4 && filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (true);
	else
		return (false);
}
void	set_keyhooks(mlx_key_data_t keydata, void *param)
{
	t_img		*img = NULL;
	(void)param;

	//  The left and right arrow keys of the keyboard must allow you to look left and
	// right in the maze.
	if (keydata.key == MLX_KEY_LEFT)
	{
		img->angle -= 0.1;
		if (img->angle < 0)
			img->angle += 2 * PI;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		img->angle += 0.1;
		if (img->angle > 2 * PI)
			img->angle -= 2 * PI;
	}
	// ◦ Pressing ESC must close the window and quit the program cleanly.
	// ◦ Clicking on the red cross on the window’s frame must close the window and
	// quit the program cleanly.
	// void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(img->mlx);
}

// ◦ The W, A, S, and D keys must allow you to move the point of view through
// the maze.
void	set_keyhooks_bis(mlx_key_data_t keydata, void *param)
{
	t_img		*img = NULL;
	t_mapreqs	*mapreqs = NULL;

	(void)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		mapreqs->pos_x += 10 * cos(img->angle);
		mapreqs->pos_y += 10 * sin(img->angle);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		mapreqs->pos_x -= 10 * cos(img->angle);
		mapreqs->pos_y -= 10 * sin(img->angle);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		mapreqs->pos_x += 10 * cos(img->angle + PI / 2);
		mapreqs->pos_y += 10 * sin(img->angle + PI / 2);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		mapreqs->pos_x += 10 * cos(img->angle - PI / 2);
		mapreqs->pos_y += 10 * sin(img->angle - PI / 2);
	}
}

void	free_map_exit(t_map *map, char *str, int d)
{
	int	i;

	i = 0;
	while ((*map).tiles && (*map).tiles[i])
	{
		free((*map).tiles[i]);
		i++;
	}
	if ((*map).tiles)
		free((*map).tiles);
	ft_error(str);
	if (d == 1)
		exit(1);
	return;
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
	mlx_delete_image(img->mlx, img->no_image);
	mlx_delete_image(img->mlx, img->so_image);
	mlx_delete_image(img->mlx, img->we_image);
	mlx_delete_image(img->mlx, img->ea_image);
	mlx_delete_image(img->mlx, img->exit_image);
	mlx_delete_image(img->mlx, img->floor_image);
	mlx_delete_texture(img->nor_texture);
	mlx_delete_texture(img->sou_texture);
	mlx_delete_texture(img->wes_texture);
	mlx_delete_texture(img->eas_texture);
}

// // This is a simple valid map:
// // 111111
// // 100101
// // 101001
// // 1100N1
// // 111111

// // ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
// // 1 for a wall, and N,S,E or W for the player’s start position and spawning
// // orientation.
// bool	check_map_characters(t_map map_i)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_i.height)
// 	{
// 		j = 0;
// 		while (j < map_i.width)
// 		{
// 			if (map_i.tiles[i][j] != '0' && map_i.tiles[i][j] != '1'
// 				&& map_i.tiles[i][j] != 'N' && map_i.tiles[i][j] != 'S'
// 				&& map_i.tiles[i][j] != 'E' && map_i.tiles[i][j] != 'W')
// 				return (false);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }
// // ◦ The map must be closed/surrounded by walls, if not the program must return
// // an error.
// bool	map_closed(t_map map_i)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_i.height)
// 	{
// 		j = 0;
// 		while (j < map_i.width)
// 		{
// 			if (map_i.tiles[i][j] == '0')
// 			{
// 				if (i == 0 || i == map_i.height - 1)
// 					return (false);
// 				if (j == 0 || j == map_i.width - 1)
// 					return (false);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// // ◦ Except for the map content, each type of element can be separated by one or
// // more empty line(s).
// // ◦ Except for the map content which always has to be the last, each type of
// // element can be set in any order in the file.
// // ◦ Except for the map,
// // each type of information from an element can be separated
// // by one or more space(s).
// // ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
// // map and are up to you to handle. You must be able to parse any kind of map,
// // as long as it respects the rules of the map.
// // Each element (except the map) firsts information is the type identifier (com-
// // posed by one or two character(s)),
// // followed by all specific informations for each
// // object in a strict order such as :
// // ∗ North texture:
// // NO ./path_to_the_north_texture
// // · identifier: NO
// // · path to the north texure
// // ∗ South texture:
// // SO ./path_to_the_south_texture
// // · identifier: SO
// // · path to the south texure
// // ∗ West texture:
// // WE ./path_to_the_west_texture
// // · identifier: WE
// // · path to the west texure
// // ∗ East texture:
// // EA ./path_to_the_east_texture
// // · identifier: EA
// // · path to the east texure
// // ∗ Floor color:
// // F 220,100,0
// // · identifier: F
// // · R,G,B colors in range [0,255]: 0, 255, 255
