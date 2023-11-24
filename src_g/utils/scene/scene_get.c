#include <math.h>
#include "scenedef.h"
#include "vecdef.h"

char	scene_get(t_scene *scene, t_vec position)
{
	int x;
	int y;

	x = (int) position.x;
	y = (int) position.y;
	if (x < 0 || x >= (int) scene->map_size.x || y < 0 || y >= (int) scene->map_size.y)
		return (' ');
	return (scene->map[y][x]);
}

void	scene_set(t_scene *scene, t_vec position, char c)
{
	int x;
	int y;

	x = (int) position.x;
	y = (int) position.y;
	if (x < 0 || x >= (int) scene->map_size.x || y < 0 || y >= (int) scene->map_size.y)
		return ;
	scene->map[y][x] = c;
}
