/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 00:20:52 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 17:26:58 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "cub3d.h"
#include "scene.h"
#include "vec.h"
#include "hooks.h"
#include "setup.h"

int	setup_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (scene->mlx == NULL)
		return (1);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (scene->image == NULL)
		return (mlx_close_window(scene->mlx), 1);
	if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == -1)
		return (mlx_close_window(scene->mlx), 1);
	scene->minimap = mlx_new_image(scene->mlx, 100, 100);
	if (scene->minimap == NULL)
		return (mlx_close_window(scene->mlx), 1);
	if (mlx_image_to_window(scene->mlx, scene->minimap, 0, 0) == -1)
		return (mlx_close_window(scene->mlx), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2 || !is_cub(argv[1]))
		return (ft_error("Invalid arguments"), 1);
	scene.size = vec_create(WIDTH, HEIGHT, 0);
	if (setup_mlx(&scene))
		return (ft_error(mlx_strerror(mlx_errno)), mlx_terminate(scene.mlx), 1);
	parse(argv[1], &scene);
	mlx_loop_hook(scene.mlx, loop_hook, &scene);
	mlx_resize_hook(scene.mlx, resize_hook, &scene);
	mlx_mouse_hook(scene.mlx, mouse_hook, &scene);
	mlx_cursor_hook(scene.mlx, cursor_hook, &scene);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	scene_free(&scene, -1);
	return (0);
}
