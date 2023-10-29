/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:14:00 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 16:33:43 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>  // for NULL

// char	*ft_strtok(char *str, const char *sep)
// {
// 	static char	*p;

// 	p = 0;
// 	if (str)
// 		p = str;
// 	else if (!p)
// 		return (0);
// 	str = p + ft_strspn(p, sep);
// 	p = str + ft_strcspn(str, sep);
// 	if (p == str)
// 		return (p = 0);
// 	if (*p)
// 	{
// 		*p = 0;
// 		p += 1;
// 	}
// 	else
// 		p = 0;
// 	return (str);
// }

char *ft_strtok(char *str, const char *sep)
{
	static char *p = NULL;

	// Edge case 1: Null check for str and sep
	if (sep == NULL)
		return NULL;
	// Initialize p if a new string is given
	if (str != NULL)
		p = str;
	else if (p == NULL)
		return NULL;  // Edge case 3: No token found
	// Skip any leading delimiters
	str = p + ft_strspn(p, sep);
	// Edge case 4: Check if we are beyond string bounds
	if (*str == '\0') 
	{
		p = NULL;
		return NULL;  // Edge case 3: No token found
	}
	p = str + ft_strcspn(str, sep);// Find the end of the token
	if (*p != '\0') 
	{// Null-terminate the token
		*p = '\0';
		p += 1;  // Move to next character after the null-terminator
	} 
	else
		p = NULL;  // No more tokens
	return str;
}
