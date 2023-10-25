/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:07:57 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/25 22:38:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_and_delete(char **arr, t_img *img)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	mlx_delete_image(img->mlx, img->pi);
	mlx_delete_image(img->mlx, img->wi);
	mlx_delete_image(img->mlx, img->ci);
	mlx_delete_image(img->mlx, img->ei);
	mlx_delete_image(img->mlx, img->bi);
	mlx_delete_texture(img->bt);
	mlx_delete_texture(img->pt);
	mlx_delete_texture(img->wt);
	mlx_delete_texture(img->ct);
	mlx_delete_texture(img->et);
}
