/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:09:00 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 16:39:55 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!c)
		return (((char *)(s + ft_strlen(s))));
	while (s[i])
	{
		if (s[i] == (char)c)
			return (((char *)(s + i)));
		i++;
	}
	return (0);
}
