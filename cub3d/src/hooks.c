/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:18:47 by baptistevie       #+#    #+#             */
/*   Updated: 2024/06/16 17:38:31 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_key(t_game *game, keys_t key, bool value)
{
	if (key == MLX_KEY_W)
		game->keys.w = value;
	else if (key == MLX_KEY_A)
		game->keys.a = value;
	else if (key == MLX_KEY_S)
		game->keys.s = value;
	else if (key == MLX_KEY_D)
		game->keys.d = value;
	else if (key == MLX_KEY_LEFT)
		game->keys.left = value;
	else if (key == MLX_KEY_RIGHT)
		game->keys.right = value;
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.action == MLX_PRESS)
		set_key(game, keydata.key, true);
	else if (keydata.action == MLX_RELEASE)
		set_key(game, keydata.key, false);
}

void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}
