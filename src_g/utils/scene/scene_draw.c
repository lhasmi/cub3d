#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constdef.h"
#include "scene.h"
#include "vec.h"
#include "ray.h"
#include "mat.h"
#include "draw.h"
#include "dda.h"
#include "player.h"
#include "minimap.h"

#define FOV 75.0

uint32_t	get_pixel(t_scene *scene, double x, double y, t_bearing bearing)
{
	mlx_texture_t	*tex;
	uint32_t		index;

	tex = scene->tex[bearing];
	x *= tex->width;
	y *= tex->height;
	index = ((uint32_t) y * tex->width + (uint32_t) x) * 4;
	return (
		tex->pixels[index++] << 24 |
		tex->pixels[index++] << 16 |
		tex->pixels[index++] << 8 |
		tex->pixels[index]
	);
}

void	scene_draw_column(t_scene *scene, uint32_t ix, t_hit *hit, uint32_t height)
{
	double		y;
	int32_t		iy;
	int32_t		start;
	int32_t		end;
	uint32_t	color;

	start = (int32_t) (scene->size.y - height) / 2;
	end = (int32_t) (scene->size.y + height) / 2;
	iy = start;
	while (iy < end)
	{
		if (iy < 0 || iy >= scene->size.y)
		{
			iy++;
			continue ;
		}
		y = (double) (iy - start) / (double) height;
		if(scene_get(scene, hit->position) == 'D')
			color = get_pixel(scene, hit->offset, y, 4);
		else
			color = get_pixel(scene, hit->offset, y, hit->bearing);
		mlx_put_pixel(scene->image, ix, iy, color);
		iy++;
	}
}

void	scene_draw(t_scene *scene)
{
	uint32_t	ix;
	t_vec		look;
	t_ray		ray;
	t_hit		hit;
	uint32_t	height;

	draw_rect(scene->image, vec_create(0, 0, 0), vec_create(scene->size.x, scene->size.y / 2, 0), scene->color_ceiling);
	draw_rect(scene->image, vec_create(0, scene->size.y / 2, 0), vec_create(scene->size.x, scene->size.y / 2, 0), scene->color_floor);
	minimap_draw(scene);
	look = player_get_look_at(&scene->player, 0);
	ix = 0;
	while (ix < (uint32_t) scene->size.x)
	{
		ray = ray_get(scene, ix);
		hit = dda(scene, &ray, 0);
		height = scene->size.y / vec_dot(hit.hit, look) * (scene->size.x / scene->size.y);
		minimap_draw_ray(scene, hit.hit);
		scene_draw_column(scene, ix, &hit, height);
		ix++;
	}
}
