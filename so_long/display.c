/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:31:37 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:32:32 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "display.h"
#include "error.h"
#include "strings.h"
#include "structs.h"
#include "free.h"
#include "hooks.h"
#include "utils.h"
#include "texture.h"
#include <stdlib.h>

void	build_bg(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->map->map_size->y)
	{
		j = -1;
		while (++j < mlx->map->map_size->x)
		{
			if (mlx->map->map[i][j] == WALL)
				mlx_image_to_window(mlx->mlx, mlx->textures[1],
					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
			else
				mlx_image_to_window(mlx->mlx, mlx->textures[0],
					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
		}
	}
}

void	build_assets(t_mlx *mlx)
{
	int		i;
	int		j;
	int32_t	idx;

	i = -1;
	while (++i < mlx->map->map_size->y)
	{
		j = -1;
		while (++j < mlx->map->map_size->x)
		{
			if (mlx->map->map[i][j] == COLL)
			{
				idx = mlx_image_to_window(mlx->mlx, mlx->textures[2],
						j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
				mlx->coll_instances[i][j] = &mlx->textures[2]->instances[idx];
			}
		}
	}
	mlx_image_to_window(mlx->mlx, mlx->textures[4],
		mlx->map->exit->x * TILE_SIZE,
		mlx->map->exit->y * TILE_SIZE + SCORE_OFFSET);
	idx = mlx_image_to_window(mlx->mlx, mlx->textures[3],
			mlx->map->player_pos->x * TILE_SIZE,
			mlx->map->player_pos->y * TILE_SIZE + SCORE_OFFSET);
	mlx->player_instance = &mlx->textures[3]->instances[idx];
}

void	display_score(t_mlx *mlx)
{
	char	*moves;
	char	*score_str;

	moves = ft_itoa(mlx->map->moves);
	if (!moves)
		ft_error(MALLOC_FAILURE);
	score_str = ft_strjoin("moves : ", moves);
	free(moves);
	if (!score_str)
		ft_error(MALLOC_FAILURE);
	if (mlx->score_img)
		mlx_delete_image(mlx->mlx, mlx->score_img);
	mlx->score_img = mlx_put_string(mlx->mlx, score_str, 10, 15);
	free(score_str);
}

static void	alloc_coll_instances(t_mlx *mlx)
{
	int	y;
	int	x;

	mlx->coll_instances = malloc(sizeof(mlx_instance_t **)
			* mlx->map->map_size->y);
	if (!mlx->coll_instances)
		free_init_err(mlx, MALLOC_FAILURE);
	y = -1;
	while (++y < mlx->map->map_size->y)
	{
		mlx->coll_instances[y] = malloc(sizeof(mlx_instance_t *)
				* mlx->map->map_size->x);
		if (!mlx->coll_instances[y])
			free_init_err(mlx, MALLOC_FAILURE);
		x = -1;
		while (++x < mlx->map->map_size->x)
			mlx->coll_instances[y][x] = NULL;
	}
}

void	init_window(t_mlx *mlx)
{
	mlx->score_img = NULL;
	mlx->mlx = mlx_init(mlx->map->map_size->x * TILE_SIZE,
			mlx->map->map_size->y * TILE_SIZE + SCORE_OFFSET, "so_long", false);
	if (!mlx->mlx)
	{
		free_mlx(mlx);
		ft_error(EX11);
	}
	if (!load_textures(mlx))
		free_init_err(mlx, ETXTUR);
	alloc_coll_instances(mlx);
	build_bg(mlx);
	build_assets(mlx);
	display_score(mlx);
	mlx_key_hook(mlx->mlx, &ft_on_keypress, mlx);
	mlx_close_hook(mlx->mlx, &ft_on_close, mlx);
	mlx_loop(mlx->mlx);
}
