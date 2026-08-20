/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:59 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:33:55 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "structs.h"

void	free_array(char	**array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
}

void	free_map(t_map *map)
{
	free_array(map->map);
	free(map->map);
	free(map->data);
	free(map->map_size);
	free(map->exit);
	free(map->player_pos);
}

void	free_mlx(t_mlx *mlx)
{
	int	y;
	int	height;

	if (mlx->coll_instances)
	{
		height = mlx->map->map_size->y;
		y = -1;
		while (++y < height)
			free(mlx->coll_instances[y]);
		free(mlx->coll_instances);
	}
	free_map(mlx->map);
	free(mlx->map);
	if (mlx->mlx)
		mlx_terminate(mlx->mlx);
}
