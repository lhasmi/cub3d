/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:03:27 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 09:32:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_puthex(unsigned long long n, char specifier)
{
	char	tmp;

	if (n >= 16)
		pf_puthex(n / 16, specifier);
	if (n % 16 <= 9)
		tmp = n % 16 + 48;
	else if (specifier == 'x')
		tmp = n % 16 + 'a' - 10;
	else if (specifier == 'X')
		tmp = n % 16 + 'A' - 10;
	write(1, &tmp, 1);
}

int	pf_get_hex_len(unsigned long long n)
{
	int					len;
	unsigned long long	i;

	i = (unsigned long long)n;
	len = 0;
	while (i > 0)
	{
		i = i / 16;
		len++;
	}
	if (!n)
		return (1);
	return (len);
}

int		pf_convert_hex(va_list ap, char specifier)
{
	unsigned int	n;

	n = va_arg(ap, unsigned int);
	pf_puthex(n, specifier);
	return (pf_get_hex_len(n));
}

int 	pf_convert_ptr(va_list ap)
{
	long				n;
	unsigned long long	u;

	n = (long)va_arg(ap, void *);
	u = (unsigned long long)n;
	if (!u && OS_FLAG == 'L')
	{
		write(1, "(nil)", 5);
		return (5);
	}	
	write(1, "0x", 2);
	pf_puthex(u, 'x');
	return (pf_get_hex_len(u) + 2);
}
