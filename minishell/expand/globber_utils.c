/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:22 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:15:13 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

t_bool	contains_asterisk(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

size_t	ft_arrlen(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	match_count(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	size_t			match_count;

	match_count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (is_star_match(pattern, entry->d_name))
			match_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (match_count);
}

static size_t	mult_arrs_strlen(char ***s)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
			j++;
		len = len + j;
		i++;
	}
	return (len);
}

char	**join_mult_arrs(char ***s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**res;

	i = 0;
	len = mult_arrs_strlen(s);
	res = (char **)ft_calloc(len + 1, sizeof(char *));
	len = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			res[len + j] = ft_strdup(s[i][j]);
			j++;
		}
		len = len + j;
		i++;
	}
	return (free_char3(s), res);
}
