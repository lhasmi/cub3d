/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:43:59 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:44:00 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "scenedef.h"

void	minimap_draw(t_scene *scene);
void	minimap_draw_ray(t_scene *scene, t_vec vec);

#endif