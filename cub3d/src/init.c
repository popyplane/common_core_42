/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:28:11 by baptistevie       #+#    #+#             */
/*   Updated: 2024/06/21 15:01:28 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_error("[init_map(...)] : t_map malloc failed");
	garbage_collector(map, false);
	map->height = 0;
	map->width = 0;
	map->texture = malloc(sizeof(t_texture));
	if (!map->texture)
		ft_error("[init_map(...)] : t_texture malloc failed");
	garbage_collector(map->texture, false);
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("[init_game(...)] : t_game malloc failed");
	garbage_collector(game, false);
	game->mlx = NULL;
	game->img = NULL;
	game->player = NULL;
	ft_bzero(&game->keys, sizeof(t_keys));
	game->map = init_map();
	return (game);
}
