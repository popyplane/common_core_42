/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:40:47 by codespace         #+#    #+#             */
/*   Updated: 2024/07/12 15:07:14 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* mlx_t and mlx_image_t come from MLX42.h (included before this header) */

typedef struct s_texture
{
	char	*east_wall;
	char	*west_wall;
	char	*north_wall;
	char	*south_wall;
	char	*floor;
	char	*ceiling;
}	t_texture;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	t_texture	*texture;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_player	*player;
	t_keys		keys;
	int			floor_color;
	int			ceiling_color;
}	t_game;

#endif
