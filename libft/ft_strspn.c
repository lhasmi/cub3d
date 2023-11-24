/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:15:42 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 16:36:17 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t	counter;

	counter = 0;
	while (*s1 && ft_strchr(s2, *s1++))
		counter++;
	return (counter);
}
