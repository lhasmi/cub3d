/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:53:40 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/01 21:45:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char    **manual_realloc_2D_array(char **old_array, int old_rows, int new_rows, int new_cols)
{
    char **new_array;
    int i;
    
    (void)new_cols; // To silence the unused parameter warning (for now
    new_array = (char **)malloc(sizeof(char *) * new_rows);
    if (new_array == NULL)
    {
        ft_error("Error: Could not allocate memory for new array");
        exit(1);
    }
    i = 0;
    while (i < old_rows) 
    {
        new_array[i] = old_array[i];
        i++;
    }
    i = old_rows;
    while ( i < new_rows) 
    {
        new_array[i] = NULL;
        i++;
    }
    free(old_array);
    return new_array;
}

void update_map_cols(t_map *map, int new_row_length) 
{
    if (new_row_length > map->cols)
        map->cols = new_row_length;
}

void fill_map_tiles(t_map *map, int fd) 
{
    int i = 0;
    char *line;

    map->tiles = (char **)malloc(sizeof(char *));
    if (!map->tiles) 
        free_map_exit(map, "Error: Memory allocation failed", 1);
    line = get_next_line(fd);
    while (line) 
    {
        update_map_cols(map, ft_strlen(line));
        map->tiles = manual_realloc_2D_array(map->tiles, i, i + 1, map->cols);
        if (!map->tiles) 
            free_map_exit(map, "Error: Memory allocation failed", 1);
        map->tiles[i] = line;
        i++;
        map->rows++;
        line = get_next_line(fd);
    }
    map->tiles = manual_realloc_2D_array(map->tiles, i, i + 1, map->cols);
    if (!map->tiles) 
        free_map_exit(map, "Error: Memory allocation failed", 1);
    map->tiles[i] = NULL;    
}
