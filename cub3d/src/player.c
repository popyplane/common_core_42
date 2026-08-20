/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:14 by baptistevie       #+#    #+#             */
/*   Updated: 2024/07/12 15:07:14 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *s)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	int		i;

	parts = ft_split(s, ",");
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		ft_error("[parse_color(...)] : invalid color, expected R,G,B");
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return ((r << 16) | (g << 8) | b);
}

bool	is_walkable(t_game *game, int x, int y)
{
	char	c;

	if (y < 0 || y >= game->map->height || !game->map->map[y])
		return (false);
	if (x < 0 || (size_t)x >= ft_strlen(game->map->map[y]))
		return (false);
	c = game->map->map[y][x];
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_dir_from_spawn(t_player *player, char spawn)
{
	if (spawn == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (spawn == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (spawn == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}

void	init_player(t_game *game)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (game->map->map[row][col])
		{
			c = game->map->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player->x = col + 0.5;
				game->player->y = row + 0.5;
				set_dir_from_spawn(game->player, c);
				return ;
			}
			col++;
		}
		row++;
	}
	ft_error("[init_player(...)] : no spawn point (N/S/E/W) found in map");
}

static void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle)
		+ player->plane_y * cos(angle);
}

void	move_player(t_game *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x;
	new_y = p->y;
	if (game->keys.w)
	{
		new_x += p->dir_x * MOVE_SPEED;
		new_y += p->dir_y * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		new_x -= p->dir_x * MOVE_SPEED;
		new_y -= p->dir_y * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		new_x += p->plane_x * MOVE_SPEED;
		new_y += p->plane_y * MOVE_SPEED;
	}
	if (game->keys.a)
	{
		new_x -= p->plane_x * MOVE_SPEED;
		new_y -= p->plane_y * MOVE_SPEED;
	}
	if (is_walkable(game, (int)new_x, (int)p->y))
		p->x = new_x;
	if (is_walkable(game, (int)p->x, (int)new_y))
		p->y = new_y;
	if (game->keys.left)
		rotate_player(p, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(p, ROT_SPEED);
}
