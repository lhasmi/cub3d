/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constdef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:19 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:44:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTDEF_H
# define CONSTDEF_H

# define PI 3.14159265358979323846
# define PI_HALF 1.5707963267948966

typedef enum e_bearing
{
	BEARING_NORTH = 0,
	BEARING_EAST = 1,
	BEARING_SOUTH = 2,
	BEARING_WEST = 3,
}	t_bearing;

#endif