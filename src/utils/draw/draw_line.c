#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "vecdef.h"
#include "scenedef.h"

void	draw_line(mlx_image_t *img, t_vec start, t_vec end, uint32_t color)
{
	int dx, dy, p, x, y;

	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    x = x0;
    y = y0;

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
		if (!(x < 0 || x >= img->width || y < 0 || y >= img->height))
            mlx_put_pixel(img, x, y, color);
        if (x == x1 && y == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x += sx; }
        if (e2 < dy) { err += dx; y += sy; }
    }
}
