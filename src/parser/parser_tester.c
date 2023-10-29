/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:50:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 16:08:22 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "../../include/cub3d.h"


void test_init_map_struct() {
    t_map *map = init_map_struct();
    assert(map != NULL);
    assert(map->tiles == NULL);
    // ... other assertions for initial values ...
    free(map); // Remember to free the map after testing
}

void test_parse_valid_data(const char *file_name)
{
	int fd;
    t_map *map = init_map_struct();
	fd = open(file_name, O_RDONLY, 0777);
	if (fd < 0) 
	{
        ft_error("Error opening file");
        return;
    }
    parse_config_file(fd, map);
    assert(map->no_texture != NULL); // Texture paths should be populated
    // ... other assertions for populated values ...
	close(fd);
    free_map_exit(map, "map freed", 2);// Make sure to write a function to free the map
}

// Main function to run tests
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