/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:43:46 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 16:47:39 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "scenedef.h"
# include "vecdef.h"

char	scene_get(t_scene *scene, t_vec position);
void	scene_set(t_scene *scene, t_vec position, char c);
void	scene_draw(t_scene *scene);
int		scene_is_wall(t_scene *scene, t_vec position, int with_door);

void	scene_free(t_scene *scene, int i);

#endif