/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:27:29 by codespace         #+#    #+#             */
/*   Updated: 2024/06/25 18:48:26 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map(char *path)
{
	int	fd;
	int	map_row;
	char	*line;
	t_map	*map;

	map = init_map();
	get_map_dim(map, path);
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		ft_error("[get_map(...)] : map->map malloc failed");
	garbage_collector(map->map, false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("[get_map(...)] : opened file returned < 0");
	line = get_next_line(fd);

	map_row = 0;
	while (line)
	{
		if (*line != '\n')
		{
			if (is_texture_line(line))
				get_texture_line(map, line);
			else if (is_map_line(line))
				get_map_line(map, line, &map_row);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}	

void	get_map_dim(t_map *map, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("[get_map_dim(...)] : opened file returned < 0");
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && is_map_line(line))
		{
			(map->height)++;
			if ((int)ft_strlen(line) > map->width)
				map->width = ft_strlen(line);
		}
		free (line);
		line = get_next_line(fd);
	}
	free(line);
}