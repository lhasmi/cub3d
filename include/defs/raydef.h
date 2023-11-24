/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:44:14 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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