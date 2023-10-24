/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:57:11 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/21 14:01:00 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int		is_wall(t_img *img, int32_t y, int32_t x) 
{
	size_t	i;

	i = 0; 
	while (img->wi->count > i)
	{
		if (img->wi->instances[i].y == y)
		{
			if (img->wi->instances[i].x == x)
				return (1);
		}
		i++;
	}
	return (0);
}

int		is_coll(t_img *img, size_t *coll, int32_t y, int32_t x)
{
	size_t	i;

	i = 0;
	while (img->ci->count > i)
	{
		if (img->ci->instances[i].y == y)
		{
			if (img->ci->instances[i].x == x)
			{
				if (img->ci->instances[i].z != -1)
				{
					img->ci->instances[i].z = -1;
					(*coll)++;
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

int		is_exit(t_img *img, size_t *coll, int32_t y, int32_t x)
{
	size_t	i;

	i = 0;
	while (img->ei->count > i)
	{
		if (img->ei->instances[i].y == y)
		{
			if (img->ei->instances[i].x == x)
				return (1);
		}
		i++;
	}
	if (coll == NULL)
		return (0);
	return (0);
}
