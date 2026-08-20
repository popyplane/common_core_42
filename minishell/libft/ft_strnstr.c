/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:37:14 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 17:19:27 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (NULL);
	if (s1[i] == '\0' && s2[i] == '\0')
		return ((char *)s1);
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (s1[i + j] == s2[j] && i + j < len)
		{
			j++;
			if (s2[j] == '\0')
				return (((char *)(s1 + i)));
		}
		i++;
	}
	return (0);
}
