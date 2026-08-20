/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:36:50 by codespace         #+#    #+#             */
/*   Updated: 2024/06/25 18:30:02 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MLX_ERROR 1

int	main(int ac, char **av)
{
	t_game	*game;

	game = init_game();
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", false);
	if (game->mlx == NULL)
		return (MLX_ERROR);
	game->map = get_map(av[1]);
	game->floor_color = parse_color(game->map->texture->floor);
	game->ceiling_color = parse_color(game->map->texture->ceiling);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		ft_error("[main(...)] : t_player malloc failed");
	garbage_collector(game->player, false);
	init_player(game);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (game->img == NULL || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (MLX_ERROR);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_key_hook(game->mlx, &handle_key, game);
	mlx_close_hook(game->mlx, &handle_close, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}
