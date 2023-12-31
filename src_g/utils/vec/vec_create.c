/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:53:11 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:53:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecdef.h"

t_vec	vec_create(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}
