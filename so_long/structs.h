/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:28 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:56:29 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "MLX42/MLX42.h"

# define WALL '1'
# define FLOOR '0'
# define COLL 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef bool	t_bool;

typedef struct s_position{
	int	x;
	int	y;
}	t_position;

typedef struct s_data{
	int	exit;
	int	start;
	int	collectible;
}	t_data;

typedef struct s_map{
	char		**map;
	int			moves;
	t_data		*data;
	t_position	*map_size;
	t_position	*exit;
	t_position	*player_pos;
}	t_map;

typedef struct s_mlx{
	mlx_t			*mlx;
	mlx_image_t		*textures[5];
	mlx_image_t		*score_img;
	mlx_instance_t	*player_instance;
	mlx_instance_t	***coll_instances;
	t_map			*map;
}	t_mlx;

#endif
