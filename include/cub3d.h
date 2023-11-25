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

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TSIZE 64

typedef struct s_map	t_map;

typedef struct s_mapreqs
{
	int					pos_x;
	int					pos_y;
	char				orientation;
}						t_mapreqs;

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct s_map
{
	int					rows;
	int					cols;
	char				**tiles;
	t_mapreqs			mapreqs;
	char				*line;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	int					textur_no_found;
	int					textur_so_found;
	int					textur_we_found;
	int					textur_ea_found;
	t_color				*floor_color;
	t_color				*ceiling_color;
	int					floor_color_hex;
	int					ceiling_color_hex;
	int					colorf_found;
	int					colorc_found;
}						t_map;

/****************************************************************************
***************************** Functions *************************************
****************************************************************************/

/* parser/check_map_bis.c*/
bool					is_valid_tile(char c);
bool					first_last_line(char *line);
bool					is_valid_middle_line(char *line);
int						trim_leading_ws(char *line);
bool					check_space_adjacency(char *row);

/* parser/check_map.c*/
bool					check_wall_line(t_map *map, char *current_row,
							int row_index);
bool					check_walls(t_map *map);
bool					set_player_position(t_map *map, int i, int j,
							bool *player_found);
bool					validate_components(t_map *map);
bool					map_valid(t_map *map);

/* parser/check_tile.c*/
bool					is_line_a_wall(char *line);
int						is_wall(t_map *map, int x, int y);
bool					is_orientation(char c);

/* parser/init.c*/
void					init_map_struct(t_map *map);
t_mapreqs				init_mapreqs(void);
t_color					*init_color_struct(void);

/* parser/parse_file_bis.c*/
int						get_color(char **lineptr);
void					parse_color_bisc(char *line, t_map *map,
							const char *color_id);
void					parse_color_bisf(char *line, t_map *map,
							const char *color_id);
bool					parse_color(char *line, t_map *map,
							const char *color_id);

/* parser/parse_file.c*/
char					**get_texture_field(t_map *map, const char *texture_id);
bool					parse_texture(char *line, t_map *map,
							const char *texture_id);
bool					parse_line_bis(char *line, t_map *map, int fd);
bool					parse_line(char *line, t_map *map, int fd);
int						parse_config_file(int fd, t_map *map);

/* parser/parse_map.c*/
char					**manual_realloc_2d_array(char **old_array,
							int old_rows, int new_rows, int cols);
void					update_map_cols(t_map *map, int new_row_length);
void					fill_map_tiles(t_map *map, int fd, char *first_line);

/* parser/parse_utils.c*/
bool					is_cub(char *filename);
void					free_map_struct(t_map *map);
void					free_map_resources(t_map *map);
void					free_map_exit(t_map *map, char *error_message,
							int status);
int						rgb_to_hex(int r, int g, int b);

/* parser/parse_utils2.c*/
int						is_cub_file_empty(const char *filepath);
bool					is_wspace(char c);
int						open_file(char *file, t_map *map_i, char *err_message);
bool					is_path_valid(char *path);
bool					is_color_valid(int color);

#endif
