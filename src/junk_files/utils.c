/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:19:13 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/25 22:35:25 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


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
