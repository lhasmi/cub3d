#include <math.h>
#include <stdio.h>
#include "constdef.h"
#include "raydef.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"

static double	dda_get_scale(double a, double b)
{
	double	d;

	d = a / b;
	return (sqrt(1 + d * d));
}

static void dda_init_scale(t_ray *ray, t_vec *scale)
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

t_bearing	dda_get_bearing(t_vec diff)
{
	if (diff.x == 0.0)
		return (BEARING_EAST);
	if (diff.x == 1.0)
		return (BEARING_WEST);
	if (diff.y == 0.0)
		return (BEARING_SOUTH);
	if (diff.y == 1.0)
		return (BEARING_NORTH);
}

double	dda_get_offset(t_vec diff)
{
	if (fmod(diff.x, 1.0) == 0.0)
		return (diff.y);
	if (fmod(diff.y, 1.0) == 0.0)
		return (diff.x);
}

t_hit	dda_hit(t_scene *scene, t_ray *ray, double distance, t_vec position)
{
	t_vec		hit;
	t_vec		diff;

	hit = vec_mult_scalar(ray->direction, distance);
	diff = vec_correct(vec_sub(vec_add(ray->origin, hit), position));
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

t_hit	dda(t_scene *scene, t_ray *ray)
{
	t_vec	scale;
	t_vec	step;
	t_vec	length;
	t_vec	position;
	double	distance;

	dda_init(ray, &scale, &step, &length);
	position = vec_create(trunc(ray->origin.x), trunc(ray->origin.y), 0);
	while (1)
	{
		// draw_square(scene->image, vec_mult_scalar(position, 32), 32, 0x0000ffff);
		if (length.x < length.y)
		{
			position.x += step.x;
			distance = length.x;
			length.x += scale.x;
		}
		else
		{
			position.y += step.y;
			distance = length.y;
			length.y += scale.y;
		}


		if (scene_is_wall(scene, position))
		{
			// vec_print(position);
			break ;
		}
		// draw_square(scene->image, vec_sub(vec_add(ray->origin, vec_mult_scalar(ray->direction, distance * 32)), vec_create(3, 3, 0)), 6, 0xff7800ff);

		if (distance > vec_length(scene->map_size) + 1)
			break ;
	}
	return (dda_hit(scene, ray, distance, position));
}
