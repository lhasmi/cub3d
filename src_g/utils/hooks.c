#include <stdio.h>
#include "MLX42/MLX42.h"
#include "constdef.h"
#include "scene.h"
#include "player.h"
#include "vec.h"
#include "ray.h"
#include "dda.h"

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

void	loop_hook(void *param)
{
	t_scene *scene;

	scene = param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
	{
		// if (scene->cursor_locked)
		// {
		// 	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_NORMAL);
		// 	scene->cursor_locked = 0;
		// 	return;
		// }
		mlx_close_window(scene->mlx);
	}
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_UP))
	// 	scene->player.pitch -= 0.05;
	// if (mlx_is_key_down(scene->mlx, MLX_KEY_DOWN))
	// 	scene->player.pitch += 0.05;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_LEFT))
	{
		scene->player.yaw -= 0.05;
		scene->cloud_offset -= 20;
	}
	if (mlx_is_key_down(scene->mlx, MLX_KEY_RIGHT))
	{
		scene->player.yaw += 0.05;
		scene->cloud_offset += 20;
	}
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

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_scene *scene;

	(void) mods;
	scene = param;
	if (button != MLX_MOUSE_BUTTON_LEFT && action != MLX_PRESS)
		return ;
	if (scene->cursor_locked)
		return ;
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	scene->cursor_locked = 1;
}

void	cursor_hook(double xpos, double ypos, void* param)
{
	t_scene *scene;
	t_vec	center;
	t_vec	current;
	t_vec	diff;

	scene = param;
	if (!scene->cursor_locked)
		return ;
	center = vec_div_scalar(scene->size, 2);
	current = vec_create(xpos, ypos, 0);
	diff = vec_sub(center, current);
	scene->player.yaw -= diff.x * (PI / 180.0);
	mlx_set_mouse_pos(scene->mlx, (int32_t) center.x, (int32_t) center.y);
}
