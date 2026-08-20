/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:45:10 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/08/03 19:52:36 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include <stdlib.h>
# include "MLX42/MLX42.h"
# include "structs.h"

void	free_array(char	**array);
void	free_mlx(t_mlx *mlx);
void	free_map(t_map *map);

#endif
