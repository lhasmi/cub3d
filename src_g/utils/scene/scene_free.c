/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 17:25:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "scenedef.h"

void	scene_free(t_scene *scene, int i)
{
	if (i == -1)
		i = (int) scene->map_size.y;
	while (i--)
		free(scene->map[i]);
	free(scene->map);
	mlx_delete_texture(scene->tex[0]);
	mlx_delete_texture(scene->tex[1]);
	mlx_delete_texture(scene->tex[2]);
	mlx_delete_texture(scene->tex[3]);
	mlx_delete_texture(scene->tex[4]);
	mlx_delete_texture(scene->tex[5]);
	// mlx_delete_image(scene->mlx, scene->image);
	// mlx_delete_image(scene->mlx, scene->minimap);
}
