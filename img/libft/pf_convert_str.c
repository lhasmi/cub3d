/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:03:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 09:03:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	pf_convert_str(va_list ap)
{
	char	*s;

	s = va_arg(ap, char *);
	if (!s)
		return (write(1, "(null)", 6));
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
