/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:50:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 21:11:20 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "../../include/cub3d.h"

void test_parse_valid_data(const char *file_name)
{
	t_map	*map;
	int		fd;


	printf("\nStarting test_parse_valid_data...\n");
	printf("\nIs the file empty?...\n");
	if (is_cub_file_empty(file_name) == - 1)
	{
		ft_error("unable to open file");
		exit(1);
	}
	else if(is_cub_file_empty(file_name) == 1)
	{
		ft_error("Empty file");
		exit(1);
	}
	printf("\nNOT empty ...continue\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("\nError opening file");
		assert(false);
		return;
	}
	printf("\n***** INITIALIZATION OF THE STRUCTS ******\n");
	printf("\nTest if Map struct initialized...\n");
	init_mapreqs();
	printf("\ninit_mapreqs() passed\n");
	map = init_map_struct();
	printf("\nMap struct has been initialized successfully: ...%p\n", map);
	printf("\nPlayer position has been initialized successfully: x position %d, y position %d\n", map->mapreqs.pos_x, map->mapreqs.pos_y);

	printf("\n***** FILLING UP THE STRUCTURES ******\n");
	printf("\nStart filling the map with parse_config_file...\n");
	map = parse_config_file(fd, map);
	if (map == NULL)
	{
		free_map_exit(map, "Invalid map, map freed", 1);
	}
	printf("\nFinished parse_config_file...\n");
	close(fd);
	printf("\nFile closed...\n");

	printf("\n***** CHECKING STRUCTS CONTENT ******\n");
	printf("\nAll 4 textures paths are loaded successfully:\n north %s\n  east %s\n  west %s\n  south %s\n", map->no_texture,
		map->ea_texture, map->we_texture, map->so_texture);
	printf("\nChecking if colors are parsed correctly...\n");
	printf("\nfloor color: %d   %d    %d\n", map->floor_color->red, map->floor_color->green, map->floor_color->blue);
	printf("\nceiling color: %d   %d    %d\n", map->ceiling_color->red, map->ceiling_color->green, map->ceiling_color->blue);
	printf("\ncolor_hex: %x    %x\n", map->floor_color_hex, map->ceiling_color_hex);
	printf("\nChecking if map is valid...\n");
	// fflush(stdout);
	assert(map_valid(map));
	printf("\n**************************************************************************************\n");
	printf("\nMap is valid\n");
	printf("\n**************************************************************************************\n");
	printf("\nPlayer position is valid: x position %d, y position %d, and the orientation is : %c\n", \
		map->mapreqs.pos_x, map->mapreqs.pos_y, map->mapreqs.orientation);
	free_map_exit(map, "\nFinished tests, map freed", 0);
	printf("\nExiting test_parse_valid_data...\n\n\n\n");
}

int main(int argc, char *argv[])
{
	if ( argc != 2 || !is_cub(argv[1]))
	{
		ft_error("Invalid arguments");
		exit(1);
	}
	test_parse_valid_data(argv[1]);
	return (0);
}
