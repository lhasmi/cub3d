/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:53:15 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/12 17:44:55 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t	n)
{
	char	*s;
	char	*d;

	s = ((char *)src);
	d = ((char *)dst);
	if (!s && !d)
		return (0);
	while (n > 0)
	{
		d[n - 1] = s[n - 1];
		n --;
	}
	return ((void *)d);
}
