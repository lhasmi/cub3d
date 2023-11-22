#include "scenedef.h"
#include "vec.h"
#include "draw.h"

void	draw_square(mlx_image_t *img, t_vec position, uint32_t size, uint32_t color)
{
	draw_rect(img, position, vec_create(size, size, 0), color);
}
