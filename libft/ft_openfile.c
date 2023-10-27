/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:36:38 by lailah            #+#    #+#             */
/*   Updated: 2023/10/27 14:02:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void		free_map(t_map *map, char *str);

void	ft_openfile(char *file, int i, char *err_message)
{
	if (i == 0)
	{
		if (open(file, O_RDONLY, 0777) == -1){
			free_map(map_i, err_message);
			exit(1);
		}			
	}
	else if (i == 1)
	{
		if (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777) == -1)
			ft_error("Error: open failed");
	}
	else if (i == 2)
	{
		if (open(file, O_WRONLY | O_CREAT | O_APPEND, 0777) == -1)
			ft_error("Error: open failed");
	}
}