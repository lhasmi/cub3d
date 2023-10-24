/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:43:09 by lhasmi            #+#    #+#             */
/*   Updated: 2022/06/12 17:43:51 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	*stralloc(char	const*s1, size_t	len)
{
	char	*s1trimed;

	s1trimed = (char *)malloc(len + 1);
	if (!s1trimed)
		return (NULL);
	s1trimed = ft_memcpy(s1trimed, s1, len);
	*(s1trimed + len) = '\0';
	return (s1trimed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	while (*s1 != '\0')
	{
		if (ft_strchr(set, *s1))
			s1++;
		else
			break ;
	}
	i = ft_strlen(s1);
	while (*s1 != '\0' && ft_strchr(set, *(s1 + i)) != NULL)
		i--;
	if (i < ft_strlen(s1))
		return (stralloc (s1, i + 1));
	else
		return (stralloc (s1, ft_strlen(s1)));
}
