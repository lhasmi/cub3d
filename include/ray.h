/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:43:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:43:54 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "raydef.h"

t_ray	ray_create(t_vec origin, t_vec direction);
t_ray	ray_get(t_scene *scene, uint32_t x);

#endif