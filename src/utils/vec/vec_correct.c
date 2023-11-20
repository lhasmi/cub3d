#include <math.h>
#include "vec.h"

static double	apply(double v, double epsilon)
{
	double	rounded;

	rounded = round(v);
	if (fabs(v - rounded) > epsilon)
		return (v);
	return (rounded);
}

t_vec	vec_correct(t_vec v, double epsilon)
{
	return (vec_create(
		apply(v.x, epsilon),
		apply(v.y, epsilon),
		apply(v.z, epsilon)
	));
}
