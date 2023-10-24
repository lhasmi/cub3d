/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:19:13 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 14:19:36 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool is_ber(char *filename)
{
    int len = ft_strlen(filename);
    if (len >= 4 && filename[len - 4] == '.' && filename[len - 3] == 'b' 
				&& filename[len - 2] == 'e' && filename[len - 1] == 'r')
        return true;
    else
        return false;
}

void	put_img(mlx_t *mlx, t_img img, t_map map_i)
{
	int	i;
	int	j;

	mlx_resize_image(img.bi, map_i.width * TSIZE, map_i.height * TSIZE);
	mlx_image_to_window(mlx, img.bi, 0, 0);
	i = 0;
	while (map_i.tiles[i])
	{
		j = 0;
		while (map_i.tiles[i][j])
		{
			if (map_i.tiles[i][j] == '1')
				mlx_image_to_window(mlx, img.wi, j * TSIZE, i * TSIZE);
			if (map_i.tiles[i][j] == 'P')
				mlx_image_to_window(mlx, img.pi, j * TSIZE, i * TSIZE);
			if (map_i.tiles[i][j] == 'E')
				mlx_image_to_window(mlx, img.ei, j * TSIZE, i * TSIZE);
			if (map_i.tiles[i][j] == 'C')
				mlx_image_to_window(mlx, img.ci, j * TSIZE, i * TSIZE);
			j++;
		}
		i++;
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}
