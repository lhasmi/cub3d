/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:49:00 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/12 17:45:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*srce;
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	size_t	j;

	srce = ((char *)src);
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (!dst || dstsize == 0)
		return (lensrc);
	i = lendst;
	j = 0;
	while (srce[j] && (i < dstsize -1))
	{
		dst[i] = srce[j];
		i++;
		j++;
	}
	if (dstsize >= lendst)
		dst[i] = '\0';
	if (dstsize < lendst)
		return (dstsize + lensrc);
	return (lendst + lensrc);
}
