/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:00:45 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 21:00:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "playerdef.h"

t_player	player_create(t_vec position, double yaw)
{
	return ((t_player){position, yaw});
}
