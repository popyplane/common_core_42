/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:13:25 by bvieilhe          #+#    #+#             */
/*   Updated: 2024/07/03 13:52:20 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600

# define BLUE_PIXEL		0xFF
# define GREEN_PIXEL	0xFF00
# define RED_PIXEL		0xFF0000
# define BLACK_PIXEL	0xFFFFFF
# define WHITE_PIXEL	0x0

# define MOVE_SPEED		0.045
# define ROT_SPEED		0.03

/* solid directional wall shading (no image textures available in this repo,
   the sample map only lists placeholder texture paths) */
# define WALL_NS_COLOR	0x8C8C8C
# define WALL_EW_COLOR	0x5C5C5C

#endif