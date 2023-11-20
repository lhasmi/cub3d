#include "scene.h"
#include "vec.h"

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

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t	*mlx;
	t_scene	scene;

	scene.player = (t_player){
		vec_create(2.5, 2.5, 0),
		0,
		0,
	};
	scene.size = vec_create(WIDTH, HEIGHT, 0);
	scene.map_size = vec_create(10, 10, 0);
	scene.map =
		"1111111111"
		"1000000001"
		"1011111001"
		"1010000001"
		"1010110001"
		"1000000001"
		"1000000001"
		"1000000001"
		"1000000001"
		"1111111111";

	// Gotta error check this stuff
	if (!(mlx = scene.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	scene.tex[0] = mlx_load_png("imgs/img.png");
	scene.tex[1] = mlx_load_png("imgs/img.png");
	scene.tex[2] = mlx_load_png("imgs/img.png");
	scene.tex[3] = mlx_load_png("imgs/img.png");
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

	mlx_loop_hook(mlx, loop_hook, &scene);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
