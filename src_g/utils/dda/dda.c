/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:53:48 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 20:13:40 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "constdef.h"
#include "raydef.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"
#include "dda.h"

static double	dda_get_scale(double a, double b)
{
	double	d;

	d = a / b;
	return (sqrt(1 + d * d));
}

static void	dda_init_scale(t_ray *ray, t_vec *scale)
{
	*scale = vec_create(
			dda_get_scale(ray->direction.y, ray->direction.x),
			dda_get_scale(ray->direction.x, ray->direction.y),
			0
			);
}

static void	dda_init(t_ray *ray, t_vec *scale, t_vec *step, t_vec *length)
{
	dda_init_scale(ray, scale);
	*step = vec_create(0, 0, 0);
	*length = vec_create(0, 0, 0);
	if (ray->direction.x < 0)
	{
		step->x = -1;
		length->x = (ray->origin.x - trunc(ray->origin.x)) * scale->x;
	}
	else
	{
		step->x = 1;
		length->x = (trunc(ray->origin.x + 1) - ray->origin.x) * scale->x;
	}
	if (ray->direction.y < 0)
	{
		step->y = -1;
		length->y = (ray->origin.y - trunc(ray->origin.y)) * scale->y;
	}
	else
	{
		step->y = 1;
		length->y = (trunc(ray->origin.y + 1) - ray->origin.y) * scale->y;
	}
}

t_hit	dda(t_scene *scene, t_ray *ray, int doors)
{
	t_dda	d;

	dda_init(ray, &d.scale, &d.step, &d.length);
	d.position = vec_create(trunc(ray->origin.x), trunc(ray->origin.y), 0);
	while (1)
	{
		if (d.length.x < d.length.y)
		{
			d.position.x += d.step.x;
			d.distance = d.length.x;
			d.length.x += d.scale.x;
		}
		else
		{
			d.position.y += d.step.y;
			d.distance = d.length.y;
			d.length.y += d.scale.y;
		}
		if (scene_is_wall(scene, d.position, doors)
			|| d.distance > vec_length(scene->map_size) + 1)
			break ;
	}
	return (dda_hit(scene, ray, d.distance, d.position));
}
