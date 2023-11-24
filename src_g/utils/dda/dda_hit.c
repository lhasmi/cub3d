/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:53:48 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:56:45 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "constdef.h"
#include "raydef.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"

static t_bearing	dda_get_bearing(t_vec diff)
{
	if (diff.x == 0.0)
		return (BEARING_EAST);
	if (diff.x == 1.0)
		return (BEARING_WEST);
	if (diff.y == 0.0)
		return (BEARING_SOUTH);
	if (diff.y == 1.0)
		return (BEARING_NORTH);
	else
		return (0);
}

static double	dda_get_offset(t_vec diff)
{
	if (fmod(diff.x, 1.0) == 0.0)
		return (diff.y);
	if (fmod(diff.y, 1.0) == 0.0)
		return (diff.x);
	else
		return (0.0);
}

t_hit	dda_hit(t_scene *scene, t_ray *ray, double distance,
	t_vec position)
{
	t_vec		hit;
	t_vec		diff;

	(void) scene;
	hit = vec_mult_scalar(ray->direction, distance);
	diff = vec_correct(vec_sub(vec_add(ray->origin, hit), position), 0.0001);
	if (dda_get_bearing(diff) > 3)
		vec_print(diff);
	return ((t_hit){
		hit,
		position,
		distance,
		dda_get_bearing(diff),
		dda_get_offset(diff)
	});
}
