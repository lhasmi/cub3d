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
	dir = vec_normalize(vec_create(look.x + plane.x * cx, look.y + plane.y * cx, 0));
	return (ray_create(scene->player.position, dir));
}

// int	ray_intersect(t_ray ray, t_plane plane, t_vec *intersect)
// {
// 	double	denominator;
// 	double	d;
// 	double	t;

// 	denominator = vec_dot(plane.normal, ray.direction);
// 	if (denominator >= 0)
// 		return (1);
// 	d = vec_dot(plane.normal, plane.position);
// 	t = (d - vec_dot(plane.normal, ray.origin)) / denominator;
// 	if (t < 0)
// 		return (1);
// 	*intersect = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
// 	t_vec sub = vec_sub(*intersect, plane.position);
// 	if (sub.x < 0 || sub.x > 10 || sub.y < 0 || sub.y > 10 || sub.z < 0 || sub.z > 10)
// 		return (1);
// 	return (0);
// }
