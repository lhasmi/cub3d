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
		color = get_pixel(scene, hit->offset, y, hit->bearing);
		mlx_put_pixel(scene->image, ix, iy, color);
		iy++;
	}
}

void	scene_draw(t_scene *scene)
{
	uint32_t	ix;

	draw_square(scene->image, vec_create(0, 0, 0), 512, 0x333333ff);
	minimap_draw(scene);

	// t_vec	plane = vec_create(0, 0.66, 0);
	t_vec	plane = vec_mult_scalar(player_get_right(&scene->player), 0.66);
	t_vec	look = player_get_look_at(&scene->player, 0);

	for (int i = 0; i < scene->size.x; i++)
	{
		double cx = i / scene->size.x * 2 - 1;
		t_vec dir = vec_normalize(vec_create(look.x + plane.x * cx, look.y + plane.y * cx, 0));
		t_ray	ray = ray_create(scene->player.position, dir);


		t_hit	hit = dda(scene, &ray);
		uint32_t height = scene->size.y / vec_dot(hit.hit, look);
		minimap_draw_ray(scene, hit.hit);
		scene_draw_column(scene, i, &hit, height);
	}
	return ;

	// draw_square(scene->image, vec_create(0, 0, 0), 512, 0x333333ff);

	// for (int ix = 0; ix < 10; ix++)
	// {
	// 	for (int iy = 0; iy < 10; iy++)
	// 	{
	// 		t_vec pos = vec_create(ix, iy, 0);
	// 		int	is_wall	= scene_get(scene, pos) == '1';
	// 		uint32_t x = ix * 32;
	// 		uint32_t y = iy * 32;

	// 		draw_square(scene->image, vec_create(x, y, 0), 32, (is_wall ? 0xdd0000ff : 0x111111ff) + ((ix + iy) % 2) * 0x11111100);
	// 	}
	// }

	// t_vec	origin = scene->player.position;
	// t_ray	ray = ray_create(origin, vec_normalize(vec_sub(vec_div_scalar(scene->mouse, 32), origin)));
	// draw_line(scene->image, vec_mult_scalar(origin, 32), scene->mouse, 0x00ff00ff);
	// dda(scene, &ray);
	// // printf("yay\n");
	// return ;



	// const double	fov = 75;
	// double 			fov_dist;

	// fov_dist = tan(PI * 0.5 * fov / 180.0);

	// for (uint32_t ix = 0; ix < scene->size.x; ix++)
	// {
	// 	for (uint32_t iy = 0; iy < scene->size.y; iy++)
	// 	{
	// 		double x = (((ix + 0.5) / scene->size.x) * 2 - 1) * fov_dist * (scene->size.x / scene->size.y);
	// 		double y = (1 - ((iy + 0.5) / scene->size.y) * 2) * fov_dist;

	// 		t_vec direction = vec_rotate(vec_normalize(vec_create(x, y, 1)), 0, scene->player.yaw);
	// 		t_ray ray = ray_create(scene->player.position, direction);

	// 		scene->planes[0] = (t_plane){
	// 			(t_vec){0, 0, 25},
	// 			(t_vec){0, 0, -1},
	// 			BEARING_SOUTH
	// 		};
	// 		scene->planes[1] = (t_plane){
	// 			(t_vec){0, 0, 15},
	// 			(t_vec){1, 0, 0},
	// 			BEARING_EAST
	// 		};

	// 		mlx_put_pixel(scene->image, ix, iy, 0x000000ff);

	// 		for (int i = 0; i < 2; i++)
	// 		{
	// 			t_vec intersect;
	// 			if (ray_intersect(ray, scene->planes[i], &intersect))
	// 				continue ;
	// 			mlx_put_pixel(scene->image, ix, iy, get_pixel(scene->tex, scene->planes[i], intersect));
	// 		}
	// 	}
	// }
}
