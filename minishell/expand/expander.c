/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:23:55 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:16:01 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*pre_expander(char *s)
{
	char	*res;
	size_t	i;

	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			res = ft_strjoin_free(res, handle_squotes(s, &i));
		else if (s[i] == '"')
			res = ft_strjoin_free(res, handle_dquotes(s, &i));
		else if (s[i] == '$')
			res = ft_strjoin_free(res, handle_dollar(s, &i));
		else
			res = ft_strjoin_free(res, handle_normal_str(s, &i));
	}
	return (res);
}

char	**expander(char *s)
{
	char	**expanded;
	char	**res;
	size_t	i;

	s = pre_expander(s);
	if (!s)
		return (NULL);
	s = clean_empty_strs(s);
	if (!s)
		return (NULL);
	expanded = expander_split(s);
	free(s);
	if (!expanded)
		return (NULL);
	res = globber(expanded);
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		res[i] = strip_quotes(res[i]);
		i++;
	}
	return (res);
}
