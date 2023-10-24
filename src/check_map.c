/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 15:30:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_walls(t_map map_i)
{
    size_t i;
    size_t j;

    i = -1;
    while (map_i.tiles[++i])
    {
        j = -1;
        while (map_i.tiles[i][++j])
        {
            if ((i == 0 || i == map_i.height - 1) && map_i.tiles[i][j] != '1')
                free_map(&map_i, "Invalid or open top/bottom wall");
            if ((j == 0 || j == map_i.width - 1) && map_i.tiles[i][j] != '1')
                free_map(&map_i, "Invalid or open left/right wall");
        }
    }
}

t_req	count_components(t_map map_i, t_req ecpo, size_t i, size_t j)
{
    while (map_i.tiles[++i])
    {
		j = -1;
        while (map_i.tiles[i][++j])
        {
            if (ft_toupper(map_i.tiles[i][j]) == 'E')
                ecpo.e++;
            else if (ft_toupper(map_i.tiles[i][j]) == 'C')
                ecpo.c++;
            else if (ft_toupper(map_i.tiles[i][j]) == 'P')
            {
                ecpo.p++;
                if (ecpo.p == 1)
                {
                    ecpo.px = j;
                    ecpo.py = i;
                }
            }
            else if (map_i.tiles[i][j] != '1' && map_i.tiles[i][j] != '0')
                ecpo.o++;
        }
    }
    return (ecpo);
}

void    validate_components(t_map map_i, t_req ecpo)
{
    if (ecpo.e != 1 || !ecpo.c || ecpo.p != 1 || ecpo.o)
        free_map(&map_i, "Invalid components detected on the map");
}

bool    check_additional_conditions(t_map *map_i)
{
    size_t  i;
    size_t  j;

    i = 0;
    while (i < map_i->height)
    {
        j = 0;
        while (j < map_i->width)
        {
            if (ft_strchr("01CEP", map_i->tiles[i][j]) == NULL)
                return (false);
            j++;
        }
        i++;
    }
    if (map_i->tiles[0][0] != '1' || map_i->tiles[0][map_i->width - 1] != '1'
        || map_i->tiles[map_i->height - 1][0] != '1'
        || map_i->tiles[map_i->height - 1][map_i->width - 1] != '1')
        return (false);
    if (map_i->height < 3 || map_i->width < 3)
        return (false);

    return (true);
}

bool    map_valid(t_map map_i)
{
    static t_req	ecpo;
	size_t			i;
	size_t			j;
	
	i = -1;
	j = -1;
	ft_memset(&ecpo, 0, sizeof(t_req));
    check_walls(map_i);
    ecpo = count_components(map_i, ecpo, i, j);
    validate_components(map_i, ecpo);
    if (!check_additional_conditions(&map_i))
        free_map(&map_i, "Additional map conditions not met");
    check_path(&map_i, &ecpo);
    return (1);
}
