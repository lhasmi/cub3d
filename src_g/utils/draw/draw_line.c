/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:46:18 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 01:22:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "scenedef.h"
#include "vecdef.h"
#include "draw.h"

void	draw_line_setup(t_vec start, t_vec end, t_line *line)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = start.x;
	y0 = start.y;
	x1 = end.x;
	y1 = end.y;
	line->dx = (int) abs(x1 - x0);
	line->dy = (int) abs(y1 - y0);
	line->x = x0;
	line->y = y0;
	line->sx = (x0 < x1) * 2 - 1;
	line->sy = (y0 < y1) * 2 - 1;
	if (line->dx > line->dy)
		line->err = line->dx / 2;
	else
		line->err = -line->dy / 2;
}

void	draw_line(mlx_image_t *img, t_vec start, t_vec end, uint32_t color)
{
	t_line	line;
	int		err_tmp;

	draw_line_setup(start, end, &line);
	while (1)
	{
		draw_pixel(img, line.x, line.y, color);
		if (line.x == (int) end.x && line.y == (int) end.y)
			break ;
		err_tmp = line.err;
		if (err_tmp > -line.dx)
		{
			line.err -= line.dy;
			line.x += line.sx;
		}
		if (err_tmp < line.dy)
		{
			line.err += line.dx;
			line.y += line.sy;
		}
	}
}
