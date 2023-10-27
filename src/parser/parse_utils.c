/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:48:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/10/27 20:11:36 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool is_space (char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

ft_openfile(char *file, int i, char *err_message);
FILE *open_file(char *file)
{
	FILE *fd;

	fd = ft_openfile(file, 0, "Could not open the map file");
	return (fd);
}

bool is_path_valid(char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		return false;
	} else {
		close(fd);
		return true;
	}
}

//  the is_color_valid() function would check that each of color.red, color.green, and color.blue is between 0 and 255.
bool is_color_valid(t_color color)
{
	if (color.red < 0 || color.red > 255)
		return false;
	if (color.green < 0 || color.green > 255)
		return false;
	if (color.blue < 0 || color.blue > 255)
		return false;
	return true;
}