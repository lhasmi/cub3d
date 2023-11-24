/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_get_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:00:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 21:00:49 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constdef.h"
#include "player.h"
#include "vec.h"

t_vec	player_get_left(t_player *player)
{
	return (player_get_look_at(player, -PI_HALF));
}

t_vec	player_get_right(t_player *player)
{
	return (player_get_look_at(player, PI_HALF));
}

t_vec	player_get_front(t_player *player)
{
	return (player_get_look_at(player, 0));
}

t_vec	player_get_back(t_player *player)
{
	return (player_get_look_at(player, PI));
}
