/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:41:54 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 19:57:21 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "scenedef.h"

void	scene_free(t_scene *scene, int i)
{
	if (scene->map != NULL)
	{
		if (i == -1)
			i = (int) scene->map_size.y;
		while (i--)
			free(scene->map[i]);
		free(scene->map);
		scene->map = NULL;
	}
	if (scene->tex[0] != NULL)
		mlx_delete_texture(scene->tex[0]);
	if (scene->tex[1] != NULL)
		mlx_delete_texture(scene->tex[1]);
	if (scene->tex[2] != NULL)
		mlx_delete_texture(scene->tex[2]);
	if (scene->tex[3] != NULL)
		mlx_delete_texture(scene->tex[3]);
	if (scene->tex[4] != NULL)
		mlx_delete_texture(scene->tex[4]);
	if (scene->tex[5] != NULL)
		mlx_delete_texture(scene->tex[5]);
}
