/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:36:38 by lailah            #+#    #+#             */
/*   Updated: 2023/05/06 08:58:22 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_openfile(char *file, int i)
{
	if (i == 0)
	{
		if (open(file, O_RDONLY, 0777) == -1)
			ft_error("Error: open failed");
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