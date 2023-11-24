/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lailah <lailah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:03:55 by lailah            #+#    #+#             */
/*   Updated: 2023/01/11 14:10:26 by lailah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	dest = ft_strcpy(dest + dest_len, src);
	return (dest);
}
