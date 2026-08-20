/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:50:54 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 14:44:41 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if ((long int)src > (long int)dest)
		while (++i < n)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}

/* int main(void) */
/* { */
/*     char sResult[] = {67, 68, 67, 68, 69, 0, 45}; */
/* 	char sResult2[] = {67, 67, 68, 68, 69, 0, 45}; */
/*     char tsResult[] = {67, 68, 67, 68, 69, 0, 45}; */
/* 	char tsResult2[] = {67, 67, 68, 68, 69, 0, 45}; */

/*     printf("%s \n", ft_memmove(sResult + 1, sResult2, 2)); */
/*     printf("%s \n", memmove(tsResult + 1, tsResult2, 2)); */
/*     return (0); */
/* } */
