/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenedef.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:11 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:44:12 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEDEF_H
# define SCENEDEF_H

# include <MLX42/MLX42.h>
# include "playerdef.h"
# include "vecdef.h"

# define WIDTH 512
# define HEIGHT 512

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*minimap;
	mlx_texture_t	*tex[6];
	uint32_t		color_floor;
	uint32_t		color_ceiling;
	t_player		player;
	t_vec			size;
	t_vec			map_size;
	char			**map;
	t_vec			mouse;
	int				interact;
	int				cursor_locked;
	int32_t		cloud_offset;
}	t_scene;

#endif