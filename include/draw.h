/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:44:04 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/24 20:45:30 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "MLX42/MLX42.h"
# include "vecdef.h"

void	draw_rect(mlx_image_t *img, t_vec position, t_vec size, uint32_t color);
void	draw_square(mlx_image_t *img, t_vec	position, uint32_t size,
			uint32_t color);
void	draw_line(mlx_image_t *img, t_vec start, t_vec end, uint32_t color);

#endif