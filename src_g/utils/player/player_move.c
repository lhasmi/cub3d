/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:01:10 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:01:42 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "vec.h"

void	player_move_left(t_player *player)
{
	t_vec	new;

	new = vec_add(player->position,
			vec_mult_scalar(player_get_left(player), 0.1));
	player->position = new;
}

void	player_move_right(t_player *player)
{
	t_vec	new;

	new = vec_add(player->position,
			vec_mult_scalar(player_get_right(player), 0.1));
	player->position = new;
}

void	player_move_front(t_player *player)
{
	t_vec	new;

	new = vec_add(player->position,
			vec_mult_scalar(player_get_front(player), 0.1));
	player->position = new;
}

void	player_move_back(t_player *player)
{
	t_vec	new;

	new = vec_add(player->position,
			vec_mult_scalar(player_get_back(player), 0.1));
	player->position = new;
}
