/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:35 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:12:51 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*handle_dquotes_str(char *s, size_t *i)
{
	size_t	start;

	start = *i;
	while (s[*i] != '"' && s[*i] != '$')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	*handle_squotes(char *s, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (s[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	*handle_dquotes(char *s, size_t *i)
{
	char	*res;

	res = ft_strdup("\"");
	(*i)++;
	while (s[*i] != '\"')
	{
		if (s[*i] == '$')
			res = ft_strjoin_free(res, handle_dollar(s, i));
		else
			res = ft_strjoin_free(res, handle_dquotes_str(s, i));
	}
	(*i)++;
	return (ft_strjoin_free(res, ft_strdup("\"")));
}

char	*handle_dollar(char *s, size_t *i)
{
	char	*var;
	char	*env_val;
	size_t	start;

	(*i)++;
	if (ft_isdigit(s[*i]) || s[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_s));
	}
	else if (!is_valid_char(s[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (is_valid_char(s[*i]))
		(*i)++;
	var = ft_substr(s, start, *i - start);
	env_val = get_envlst_val(var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

char	*handle_normal_str(char *s, size_t *i)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}
