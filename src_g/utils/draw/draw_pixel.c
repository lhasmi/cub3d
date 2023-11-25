/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 00:57:51 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 00:58:13 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

void	draw_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (!(x < 0 || x >= img->width || y < 0 || y >= img->height))
		mlx_put_pixel(img, x, y, color);
}
