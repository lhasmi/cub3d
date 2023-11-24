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

uint32_t	get_pixel_tex(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint32_t		index;

	x %= tex->width;
	y %= tex->height;
	index = (y * tex->width + x) * 4;
	return (
		tex->pixels[index] << 24 |
		tex->pixels[index + 1] << 16 |
		tex->pixels[index + 2] << 8 |
		tex->pixels[index + 3]
	);
}

uint32_t	get_pixel(t_scene *scene, double x, double y, t_bearing bearing)
{
	mlx_texture_t	*tex;

	tex = scene->tex[bearing];
	x *= tex->width;
	y *= tex->height;
	return (get_pixel_tex(tex, (uint32_t) x, (uint32_t) y));
}

// uint32_t	get_pixel(t_scene *scene, double x, double y, t_bearing bearing)
// {
// 	mlx_texture_t	*tex;
// 	uint32_t		index;

// 	tex = scene->tex[bearing];
// 	x *= tex->width;
// 	y *= tex->height;
// 	index = ((uint32_t) y * tex->width + (uint32_t) x) * 4;
// 	return (
// 		tex->pixels[index++] << 24 |
// 		tex->pixels[index++] << 16 |
// 		tex->pixels[index++] << 8 |
// 		tex->pixels[index]
// 	);
// }

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

uint32_t	c(uint32_t color, uint32_t offset)
{
	return ((color >> offset) & 0xff);
}

uint32_t	blend(uint32_t back, uint32_t front)
{
	uint32_t	alpha;

	alpha = c(front, 0);
	uint8_t r = (c(back, 24) * (255 - alpha) + c(front, 24) * alpha) / 255;
    uint8_t g = (c(back, 16) * (255 - alpha) + c(front, 16) * alpha) / 255;
    uint8_t b = (c(back, 8) * (255 - alpha) + c(front, 8) * alpha) / 255;
	return (r << 24 | g << 16 | b << 8 | 0xff);
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
			color = get_pixel_tex(scene->tex[5], x + scene->cloud_offset, y);
			color = blend(scene->color_ceiling, color);
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

	// draw_rect(scene->image, vec_create(0, 0, 0), vec_create(scene->size.x, scene->size.y / 2, 0), scene->color_ceiling);
	scene_draw_clouds(scene);
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
