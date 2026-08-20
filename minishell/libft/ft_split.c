/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:32:04 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/29 10:32:28 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	word;

	i = 1;
	word = 0;
	if (!s || !s[0])
		return (word);
	if (s[0] != c)
		word++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			word++;
		i++;
	}
	return (word);
}

static void	ft_free(char **res, size_t j)
{
	while (j--)
		free(res[j]);
	free(res);
}

static size_t	ft_malwords(char const *s, char c, char **res, size_t j)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	res[j] = (char *)malloc(sizeof(char) * (len + 1));
	if (!res[j])
	{
		ft_free(res, j);
		return (0);
	}
	while (i < len)
	{
		res[j][i] = s[i];
		i++;
	}
	res[j][i] = '\0';
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	res = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!res)
		return (NULL);
	while (j < ft_count(s, c))
	{
		if (!ft_malwords(&s[i], c, res, j))
			return (NULL);
		i += ft_strlen(res[j]);
		while (s[i] && s[i] == c)
			i++;
		j++;
	}
	res[j] = 0;
	return (res);
}
