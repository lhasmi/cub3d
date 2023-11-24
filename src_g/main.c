#include <stdio.h>
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

// -----------------------------------------------------------------------------

double get_yaw(char orientation)
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

int	load_texture(char *path, mlx_texture_t **tex)
{
	*tex = mlx_load_png(path);
	return (*tex == NULL);
}

void parse(char *file_name, t_scene *scene)
{
	int		fd;
	t_map	*map;

	if (is_cub_file_empty(file_name) == - 1)
	{
		ft_error("unable to open file");
		exit(1);
	}
	else if(is_cub_file_empty(file_name) == 1)
	{
		ft_error("Empty file");
		exit(1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_error("Error opening file");
		exit(1);
	}
	map = init_map_struct();
	map = parse_config_file(fd, map);
	close(fd);
	if (map == NULL || !map_valid(map)){
		free_map_exit(map, "Invalid map", 1);
	}

	scene->map_size = vec_create(map->cols, map->rows, 0);
	if (get_padded_map(map->tiles, map->cols, map->rows, &scene->map))
		free_map_exit(map, "Invalid map, map freed", 1);
	scene->color_floor = map->floor_color_hex;
	scene->color_ceiling = map->ceiling_color_hex;
	if (load_texture(map->no_texture, &scene->tex[0]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	if (load_texture(map->ea_texture, &scene->tex[1]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	if (load_texture(map->so_texture, &scene->tex[2]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	if (load_texture(map->we_texture, &scene->tex[3]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	if (load_texture("img/img.png", &scene->tex[4]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	if (load_texture("img/clouds.png", &scene->tex[5]))
	{
		free_map_exit(map, "Texture could not be loaded", 1);
		mlx_terminate(scene->mlx);
	}
	scene->player = player_create(vec_create(map->mapreqs.pos_x + 0.5, map->mapreqs.pos_y + 0.5, 0), get_yaw(map->mapreqs.orientation));
	scene->interact = 0;
	scene->cursor_locked = 0;
	scene->cloud_offset = 0;
	free_map_resources(map);
}

int main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_scene	scene;

	if (argc != 2 || !is_cub(argv[1]))
	{
		ft_error("Invalid arguments");
		exit(1);
	}

	scene.size = vec_create(WIDTH, HEIGHT, 0);

	// Gotta error check this stuff
	if (!(mlx = scene.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(scene.image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, scene.image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	if (!(scene.minimap = mlx_new_image(mlx, 100, 100)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, scene.minimap, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	parse(argv[1], &scene);

	mlx_loop_hook(mlx, loop_hook, &scene);
	mlx_resize_hook(mlx, resize_hook, &scene);
	mlx_mouse_hook(mlx, mouse_hook, &scene);
	mlx_cursor_hook(mlx, cursor_hook, &scene);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
