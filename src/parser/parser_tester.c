/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:50:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/01 21:15:02 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "../../include/cub3d.h"


void test_init_map_struct() {
    t_map *map = init_map_struct();
    assert(map != NULL);
    assert(map->tiles == NULL);
    // ... other assertions for initial values ...
    free(map);
}

void test_parse_valid_data(const char *file_name)
{
	printf("Starting test_parse_valid_data...\n");
	int fd;
	fd = open(file_name, O_RDONLY);
	if (fd < 0) 
	{
        perror("Error opening file");
		assert(false);
        return;
    }
    t_map *map = init_map_struct();
	init_mapreqs();
	printf("Map struct initialized...\n");
    map = parse_config_file(fd, map);
	printf("Finished parse_config_file...\n");
    assert(map->no_texture != NULL); // Texture paths should be populated
	close(fd);
	
	printf("Checking if north texture is loaded...\n");
	assert(map != NULL); // Ensure map is not NULL after parsing
	printf("Map is not NULL: %p\n", map);
    assert(map->no_texture != NULL); // Check if the north texture path is populated
    printf("North texture is loaded successfully: %s\n", map->no_texture);
	free_map_exit(map, "Finished tests, map freed", 0);// Make sure to write a function to free the map
	printf("Exiting test_parse_valid_data...\n");
}

int main(int argc, char *argv[]) 
{
	if ( argc != 2 || !is_cub(argv[1]))
	{
		ft_error("Error: Invalid arguments");
		return (1);
	}
    test_init_map_struct();
    test_parse_valid_data(argv[1]);
    // test_parse_invalid_data();
    // ... any additional tests ...
    return 0;
}