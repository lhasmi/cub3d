/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lailah <lailah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:52:07 by lhasmi            #+#    #+#             */
/*   Updated: 2023/01/11 14:20:43 by lailah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char *ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		while (s1[i + j] == s2[j] && i + j < n)
		{
			if (s2[j + 1] == '\0')
				return ((char *)s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	nlen;
// 	size_t	hlen;
// 	char	*hay;
// 	char	*nee;

// 	hay = ((char *)haystack);
// 	nee = ((char *)needle);
// 	nlen = ft_strlen(nee);
// 	hlen = ft_strlen(hay);
// 	if (nee[0] == '\0')
// 		return (hay);
// 	if (hlen < nlen || len < nlen)
// 		return (0);
// 	while (hay && len)
// 	{
// 		if (!ft_strncmp((const char *)hay, (const char *)nee, nlen))
// 		{
// 			if (len >= nlen)
// 				return (hay);
// 		}
// 	hay++;
// 	len--;
// 	}
// 	return (NULL);
// }