#include <math.h>
#include "vec.h"

#define EPSILON 0.0001

double	apply(double v)
{
	double	rounded;

	rounded = round(v);
	if (fabs(v - rounded) > EPSILON)
		return (v);
	return (rounded);
}

t_vec	vec_correct(t_vec v)
{
	return (vec_create(
		apply(v.x),
		apply(v.y),
		apply(v.z)
	));
}
