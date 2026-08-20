/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:26:12 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/08 14:00:05 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!c)
		return (((char *)(s + ft_strlen(s))));
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (((char *)(s + i)));
		i--;
	}
	return (NULL);
}
