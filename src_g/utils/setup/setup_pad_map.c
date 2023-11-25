/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pad_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:52:53 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 16:53:28 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "scene.h"
#include "libft.h"
#include "setup.h"

static int	malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

static int	str_malloc(size_t len, char **str)
{
	if (malloc2(len + 1, (void **) str))
		return (1);
	(*str)[len] = '\0';
	return (0);
}

static int	str_arr_malloc(size_t len, char ***str)
{
	if (malloc2((len + 1) * sizeof(char *), (void **) str))
		return (1);
	(*str)[len] = NULL;
	return (0);
}

static void	str_fill(char *str, size_t start, size_t end, char c)
{
	unsigned long	i;

	i = start;
	while (i < end)
	{
		str[i] = c;
		i++;
	}
}

int	get_padded_map(char **tiles, int x, int y, t_scene *scene)
{
	int	i;

	if (str_arr_malloc(y, &scene->map))
		return (1);
	i = 0;
	while (i < y)
	{
		if (str_malloc(x, scene->map + i))
			return (scene_free(scene, i), 1);
		ft_strcpy(scene->map[i], tiles[i]);
		str_fill(scene->map[i], ft_strlen(tiles[i]), x, ' ');
		i++;
	}
	return (0);
}
