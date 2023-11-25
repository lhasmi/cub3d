/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:46:21 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 00:58:46 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "vecdef.h"
#include "scenedef.h"
#include "draw.h"

void	draw_rect(mlx_image_t *img, t_vec position, t_vec size, uint32_t color)
{
	uint32_t	px;
	uint32_t	py;
	uint32_t	ix;
	uint32_t	iy;

	px = (uint32_t) position.x;
	py = (uint32_t) position.y;
	ix = 0;
	while (ix < (uint32_t) size.x)
	{
		iy = 0;
		while (iy < (uint32_t) size.y)
		{
			draw_pixel(img, px + ix, py + iy, color);
			iy++;
		}
		ix++;
	}
}
