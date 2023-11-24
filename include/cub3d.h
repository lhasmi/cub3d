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

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <assert.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define TSIZE 64
// # define PI 3.14159265359

typedef struct s_map t_map;

typedef struct s_mapreqs
{
	// int			door;// just for bonus files
	int			pos_x;// N,S,E or W
	int			pos_y;// N,S,E or W
	char		orientation;// N,S,E or W in char as it is in the map
}	t_mapreqs;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
} t_color;

typedef struct s_map
{
	int			rows;
	int			cols;
	char		**tiles;
	t_mapreqs	mapreqs;
	char		*line;
	char 		*no_texture;
	char 		*so_texture;
	char 		*we_texture;
	char 		*ea_texture;
	t_color 	*floor_color;
	t_color 	*ceiling_color;
	int			floor_color_hex;
	int			ceiling_color_hex;

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
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
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


// typedef struct map
// {
// 	size_t	width;
// 	size_t	height;
// 	char	**array;
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
bool		is_cub(char *filename);
void		set_keyhooks(mlx_key_data_t keydata, void *param);
void		set_keyhooks_bis(mlx_key_data_t keydata, void *param);
t_mapreqs	init_mapreqs(void);
// t_map		*init_map_dimensions(t_map *map_i, int fd);
// t_map		*allocate_map_memory(t_map *map_i);
// t_map		*fill_map_array(t_map *map_i, int fd);
// t_map		init_map(char *map, t_map *map_i);
bool		check_map_characters(t_map map_i);
bool		map_closed(t_map map_i);
// void		free_map_exit(t_map *map, char *str, int d);
void		free_map_exit(t_map *map, char *error_message, int status);
void		free_and_delete(char **arr, t_img *img);
int			is_map_line(char *line);
int			open_file(char *file, t_map *map_i, char *err_message);
// write a function to check if the line is a map line or a line with spaces or digits or other letters
bool		is_wspace (char c);
bool		is_path_valid(char *path);
char		**get_texture_field(t_map *map, const char *texture_id);
void		parse_north_texture(char *line, t_map *map);
bool		is_color_valid(int color);
char		**manual_realloc_2D_array(char **old_array, int old_rows, int new_rows, int cols);
// void		parse_map_layout(char *line, t_map *map);
void		fill_map_tiles(t_map *map, int fd, char *first_line);
t_map		*parse_config_file(int fd, t_map *map);
void		parse_color(char *line, t_map *map, const char *color_id);
void		free_map_resources(t_map *map);


// /* so_long.c */
// int		count_moves(t_img *img, int32_t y, int32_t x);
// void	set_keyhooks(mlx_key_data_t keydata, void *param);

// /* init.c */
// t_map	*init_map_dimensions(t_map *map_i, int fd);
// t_map	*allocate_map_memory(t_map *map_i);
// t_map	*fill_map_array(t_map *map_i, int fd);
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
// void	check_array_for_path(t_map *map, char **map_d);
// void	check_path(t_map *map, t_req *pos);

// /* free.c */
// void	free_and_delete(char **arr, t_img *img);
// void	free_map(t_map *map, char *str);

t_map	*init_map_struct();
t_color *init_color_struct();
bool parse_line(char *line, t_map *map, int fd);
bool parse_texture(char *line, t_map *map, const char *texture_id);

bool	check_walls(t_map *map);
bool	validate_components(t_map *map);
bool	is_orientation(char c);
bool	is_valid_tile(char c);
bool	first_last_line(char *line);
bool	check_space_adjacency(char *row);
bool	is_valid_middle_line(char *line);
int		trim_leading_ws(char *line);
bool	map_valid(t_map *map);
int		rgb_to_hex(int r, int g, int b);
int		trim_leading_ws(char *line);
bool	is_line_a_wall(char *line);
int		is_cub_file_empty(const char *filepath);

#endif
