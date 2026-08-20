/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:32:09 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:50:32 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "MLX42/MLX42.h"
# include "error.h"
# include "strings.h"
# include "structs.h"
# include "free.h"
# include "hooks.h"
# include "utils.h"
# include <stdlib.h>

# define SCORE_OFFSET 50

void	build_bg(t_mlx *mlx);
void	build_assets(t_mlx *mlx);
void	display_score(t_mlx *mlx);
void	init_window(t_mlx *mlx);

#endif
