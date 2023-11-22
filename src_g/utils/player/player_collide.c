#include <math.h>
#include "scene.h"
#include "vec.h"

static t_vec player_get_correction(t_scene *scene, t_vec direction)
{
	t_vec	adjusted;

	adjusted = vec_add(scene->player.position, direction);
	if (!scene_is_wall(scene, adjusted, 0))
		return (vec_create(0, 0, 0));
	if (direction.x < 0)
		return (vec_create(floor(adjusted.x + 1) - adjusted.x, 0, 0));
	if (direction.x > 0)
		return (vec_create(floor(adjusted.x) - adjusted.x, 0, 0));
	if (direction.y < 0)
		return (vec_create(0, floor(adjusted.y + 1) - adjusted.y, 0));
	if (direction.y > 0)
		return (vec_create(0, floor(adjusted.y) - adjusted.y, 0));
	else
		return (vec_create(0, 0, 0));
}

void	player_collide(t_scene *scene)
{
	t_vec	*pos;

	pos = &scene->player.position;
	*pos = vec_add(*pos, player_get_correction(scene, vec_create(-.2, 0, 0)));
	*pos = vec_add(*pos, player_get_correction(scene, vec_create(0, -.2, 0)));
	*pos = vec_add(*pos, player_get_correction(scene, vec_create(.2, 0, 0)));
	*pos = vec_add(*pos, player_get_correction(scene, vec_create(0, .2, 0)));
}
