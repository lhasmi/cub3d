/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:06 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 20:11:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include "scenedef.h"
# include "raydef.h"
# include "vecdef.h"

typedef struct s_dda
{
	t_vec	scale;
	t_vec	step;
	t_vec	length;
	t_vec	position;
	double	distance;
}	t_dda;

t_hit	dda(t_scene *scene, t_ray *ray, int with_door);
t_hit	dda_hit(t_scene *scene, t_ray *ray, double distance,
			t_vec position);

#endif