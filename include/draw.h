#ifndef DRAW_H
# define DRAW_H

# include "MLX42/MLX42.h"
# include "vecdef.h"

void	draw_square(mlx_image_t *img, t_vec	position, uint32_t size, uint32_t color);
void	draw_line(mlx_image_t *img, t_vec start, t_vec end, uint32_t color);
void	draw_circle(mlx_image_t *img, t_vec position, uint32_t radius, uint32_t color);

#endif