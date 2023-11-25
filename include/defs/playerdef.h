/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerdef.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:17 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 17:07:55 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERDEF_H
# define PLAYERDEF_H

# include "vecdef.h"

typedef struct s_player
{
	t_vec	position;
	double	yaw;
}			t_player;

#endif
