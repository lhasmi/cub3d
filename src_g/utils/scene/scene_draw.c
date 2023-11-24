/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:37:23 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:50:52 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constdef.h"
#include "scene.h"
#include "vec.h"
#include "ray.h"
#include "draw.h"
#include "dda.h"
#include "player.h"
#include "minimap.h"
#include "tex.h"

void	scene_draw_column(t_scene *scene, uint32_t ix, t_hit *hit,
			uint32_t height)
{
	double		y;
	int32_t		iy;
	int32_t		start;
	int32_t		end;
	uint32_t	color;

	start = (int32_t)(scene->size.y - height) / 2;
	end = (int32_t)(scene->size.y + height) / 2;
	iy = start;
	while (iy < end)
	{
		if (iy < 0 || iy >= scene->size.y)
		{
			iy++;
			continue ;
		}
		y = (double)(iy - start) / (double) height;
		if (scene_get(scene, hit->position) == 'D')
			color = tex_get_pixel_wall(scene, hit->offset, y, 4);
		else
			color = tex_get_pixel_wall(scene, hit->offset, y, hit->bearing);
		mlx_put_pixel(scene->image, ix, iy, color);
		iy++;
	}
}

void	scene_draw_clouds(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;
	while (x < scene->size.x)
	{
		y = 0;
		while (y < scene->size.y / 2)
		{
			color = tex_get_pixel(scene->tex[5], x + scene->cloud_offset, y);
			color = tex_blend(scene->color_ceiling, color);
			mlx_put_pixel(scene->image, x, y, color);
			y++;
		}
		x++;
	}
	scene->cloud_offset--;
}

void	scene_draw(t_scene *scene)
{
	uint32_t	ix;
	t_vec		look;
	t_ray		ray;
	t_hit		hit;
	uint32_t	height;

	scene_draw_clouds(scene);
	draw_rect(scene->image, vec_create(0, scene->size.y / 2, 0),
		vec_create(scene->size.x, scene->size.y / 2, 0), scene->color_floor);
	minimap_draw(scene);
	look = player_get_look_at(&scene->player, 0);
	ix = 0;
	while (ix < (uint32_t) scene->size.x)
	{
		ray = ray_get(scene, ix);
		hit = dda(scene, &ray, 0);
		height = scene->size.y / vec_dot(hit.hit, look)
			* (scene->size.x / scene->size.y);
		minimap_draw_ray(scene, hit.hit);
		scene_draw_column(scene, ix, &hit, height);
		ix++;
	}
}
