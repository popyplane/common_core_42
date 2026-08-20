/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:01:57 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:19:05 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static size_t	no_quotes_len(char *s)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = -1;
	len = 0;
	quotes = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!quotes)
				quotes = s[i];
			else if (s[i] == quotes)
				quotes = 0;
			else
				len++;
		}
		else
			len++;
	}
	return (len);
}

static void	no_quotes_filler(char *s, size_t *i, size_t *j, char *res)
{
	char	quotes;

	quotes = s[(*i)++];
	while (s[*i] != quotes)
		res[(*j)++] = s[(*i)++];
	(*i)++;
}

char	*strip_quotes(char *s)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = ft_calloc(1 + no_quotes_len(s), sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			no_quotes_filler(s, &i, &j, res);
		else
			res[j++] = s[i++];
	}
	return (free(s), res);
}
