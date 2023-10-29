/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:10:03 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 16:34:14 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while ((uint8_t)str1[i] && (uint8_t)str2[i] && \
			(uint8_t)str1[i] == (uint8_t)str2[i])
		i++;
	return ((uint8_t)str1[i] - (uint8_t)str2[i]);
}
