#include "constdef.h"
#include "cub3d.h"
#include "scene.h"
#include "vec.h"
#include "ray.h"
#include "dda.h"

// int	main(int argc, char **argv)
// {
// 	t_scene	scene;

// 	scene.player = vec_create(5, 5, 0);
// 	scene.map =
// 		"1111111111"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1000000001"
// 		"1111111111";
// 	return (0);
// }

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <MLX42/../lodepng/lodepng.h>
#include "player.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	for (int32_t i = 0; i < image->width; ++i)
	{
		for (int32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void	interact(t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	char	tile;

	if (!mlx_is_key_down(scene->mlx, MLX_KEY_E))
	{
		scene->interact = 0;
		return;
	}
	if (scene->interact == 1)
		return;
	scene->interact = 1;
	ray = ray_get(scene, (uint32_t) scene->size.x / 2);
	hit = dda(scene, &ray, 1);
	if (hit.distance > 1.0)
		return;
	tile = scene_get(scene, hit.position);
	if (tile == 'D')
		scene_set(scene, hit.position, 'O');
	else if (tile == 'O')
		scene_set(scene, hit.position, 'D');
}

void loop_hook(void *param)
{
	t_scene *scene = param;

	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	// 	scene->player.pitch -= 0.05;
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	// 	scene->player.pitch += 0.05;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
		scene->player.yaw -= 0.05;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
		scene->player.yaw += 0.05;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT_SHIFT))
	scene->player.position.y -= 1;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_SPACE))
		scene->player.position.y += 1;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_S))
		player_move_back(&scene->player);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_W))
		player_move_front(&scene->player);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_A))
		player_move_left(&scene->player);
	if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
		player_move_right(&scene->player);
	player_collide(scene);
	interact(scene);

	// if (mlx_is_key_down(scene->mlx, MLX_KEY_S))
		// scene->player.position.y += .1;
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_W))
		// scene->player.position.y += -.1;
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_A))
		// scene->player.position.x += -.1;
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_D))
		// scene->player.position.x += .1;

	int32_t x;
	int32_t y;

	mlx_get_mouse_pos(scene->mlx, &x, &y);

	scene->mouse.x = (double) x;
	scene->mouse.y = (double) y;
	scene->mouse.z = 0.0;

	// printf("%d, %d\n", x, y);

	// vec_print(scene->player.position);

	scene_draw(scene);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_scene *scene;

	scene = param;
	mlx_resize_image(scene->image, width, height);
	scene->size = vec_create(width, height, 0);
}

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
}

int	malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

int	str_malloc(size_t len, char **str)
{
	if (malloc2(len + 1, (void **) str))
		return (1);
	(*str)[len] = '\0';
	return (0);
}

int	str_arr_malloc(size_t len, char ***str)
{
	if (malloc2((len + 1) * sizeof(char *), (void **) str))
		return (1);
	(*str)[len] = NULL;
	return (0);
}

void	str_fill(char *str, size_t start, size_t end, char c)
{
	unsigned long	i;

	i = start;
	while (i < end)
	{
		str[i] = c;
		i++;
	}

}

int	get_padded_map(char **tiles, int x, int y, char ***map)
{
	int	i;

	if (str_arr_malloc(y, map))
		return (1);
	i = 0;
	while (i < y)
	{
		if (str_malloc(x, (*map) + i))
			return (1);
		ft_strcpy((*map)[i], tiles[i]);
		str_fill((*map)[i], ft_strlen(tiles[i]), x, ' ');
		i++;
	}
	return (0);
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
	if (map == NULL || !map_valid(map))
		free_map_exit(map, "Invalid map", 1);

	scene->map_size = vec_create(map->cols, map->rows, 0);
	if (get_padded_map(map->tiles, map->cols, map->rows, &scene->map))
		free_map_exit(map, "Invalid map, map freed", 1);
	scene->color_floor = map->floor_color_hex;
	scene->color_ceiling = map->ceiling_color_hex;
	scene->tex[0] = mlx_load_png(map->no_texture);
	scene->tex[1] = mlx_load_png(map->ea_texture);
	scene->tex[2] = mlx_load_png(map->so_texture);
	scene->tex[3] = mlx_load_png(map->we_texture);
	// scene->tex[4] = mlx_load_png(map->_texture);
	scene->tex[4] = mlx_load_png("img/img.png");
	scene->player = player_create(vec_create(map->mapreqs.pos_x + 0.5, map->mapreqs.pos_y + 0.5, 0), get_yaw(map->mapreqs.orientation));
	scene->interact = 0;
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

	mlx_resize_hook(mlx, resize_hook, &scene);
	mlx_loop_hook(mlx, loop_hook, &scene);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
