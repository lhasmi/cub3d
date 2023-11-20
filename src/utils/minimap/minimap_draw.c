#include "MLX42/MLX42.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"
#include "player.h"

#define MAP_SCALE 10

static uint32_t	minimap_get_tile_color(char tile)
{
	if (tile == '1')
		return (0xffffffff);
	return (0x111111ff);
}

static void	minimap_draw_tile(t_scene *scene, t_vec position)
{
	char		tile;
	uint32_t	color;
	t_vec		origin;

	tile = scene_get(scene, position);
	color = minimap_get_tile_color(tile);
	origin = vec_mult_scalar(position, MAP_SCALE);
	draw_square(scene->minimap, origin, MAP_SCALE, color);
}

void	minimap_draw(t_scene *scene)
{
	uint32_t	ix;
	uint32_t	iy;
	t_vec		position;

	ix = 0;
	while (ix < scene->map_size.y)
	{
		iy = 0;
		while (iy < scene->map_size.y)
		{
			position = vec_create(ix, iy, 0);
			minimap_draw_tile(scene, position);
			iy++;
		}
		ix++;
	}
	draw_square(scene->minimap, vec_sub(vec_mult_scalar(scene->player.position, MAP_SCALE), vec_create(3, 3, 0)), 7, 0xff7800ff);
	draw_line(scene->minimap, vec_mult_scalar(scene->player.position, MAP_SCALE), vec_mult_scalar(vec_add(scene->player.position, player_get_look_at(&scene->player, 0)), MAP_SCALE), 0x00ff00ff);
}

void	minimap_draw_ray(t_scene *scene, t_vec vec)
{
	t_vec	start;
	t_vec	end;

	start = vec_mult_scalar(scene->player.position, MAP_SCALE);
	end = vec_add(start, vec_mult_scalar(vec, MAP_SCALE));
	draw_line(scene->minimap, start, end, 0xff0000ff);
}
