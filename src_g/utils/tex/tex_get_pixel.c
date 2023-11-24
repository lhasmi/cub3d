/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:32:50 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 23:15:00 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "constdef.h"
#include "scenedef.h"

uint32_t	tex_get_pixel(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint32_t	index;

	x %= tex->width;
	y %= tex->height;
	index = (y * tex->width + x) * 4;
	return (
		tex->pixels[index] << 24
		| tex->pixels[index + 1] << 16
		| tex->pixels[index + 2] << 8
		| tex->pixels[index + 3]
	);
}

uint32_t	tex_get_pixel_wall(t_scene *scene, double x, double y,
				t_bearing bearing)
{
	mlx_texture_t	*tex;

	tex = scene->tex[bearing];
	x *= tex->width;
	y *= tex->height;
	return (tex_get_pixel(tex, (uint32_t) x, (uint32_t) y));
}
