/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:24:32 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 21:30:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || is_orientation(c) || c == ' ' || c == 'D');
}

bool	first_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_valid_middle_line(char *line)
{
	int		i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	if (len > 0 && (line[0] != '1' || line[len - 1] != '1'))
	{
		ft_error("Middle rows must start and end with '1'.");
		return (false);
	}
	while (line[i])
	{
		if (!is_valid_tile(line[i]))
		{
			ft_error("Invalid tile in middle line");
			return (false);
		}
		i++;
	}
	return (true);
}

int	trim_leading_ws(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

bool	check_space_adjacency(char *row)
{
	int	len;
	int	i;

	len = ft_strlen(row);
	i = 0;
	while (i < len)
	{
		if (row[i] == ' ' && i > 0 && i < len - 1 && !(row[i - 1] == '1'
				|| row[i - 1] == ' ' || row[i + 1] == '1' || row[i + 1] == ' '
				|| row[i + 1] == '0' || row[i - 1] == '0'
				|| is_valid_tile(row[i + 1]) || is_valid_tile(row[i - 1])))
		{
			return (false);
		}
		i++;
	}
	return (true);
}
