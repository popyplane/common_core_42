/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:45:47 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:52:54 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "MLX42/MLX42.h"
# include "free.h"
# include "structs.h"

void	ft_handle_move(mlx_key_data_t keydata, t_mlx *mlx);
void	ft_on_keypress(mlx_key_data_t keydata, void *param);
void	ft_on_close(void *param);

#endif
