/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:43:53 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:34:40 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hooks.h"
#include "display.h"
#include "texture.h"
#include "free.h"
#include "print.h"
#include "utils.h"
#include "structs.h"
#include "MLX42/MLX42.h"

void	ft_handle_move(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_UP
		&& mlx->map->map[mlx->map->player_pos->y - 1][mlx->map->player_pos->x]
		!= WALL)
		--mlx->map->player_pos->y;
	else if (keydata.key == MLX_KEY_DOWN
		&& mlx->map->map[mlx->map->player_pos->y + 1][mlx->map->player_pos->x]
		!= WALL)
		++mlx->map->player_pos->y;
	else if (keydata.key == MLX_KEY_LEFT
		&& mlx->map->map[mlx->map->player_pos->y][mlx->map->player_pos->x - 1]
		!= WALL)
		--mlx->map->player_pos->x;
	else if (keydata.key == MLX_KEY_RIGHT
		&& mlx->map->map[mlx->map->player_pos->y][mlx->map->player_pos->x + 1]
		!= WALL)
		++mlx->map->player_pos->x;
	else
		return ;
	++mlx->map->moves;
	ft_dprintf(1, "You have moved %d time(s).\n", mlx->map->moves);
	mlx->player_instance->x = mlx->map->player_pos->x * TILE_SIZE;
	mlx->player_instance->y = mlx->map->player_pos->y * TILE_SIZE
		+ SCORE_OFFSET;
	display_score(mlx);
}

void	ft_on_keypress(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keydata.action != MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_on_close(mlx);
	else
		ft_handle_move(keydata, mlx);
	if (mlx->map->map[mlx->map->player_pos->y][mlx->map->player_pos->x]
		== EXIT && mlx->map->data->collectible == 0)
	{
		ft_dprintf(1, "You win!\n");
		ft_dprintf(1, "Total moves: %d\n", mlx->map->moves);
		ft_on_close(mlx);
	}
	else if (mlx->map->map[mlx->map->player_pos->y][mlx->map->player_pos->x]
		== COLL)
	{
		--mlx->map->data->collectible;
		if (mlx->coll_instances[mlx->map->player_pos->y]
			[mlx->map->player_pos->x])
			mlx->coll_instances[mlx->map->player_pos->y]
				[mlx->map->player_pos->x]->enabled = false;
		mlx->map->map[mlx->map->player_pos->y][mlx->map->player_pos->x]
			= FLOOR;
	}
}

void	ft_on_close(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	free_mlx(mlx);
	free(mlx);
	exit(0);
}
