/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:40:05 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:40:22 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEX_H
# define TEX_H

# include "MLX42/MLX42.h"
# include "constdef.h"
# include "scenedef.h"

uint32_t	tex_get_pixel_wall(t_scene *scene, double x, double y,
				t_bearing bearing);
uint32_t	tex_get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y);

uint32_t	tex_blend(uint32_t back, uint32_t front);

#endif