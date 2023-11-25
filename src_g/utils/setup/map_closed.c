/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 20:14:27 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 20:24:02 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vec.h"

static int	is_exposed(t_scene *scene, int x, int y)
{
	if (scene_get(scene, vec_create(x - 1, y, 0)) == ' ')
		return (1);
	if (scene_get(scene, vec_create(x, y - 1, 0)) == ' ')
		return (1);
	if (scene_get(scene, vec_create(x + 1, y, 0)) == ' ')
		return (1);
	if (scene_get(scene, vec_create(x, y + 1, 0)) == ' ')
		return (1);
	return (0);
}

int	map_closed(t_scene *scene)
{
	char	tile;
	int		x;
	int		y;

	y = 0;
	while (y < (int) scene->map_size.y)
	{
		x = 0;
		while (x < (int) scene->map_size.x)
		{
			tile = scene_get(scene, vec_create(x, y, 0));
			if ((tile == '0' || tile == 'D') && is_exposed(scene, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
