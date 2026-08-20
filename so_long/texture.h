/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:29:57 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:57:14 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "structs.h"

# define TILE_SIZE 48

# define FLOOR_PATH "./assets/floor.png"
# define WALL_PATH "./assets/wall.png"
# define PLAYER_PATH "./assets/player.png"
# define COLLECTIBLE_PATH "./assets/collectible.png"
# define EXIT_PATH "./assets/exit.png"

t_bool	load_textures(t_mlx *mlx);
t_data	*init_data(void);

#endif
