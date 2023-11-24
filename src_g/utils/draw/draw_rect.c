/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:46:21 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:48:20 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "vecdef.h"
#include "scenedef.h"

static void	draw_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (!(x < 0 || x >= img->width || y < 0 || y >= img->height))
		mlx_put_pixel(img, x, y, color);
}

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
