#include "MLX42/MLX42.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"
#include "player.h"

#define MAP_SCALE 10
#define MAP_SIZE 10

static t_vec	get_center(void)
{
	return (vec_mult_scalar(vec_create(MAP_SIZE, MAP_SIZE, 0), MAP_SCALE / 2));
}

static uint32_t	minimap_get_tile_color(char tile)
{
	if (tile == '1')
		return (0xffffffff);
	if (tile == 'D')
		return (0xff0000ff);
	if (tile == 'O')
		return (0x00ff00ff);
	return (0x222222ff);
}

static void	minimap_draw_tile(t_scene *scene, t_vec position)
{
	char		tile;
	uint32_t	color;
	t_vec		origin;
	t_vec		player;
	t_vec		center;

	tile = scene_get(scene, position);
	color = minimap_get_tile_color(tile);
	center = get_center();
	player = vec_correct(vec_mult_scalar(scene->player.position, MAP_SCALE), 1.0);
	position = vec_mult_scalar(position, MAP_SCALE);
	origin = vec_add(position, vec_sub(center, player));
	draw_square(scene->minimap, origin, MAP_SCALE, color);
}

void	minimap_draw(t_scene *scene)
{
	uint32_t	ix;
	uint32_t	iy;
	t_vec		position;
	t_vec		center;

	ix = 0;
	center = get_center();
	draw_square(scene->minimap, vec_create(0, 0, 0), 10 * MAP_SCALE, 0x000000ff);
	while (ix < scene->map_size.x)
	{
		iy = 0;
		while (iy < scene->map_size.y)
		{
			// position = vec_sub(vec_create(ix, iy, 0), scene->player.position);
			position = vec_create(ix, iy, 0);
			minimap_draw_tile(scene, position);
			iy++;
		}
		ix++;
	}
	// position = vec_sub(vec_create(5, 7, 0), scene->player.position);
	// minimap_draw_tile(scene, position);

	draw_square(scene->minimap, vec_sub(center, vec_create(3, 3, 0)), 7, 0xff7800ff);
	// draw_square(scene->minimap, vec_sub(vec_mult_scalar(scene->player.position, MAP_SCALE), vec_create(3, 3, 0)), 7, 0xff7800ff);
}

void	minimap_draw_ray(t_scene *scene, t_vec vec)
{
	t_vec	start;
	t_vec	end;

	start = get_center();
	// start = vec_mult_scalar(scene->player.position, MAP_SCALE);
	end = vec_add(start, vec_mult_scalar(vec, MAP_SCALE));
	draw_line(scene->minimap, start, end, 0xff0000ff);
}
