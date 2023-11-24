/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_get_look_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:00:52 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 21:01:00 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "playerdef.h"
#include "vec.h"

t_vec	player_get_look_at(t_player *player, double offset)
{
	return (vec_create(
			cos(player->yaw + offset),
			sin(player->yaw + offset),
			0
		));
}
