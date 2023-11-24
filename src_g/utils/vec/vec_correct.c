/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_correct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:53:08 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:16:44 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
