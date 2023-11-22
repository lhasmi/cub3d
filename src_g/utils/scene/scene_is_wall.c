#include "scene.h"

int	scene_is_wall(t_scene *scene, t_vec position, int with_door)
{
	char	tile;

	tile = scene_get(scene, position);
	return (tile == '1' || tile == 'D' || (with_door && tile == 'O'));
}
