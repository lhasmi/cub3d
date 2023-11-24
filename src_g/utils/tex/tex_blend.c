/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_blend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:29:26 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:31:50 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static uint32_t	c(uint32_t color, uint32_t offset)
{
	return ((color >> offset) & 0xff);
}

uint32_t	tex_blend(uint32_t back, uint32_t front)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	a = c(front, 0);
	r = (c(back, 24) * (255 - a) + c(front, 24) * a) / 255;
	g = (c(back, 16) * (255 - a) + c(front, 16) * a) / 255;
	b = (c(back, 8) * (255 - a) + c(front, 8) * a) / 255;
	return (r << 24 | g << 16 | b << 8 | 0xff);
}
