/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:25:48 by codespace         #+#    #+#             */
/*   Updated: 2024/06/25 18:38:40 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_texture_line(char *line)
{
	return (ft_strnstr(line, "NO", 2) || ft_strnstr(line, "SO", 2)
			|| ft_strnstr(line, "EA", 2) || ft_strnstr(line, "WE", 2)
			|| ft_strnstr(line, "F", 1) || ft_strnstr(line, "C", 1));
}

bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != ' '
			&& line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static char	*dup_trimmed(char *s)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '))
		len--;
	copy = malloc(len + 1);
	if (!copy)
		ft_error("[dup_trimmed(...)] : malloc failed");
	garbage_collector(copy, false);
	ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}

void	get_texture_line(t_map *map, char *line)
{
	if (ft_strnstr(line, "NO", 2))
		map->texture->north_wall = dup_trimmed(line + 3);
	if (ft_strnstr(line, "SO", 2))
		map->texture->south_wall = dup_trimmed(line + 3);
	if (ft_strnstr(line, "EA", 2))
		map->texture->east_wall = dup_trimmed(line + 3);
	if (ft_strnstr(line, "WE", 2))
		map->texture->west_wall = dup_trimmed(line + 3);
	if (ft_strnstr(line, "C", 1))
		map->texture->ceiling = dup_trimmed(line + 2);
	if (ft_strnstr(line, "F", 1))
		map->texture->floor = dup_trimmed(line + 2);
}

void	get_map_line(t_map *map, char *line, int *row)
{
	int	i;

	map->map[*row] = malloc((map->width + 1) * sizeof(char));
	if (!map->map[*row])
		ft_error("[get_map_line(...)] : malloc failed");
	garbage_collector(map->map[*row], false);
	i = 0;
	while (line[i] && i < map->width) // i or i+1 to handle the '\n' ? do we handle when lines are smallest than map->width?
	{
		map->map[*row][i] = line[i];
		i++; 
	}
	map->map[*row][i] = '\0';
	(*row)++;
}