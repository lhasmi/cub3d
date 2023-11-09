/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:50:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/09 17:16:24 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "../../include/cub3d.h"


// void test_init_map_struct() {
//     t_map *map = init_map_struct();
//     assert(map != NULL);
//     assert(map->tiles == NULL);
//     // ... other assertions for initial values ...
//     free(map);
// }
// test map_valid function

void test_parse_valid_data(const char *file_name)
{
	t_map	*map;
	int		fd;

	printf("\nStarting test_parse_valid_data...\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("\nError opening file");
		assert(false);
		return;
	}
	printf("\nTest if Map struct initialized...\n");
	init_mapreqs();
	printf("\ninit_mapreqs() passed\n");
	map = init_map_struct();
	printf("\ninit_map_struct() passed\n");
	// Assert that the map pointer is not NULL
	printf("\nAssert that the map pointer is not NULL\n");
	fflush(stdout);
	assert(map != NULL);
	printf("\nAssert that the map pointer is not NULL passed\n");

	// Assert that all pointer members are initialized to NULL
	fflush(stdout);
	printf("\nAssert that all pointer members are initialized to NULL\n");
	assert(map->tiles == NULL);
	assert(map->no_texture == NULL);
	assert(map->so_texture == NULL);
	assert(map->we_texture == NULL);
	assert(map->ea_texture == NULL);
	assert(map->floor_color == NULL);
	assert(map->ceiling_color == NULL);
	printf("\nAssert that all pointer members are initialized to NULL passed\n");
	// Assert that integer members are initialized to their expected default values
	assert(map->rows == 0);
	assert(map->cols == 0);
	printf("\n Map struct has been initialized successfully: ...%p\n", map);

	// Assert that the mapreqs struct is initialized to its expected default values
	printf("\nChecking if player position is initialized...\n");
	fflush(stdout);
	assert(map->mapreqs.pos_x == 0);
	assert(map->mapreqs.pos_y == 0);
	assert(map->mapreqs.space == 0);
	assert(map->mapreqs.wall == 0);
	assert(map->mapreqs.orientation == 0);
	printf("\nPlayer position has been initialized successfully: x position %d, y position %d\n", map->mapreqs.pos_x, map->mapreqs.pos_y);
	// Fill the map , colors, player positions, orientation and textures
	printf("\nStart filling the map with parse_config_file...\n");
    map = parse_config_file(fd, map);
	assert(map != NULL); // Ensure map is not NULL after parsing
	assert(map->tiles != NULL); // Ensure map->tiles is not NULL after parsing
	assert(map->floor_color != NULL); // Ensure map->floor_color is not NULL after parsing
	printf("\nfloor color: %d   %d    %d\n", map->floor_color->red, map->floor_color->green, map->floor_color->blue);
	printf("\nceiling color: %d   %d    %d\n", map->ceiling_color->red, map->ceiling_color->green, map->ceiling_color->blue);
	printf("\ncolor_hex: %x    %x\n", map->floor_color_hex, map->ceiling_color_hex);
	printf("\ntiles: %p\n", map->tiles);
	printf("\nMap is not NULL: %p\n", map);
	printf("\nFinished parse_config_file...\n");
	close(fd);
	printf("\nFile closed...\n");

	fflush(stdout);
	// the mapreqs and player position are updated in the map_valid function, test it
	// printf("Checking if map is valid...\n");
	// assert(map_valid(map));
	// printf("Map is valid\n");
	// test the position of the player is valid AND parsed correctly
	// printf("Checking if player position is valid...\n");
	// assert(map->mapreqs.pos_x >= 0 && map->mapreqs.pos_y >= 0); // Check if positions are non-negative.
	// assert(is_orientation(map->mapreqs.orientation)); // Check if orientation is valid.
	// printf("Player position is valid: x position %d, y position %d, orientation %d\n", \
	// 	map->mapreqs.pos_x, map->mapreqs.pos_y, map->mapreqs.orientation);

	// test the map is parsed correctly
	printf("Checking if all 4 textures paths are loaded...\n");
    assert(map->no_texture != NULL); // Check if the north texture path is populated
    assert(map->ea_texture != NULL);
    assert(map->we_texture != NULL);
    assert(map->so_texture != NULL);
    printf("All 4 textures paths are loaded successfully:\n north %s\n  east %s\n  west %s\n  south %s\n", map->no_texture,
		map->ea_texture, map->we_texture, map->so_texture);
	free_map_exit(map, "Finished tests, map freed", 0);
	printf("Exiting test_parse_valid_data...\n");
}

int main(int argc, char *argv[])
{
	if ( argc != 2 || !is_cub(argv[1]))
	{
		ft_error("Error: Invalid arguments");
		exit(1);
	}
    test_parse_valid_data(argv[1]);
    return (0);
}
