#include <math.h>
#include "scenedef.h"
#include "vecdef.h"

char	scene_get(t_scene *scene, t_vec position)
{
	int	index;

	index = floor(position.y) * floor(scene->map_size.x) + floor(position.x);
	return (scene->map[index]);
}
