#ifndef RAYDEF_H
# define RAYDEF_H

# include "constdef.h"
# include "vecdef.h"

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_hit
{
	t_vec		hit;
	t_vec		position;
	double		distance;
	t_bearing	bearing;
	double		offset;
}	t_hit;

#endif