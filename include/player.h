/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:43:57 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:43:57 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "playerdef.h"
# include "scenedef.h"
# include "vecdef.h"

t_player	player_create(t_vec position, double yaw);

t_vec		player_get_look_at(t_player *player, double offset);

t_vec		player_get_left(t_player *player);
t_vec		player_get_right(t_player *player);
t_vec		player_get_front(t_player *player);
t_vec		player_get_back(t_player *player);

void		player_move_left(t_player *player);
void		player_move_right(t_player *player);
void		player_move_front(t_player *player);
void		player_move_back(t_player *player);

void		player_collide(t_scene *scene);

#endif