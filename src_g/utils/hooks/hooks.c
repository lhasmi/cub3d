/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:22:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:30:25 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "constdef.h"
#include "dda.h"
#include "player.h"
#include "ray.h"
#include "scene.h"
#include "vec.h"
#include "hooks.h"

void	loop_hook(void *param)
{
	t_scene	*scene;

	scene = param;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene->mlx);
	player_controls(scene);
	scene_draw(scene);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;

	scene = param;
	mlx_resize_image(scene->image, width, height);
	scene->size = vec_create(width, height, 0);
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_scene	*scene;
	t_vec	center;

	scene = param;
	if (button != MLX_MOUSE_BUTTON_LEFT && action != MLX_PRESS)
		return ;
	if (scene->cursor_locked)
		return ;
	center = vec_div_scalar(scene->size, 2);
	mlx_set_cursor_mode(scene->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(scene->mlx, (int32_t) center.x, (int32_t) center.y);
	scene->cursor_locked = 1;
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_scene	*scene;
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
	scene->cloud_offset -= diff.x * (PI / 180.0) * 500;
	mlx_set_mouse_pos(scene->mlx, (int32_t) center.x, (int32_t) center.y);
}
