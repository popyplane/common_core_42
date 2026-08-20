/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:46:32 by bvieilhe          #+#    #+#             */
/*   Updated: 2024/06/19 16:05:49 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Our color values are 0xRRGGBB; MLX42's mlx_put_pixel expects 0xRRGGBBAA. */
void	img_pix_put(mlx_image_t *img, int x, int y, int color)
{
	mlx_put_pixel(img, (uint32_t)x, (uint32_t)y, ((uint32_t)color << 8) | 0xFF);
}
