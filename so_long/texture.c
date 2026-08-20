/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:29:25 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:42:41 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "texture.h"
#include "error.h"
#include "structs.h"

t_bool	load_textures(t_mlx *mlx)
{
	char			*texture_map[5];
	mlx_texture_t	*png;
	int				i;

	texture_map[0] = FLOOR_PATH;
	texture_map[1] = WALL_PATH;
	texture_map[2] = COLLECTIBLE_PATH;
	texture_map[3] = PLAYER_PATH;
	texture_map[4] = EXIT_PATH;
	i = -1;
	while (++i < 5)
	{
		png = mlx_load_png(texture_map[i]);
		if (png)
			mlx->textures[i] = mlx_texture_to_image(mlx->mlx, png);
		if (png)
			mlx_delete_texture(png);
		if (!png || !mlx->textures[i])
		{
			while (--i >= 0)
				mlx_delete_image(mlx->mlx, mlx->textures[i]);
			return (false);
		}
	}
	return (true);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(MALLOC_FAILURE);
	data->collectible = 0;
	data->exit = 0;
	data->start = 0;
	return (data);
}
