/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:53:51 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/12 17:43:56 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*allocnull(char const *s1, char const *s2)
{
	char	*buffer;

	buffer = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!buffer)
		return (NULL);
	buffer [0] = '\0';
	return (buffer);
}

static char	*compare(char const *s1, char const *s2)
{
	char	*buffer;

	if (s1[0] == '\0' && s2[0] != '\0')
	{
		buffer = (char *)malloc(ft_strlen("") + ft_strlen(s2) + 1);
		if (!buffer)
			return (NULL);
		ft_memcpy(buffer, (char *)s2, ft_strlen(s2) + 1);
		return (buffer);
	}
	else if (s2[0] == '\0' && s1[0] != '\0')
	{
		buffer = (char *)malloc(ft_strlen("") + ft_strlen(s1) + 1);
		if (!buffer)
			return (NULL);
		ft_memcpy(buffer, (char *)s1, ft_strlen(s1) + 1);
		return (buffer);
	}
	else if (s1[0] == '\0' && s2[0] == '\0')
		return (allocnull(s1, s2));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\0' || s2[0] == '\0')
		return (compare (s1, s2));
	else
	{
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
		newstr = malloc(sizeof(char) * size);
		if (!newstr)
			return (NULL);
		ft_memcpy(newstr, (char *)s1, ft_strlen(s1) + 1);
		ft_strlcat(newstr, (char *)s2, size);
		return (newstr);
	}
}
