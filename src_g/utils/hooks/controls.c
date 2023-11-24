/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:22:37 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:35:05 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "dda.h"
#include "ray.h"
#include "scene.h"
#include "vec.h"
#include "player.h"

void	interact(t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	char	tile;

	if (!mlx_is_key_down(scene->mlx, MLX_KEY_E))
	{
		scene->interact = 0;
		return ;
	}
	if (scene->interact == 1)
		return ;
	scene->interact = 1;
	ray = ray_get(scene, (uint32_t)scene->size.x / 2);
	hit = dda(scene, &ray, 1);
	if (hit.distance < 0.2 || hit.distance > 1.0)
		return ;
	tile = scene_get(scene, hit.position);
	if (tile == 'D')
		scene_set(scene, hit.position, 'O');
	else if (tile == 'O')
		scene_set(scene, hit.position, 'D');
}

void	player_controls(t_scene *scene)
{
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
}
