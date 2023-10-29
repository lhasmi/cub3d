/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:50:16 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/29 17:45:43 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *msg)
{
	int i = 0;
	ft_printf("Error from ft_error\n%s  itteration %i\n", msg, i);
	exit (EXIT_FAILURE);
}
