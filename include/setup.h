/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:43:43 by gbohm             #+#    #+#             */
/*   Updated: 2023/11/25 20:24:21 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "scenedef.h"

int		get_padded_map(char **tiles, int x, int y, t_scene *scene);
int		parse(char *file_name, t_scene *scene);
void	gnl_free(int fd);
int		map_closed(t_scene *scene);

#endif