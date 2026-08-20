/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asteriks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:23:49 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 15:23:51 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	handle_pattern_quotes(char **pattern, char *quotes)
{
	if (**pattern == '"' || **pattern == '\'')
	{
		if (!*quotes)
			*quotes = *(*pattern)++;
		else
		{
			if (*quotes == **pattern)
			{
				*quotes = 0;
				(*pattern)++;
			}
		}
	}
}

static t_bool	handle_stars(char **pattern, char **l_wildcard,
char **l_match, char *s)
{
	while (**pattern == '*')
		(*pattern)++;
	if (!**pattern)
		return (true);
	*l_wildcard = *pattern;
	*l_match = s;
	return (false);
}

static t_bool	is_pattern_match(char **pattern, char **l_wildcard,
char **l_match, char **s)
{
	if (**pattern == **s)
	{
		(*pattern)++;
		(*s)++;
		return (true);
	}
	else if (*l_wildcard)
	{
		*s = ++(*l_match);
		*pattern = *l_wildcard;
		return (true);
	}
	else
		return (false);
}

t_bool	is_star_match(char *pattern, char *s)
{
	char	*l_wildcard;
	char	*l_match;
	char	quotes;

	quotes = 0;
	l_match = NULL;
	l_wildcard = NULL;
	while (*s)
	{
		handle_pattern_quotes(&pattern, &quotes);
		if (*pattern == '*' && !quotes
			&& handle_stars(&pattern, &l_wildcard, &l_match, s))
			return (true);
		else if (!is_pattern_match(&pattern, &l_wildcard, &l_match, &s))
			return (false);
	}
	if (*pattern == '*')
		while (*pattern == '*')
			pattern++;
	return (!*pattern);
}
