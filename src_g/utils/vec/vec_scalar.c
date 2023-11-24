/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:53:25 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:53:25 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecdef.h"

t_vec	vec_mult_scalar(t_vec v, double scalar)
{
	return ((t_vec){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_vec	vec_div_scalar(t_vec v, double scalar)
{
	return ((t_vec){v.x / scalar, v.y / scalar, v.z / scalar});
}
