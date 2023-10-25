/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:50:42 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 14:42:12 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# define TSIZE 64
# define PI 3.14159265359


typedef struct s_map
{
	char	**map;
	size_t	height;
	size_t	max_width;
	size_t	*widths;
	char	**tiles;
}	t_map;

// typedef struct s_ray //s_player
// {
	// 	double	ray_orientation;//player orientation
	// 	double 	pos_x;
	// 	double 	pos_y;
// }	t_ray;//t_player;

typedef struct s_img
{
	t_map			map_i;
	int				angle;
	mlx_t			*mlx;
	mlx_texture_t	*nor_texture;
	mlx_texture_t	*sou_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_image_t		*no_image;
	mlx_image_t		*so_image;
	mlx_image_t		*we_image;
	mlx_image_t		*ea_image;
	mlx_image_t		*exit_image;
	mlx_image_t		*floor_image;
	int				nmv;
}	t_img;

	// ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
	// 1 for a wall, and N,S,E or W for the player’s start position and spawning
	// orientation.
	//N,S,E or W for the player’s start position and spawning
	// orientation.
typedef struct s_mapreqs
{
	int space;// 0
	int wall;// 1
	int pos_x;// N,S,E or W
	int pos_y;// N,S,E or W
	int orientation;// N,S,E or W
}	t_mapreqs;

// typedef struct map
// {
// 	size_t	width;
// 	size_t	height;
// 	char	**tiles;
// }	t_map;

// typedef struct img
// {
// 	mlx_texture_t	*pt;
// 	mlx_texture_t	*wt;
// 	mlx_texture_t	*ct;
// 	mlx_texture_t	*et;
// 	mlx_texture_t	*bt;
// 	mlx_image_t		*pi;
// 	mlx_image_t		*wi;
// 	mlx_image_t		*ci;
// 	mlx_image_t		*ei;
// 	mlx_image_t		*bi;
// 	mlx_t			*mlx;
// 	int				nmv;
// }	t_img;

// typedef struct req
// {
// 	int		e;
// 	int		c;
// 	int		p;
// 	int		o;
// 	size_t	px;
// 	size_t	py;
// }	t_req;

/******************************************************************************************************************
********************************************** Functions **********************************************************
*******************************************************************************************************************/

/* parser/outline.c */
bool	is_cub(char *filename);
void	set_keyhooks(mlx_key_data_t keydata, void *param);
void	set_keyhooks_bis(mlx_key_data_t keydata, void *param);

t_map	*init_map_dimensions(t_map *map_i, int fd);
t_map	*allocate_map_memory(t_map *map_i);
t_map	*fill_map_tiles(t_map *map_i, int fd);
t_map	init_map(char *map, t_map *map_i);
bool	check_map_characters(t_map map_i);
bool	map_closed(t_map map_i);
void	free_map(t_map *map, char *str);
void	free_and_delete(char **arr, t_img *img);
// /* so_long.c */
// int		count_moves(t_img *img, int32_t y, int32_t x);
// void	set_keyhooks(mlx_key_data_t keydata, void *param);

// /* init.c */
// t_map	*init_map_dimensions(t_map *map_i, int fd);
// t_map	*allocate_map_memory(t_map *map_i);
// t_map	*fill_map_tiles(t_map *map_i, int fd);
// t_map	init_map(char *map, t_map *map_i);
// void	init_img(mlx_t *mlx, t_img *img);

// /* utils.c */
// bool	is_ber(char *filename);
// void	put_img(mlx_t *mlx, t_img img, t_map map_i);

// /* check_map.c */
// void	check_walls(t_map map_i);
// t_req	count_components(t_map map_i, t_req ecpo, size_t i, size_t j);
// void	validate_components(t_map map_i, t_req ecpo);
// bool	check_additional_conditions(t_map *map_i);
// bool	map_valid(t_map map_i);

// /* check_tile.c */
// int		is_wall(t_img *img, int32_t y, int32_t x);
// int		is_coll(t_img *img, size_t *coll, int32_t y, int32_t x);
// int		is_exit(t_img *img, size_t *coll, int32_t y, int32_t x);

// /* check_path.c */
// char	**allocate_map_d(t_map *map);
// void	path_fill(t_map *map, char **map_d, size_t y, size_t x);
// void	check_blocked_path(t_map *map);
// void	check_tiles_for_path(t_map *map, char **map_d);
// void	check_path(t_map *map, t_req *pos);

// /* free.c */
// void	free_and_delete(char **arr, t_img *img);
// void	free_map(t_map *map, char *str);

#endif
