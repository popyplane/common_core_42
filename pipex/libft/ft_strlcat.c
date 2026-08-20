/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:21:05 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 15:57:48 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	i;

	if (!dest)
		return (0);
	ls = 0;
	ld = 0;
	i = 0;
	ls = ft_strlen(src);
	ld = ft_strlen(dest);
	if (!dest && size == 0)
		return (0);
	if (size < ld || !size)
		return (size + ls);
	while ((size - ld) > (i + 1) && src[i])
	{
		dest[ld + i] = src[i];
		i++;
	}
	dest[ld + i] = '\0';
	return (ls + ld);
}
