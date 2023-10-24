/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:53:06 by dcharala          #+#    #+#             */
/*   Updated: 2023/05/06 08:50:12 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char **s1, char const *s2)
{
	char	*conc;
	size_t	len;

	if (s2 == NULL)
		return (NULL);
	if (!*s1)
		return (ft_strdup(s2));
	len = gnl_strlen((char *)*s1) + gnl_strlen((char *)s2) + 1;
	conc = (char *)malloc(sizeof(char) * len);
	if (!conc)
		return (NULL);
	ft_memcpy(conc, (char *)*s1, gnl_strlen((char *)*s1));
	ft_memcpy(conc + gnl_strlen((char *)*s1), s2, gnl_strlen((char *)s2));
	conc[len - 1] = '\0';
	free(*s1);
	return (conc);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*line;
	int			sz;

	if (fd < 0)
		return (NULL);
	buff = ft_calloc(2, 1);
	sz = read(fd, buff, 1);
	if (!sz)
	{
		free(buff);
		return (NULL);
	}
	line = ft_strdup(buff);
	while (sz > 0 && buff[0] != '\n')
	{
		sz = read(fd, buff, 1);
		buff[1] = 0;
		if (sz && buff[0] != '\n')
			line = gnl_strjoin(&line, buff);
	}
	free(buff);
	return (line);
}
