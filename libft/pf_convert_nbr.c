/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 09:03:35 by lhasmi            #+#    #+#             */
/*   Updated: 2023/05/06 09:33:43 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_putnbr(long int n)
{
	char	tmp;

	if (n < 0)
	{
		write(1, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
		pf_putnbr(n / 10);
	tmp = n % 10 + 48;
	write(1, &tmp, 1);
}

int		pf_get_nbr_len(long int n)
{
	int		len;
	long	i;

	i = (long)n;
	if (n < 0)
		i = (long)n * -1;
	len = 0;
	while (i > 0)
	{
		i = i / 10;
		len++;
	}
	if (n > 0)
		return (len);
	else if (!n)
		return (1);
	else
		return (len + 1);
}

int		pf_convert_nbr(va_list ap, char specifier)
{
	long int	n;

	if (specifier == 'u')
		n = (unsigned int)va_arg(ap, int);
	else
		n = va_arg(ap, int);
	pf_putnbr(n);
	return (pf_get_nbr_len(n));
}
