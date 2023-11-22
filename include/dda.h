#ifndef DDA_H
# define DDA_H

# include "scenedef.h"
# include "raydef.h"

t_hit	dda(t_scene *scene, t_ray *ray, int with_door);

#endif