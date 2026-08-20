/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:58:56 by codespace         #+#    #+#             */
/*   Updated: 2024/06/21 14:54:28 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

/************* lib ******************/
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

/*********** minilibx ***************/
/* Switched from the classic X11/Cocoa minilibx fork to MLX42
   (codam-coding-college/MLX42): the old fork's render loop never actually
   presented frames to the screen on modern macOS (see README), and after
   fixing that it still had further platform issues. MLX42 is actively
   maintained specifically to avoid this class of bug. Its key constants
   (MLX_KEY_*) are used directly, no more manual keycode table needed. */
# include "../mlx/include/MLX42/MLX42.h"

/************* inc ******************/
# include "struct.h"
# include "define.h"


/**                 FUNCTIONS                   **/

/********** get_map.c **************/
t_map	*get_map(char *path);
t_map	*init_map(void);
void	get_map_dim(t_map *map, char *path);

/********** get_map_utils.c ********/
bool	is_texture_line(char *line);
bool	is_map_line(char *line);
void	get_texture_line(t_map *map, char *line);
void	get_map_line(t_map *map, char *line, int *row);

/************* error.c *************/
void    ft_error(char *msg);
void	*garbage_collector(void *ptr, bool clean);

/************* hooks.c *************/
void	handle_key(mlx_key_data_t keydata, void *param);
void	handle_close(void *param);

/************* img.c *************/
void	img_pix_put(mlx_image_t *img, int x, int y, int color);

/********** display_2d.c *************/
void	draw_tile(int x, int y, int color, t_game *data);
void	draw_map(t_game *data);

/************* player.c *************/
void	init_player(t_game *game);
void	move_player(t_game *game);
bool	is_walkable(t_game *game, int x, int y);
int		parse_color(char *s);

/************* raycast.c ************/
void	cast_rays(t_game *game);

/********** render.c *************/
void	render_frame(void *param);

/********** init.c *************/
t_map	*init_map(void);
t_game	*init_game(void);



#endif
