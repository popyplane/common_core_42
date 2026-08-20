/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:02:57 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 09:02:59 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}

/* char	ft_min(unsigned int i, char c) */
/* { */
/* 	(void)i; */
/* 	if (c >= 'A' && c <= 'Z') */
/* 		c += 32; */
/* 	return (c); */
/* } */

/* int	main(void) */
/* { */
/* 	char s1[] = "AAAAaaaSSS"; */
/* 	char *s2 = ft_strmapi(s1, ft_min); */
/* 	printf("%s\n%s\n", s1, s2); */
/* } */
