/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lailah <lailah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:46:41 by lhasmi            #+#    #+#             */
/*   Updated: 2022/05/20 13:55:00 by lailah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_bzero(void *s, size_t n)
{
	size_t			c;
	unsigned char	*d;
	
	d = (unsigned char *)s;
	c = 0;
	while (c < n)
		{
			d[c] = '\0';
			c++;
		}
}

void	*ft_calloc(size_t strlen, size_t bytesize)
{
	char	*s;

	if ((strlen >= SIZE_MAX) || (bytesize >= SIZE_MAX))
		return (NULL);
	s = malloc(strlen * bytesize);
	if (s == (NULL))
		return (NULL);
	ft_bzero(s, strlen * bytesize);
	return (s);
}
