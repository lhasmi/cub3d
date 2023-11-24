/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:02 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:25:27 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "MLX42/MLX42.h"
# include "scenedef.h"

void	loop_hook(void *param);
void	resize_hook(int32_t width, int32_t height, void *param);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
			void *param);
void	cursor_hook(double xpos, double ypos, void *param);

void	interact(t_scene *scene);
void	player_controls(t_scene *scene);

#endif