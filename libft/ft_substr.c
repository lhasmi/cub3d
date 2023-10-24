/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:52:18 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/12 17:43:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*bufalloc(char	*buffer)
{
	buffer = (char *)malloc(1);
	if (!buffer)
		return (NULL);
	buffer [0] = '\0';
	return (buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	idxb;

	if (!s)
		return (NULL);
	buffer = NULL;
	if (start > ft_strlen(s))
		return (bufalloc(buffer));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	buffer = (char *)malloc(len + 1);
	if (!buffer || !s)
		return (NULL);
	idxb = 0;
	while (idxb < len)
	{
		*(buffer + idxb) = *(s + (start));
		idxb++;
		s++;
	}
	*(buffer + idxb) = '\0';
	return (buffer);
}
