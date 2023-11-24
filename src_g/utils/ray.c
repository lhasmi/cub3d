/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:36:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:36:07 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenedef.h"
#include "raydef.h"
#include "player.h"
#include "vec.h"

t_ray	ray_create(t_vec origin, t_vec direction)
{
	return ((t_ray){origin, direction});
}

t_ray	ray_get(t_scene *scene, uint32_t x)
{
	t_vec	plane;
	t_vec	look;
	t_vec	dir;
	double	cx;

	plane = vec_mult_scalar(player_get_right(&scene->player), 0.66);
	look = player_get_look_at(&scene->player, 0);
	cx = x / scene->size.x * 2 - 1;
	dir = vec_normalize(vec_create(look.x + plane.x * cx,
				look.y + plane.y * cx, 0));
	return (ray_create(scene->player.position, dir));
}
