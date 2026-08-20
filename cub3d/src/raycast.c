/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:14 by baptistevie       #+#    #+#             */
/*   Updated: 2024/07/12 15:07:14 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	bool	ns_wall;
}	t_ray;

static void	init_ray(t_game *game, t_ray *ray, double camera_x)
{
	ray->dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->delta_dist_y;
	}
}

static void	step_ray(t_game *game, t_ray *ray)
{
	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->ns_wall = false;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->ns_wall = true;
		}
		if (!is_walkable(game, ray->map_x, ray->map_y))
			return ;
	}
}

static double	perp_wall_dist(t_game *game, t_ray *ray)
{
	if (!ray->ns_wall)
		return ((ray->map_x - game->player->x
				+ (1 - ray->step_x) / 2.0) / ray->dir_x);
	return ((ray->map_y - game->player->y
			+ (1 - ray->step_y) / 2.0) / ray->dir_y);
}

static int	shade_color(int color, double dist)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	factor = 1.0 / (1.0 + dist * dist * 0.03);
	if (factor > 1.0)
		factor = 1.0;
	r = (int)(((color >> 16) & 0xFF) * factor);
	g = (int)(((color >> 8) & 0xFF) * factor);
	b = (int)((color & 0xFF) * factor);
	return ((r << 16) | (g << 8) | b);
}

static void	draw_column(t_game *game, int x, double perp_dist, bool ns_wall)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	wall_color;

	if (perp_dist < 0.01)
		perp_dist = 0.01;
	line_height = (int)(WINDOW_HEIGHT / perp_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (ns_wall)
		wall_color = shade_color(WALL_NS_COLOR, perp_dist);
	else
		wall_color = shade_color(WALL_EW_COLOR, perp_dist);
	y = 0;
	while (y < draw_start)
		img_pix_put(game->img, x, y++, game->ceiling_color);
	while (y < draw_end)
		img_pix_put(game->img, x, y++, wall_color);
	while (y < WINDOW_HEIGHT)
		img_pix_put(game->img, x, y++, game->floor_color);
}

void	cast_rays(t_game *game)
{
	int		x;
	double	camera_x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = 2.0 * x / (double)WINDOW_WIDTH - 1.0;
		init_ray(game, &ray, camera_x);
		step_ray(game, &ray);
		draw_column(game, x, perp_wall_dist(game, &ray), ray.ns_wall);
		x++;
	}
}
