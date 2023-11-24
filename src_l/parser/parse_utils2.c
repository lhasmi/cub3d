/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:54:36 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/24 22:56:25 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_cub_file_empty(const char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (1);
	}
	free(line);
	close(fd);
	return (0);
}

bool	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

int	open_file(char *file, t_map *map_i, char *err_message)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		free_map_exit(map_i, err_message, 1);
	return (fd);
}

bool	is_path_valid(char *path)
{
	int		fd;
	char	*ext;

	fd = open(path, O_RDONLY);
	if (path == NULL || *path == '\0' || ft_strlen(path) < 5)
		return (false);
	ext = ft_strrchr(path, '.');
	if (ext == NULL || (ft_strcmp(ext, ".png") != 0 && ft_strcmp(ext,
				".xpm") != 0))
		return (false);
	if (fd == -1)
		return (false);
	else
	{
		close(fd);
		return (true);
	}
}

bool	is_color_valid(int color)
{
	if (color < 0 || color > 255)
		return (false);
	if (color < 0 || color > 255)
		return (false);
	if (color < 0 || color > 255)
		return (false);
	return (true);
}
