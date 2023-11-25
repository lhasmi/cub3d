/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:40:19 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 19:40:40 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	gnl_free(int fd)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
	}
	close(fd);
}
