/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:15 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:11:28 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_bool	match_visibility(char *pattern, char *s)
{
	if ((pattern[0] == '.' && s[0] == '.')
		|| (pattern[0] != '.' && s[0] != '.'))
		return (true);
	return (false);
}

static t_bool	set_dir_entry(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	return (true);
}

static char	**globber_help(char *s)
{
	struct dirent	*entry;
	size_t			mc;
	char			**res;
	DIR				*dir;

	mc = match_count(s);
	if (!contains_asterisk(s) || !mc)
	{
		res = (char **)ft_calloc(mc + 1, sizeof(char *));
		res[0] = ft_strdup(s);
		return (res);
	}
	else
	{
		dir = opendir(".");
		res = (char **)ft_calloc(mc + 1, sizeof(char *));
		mc = 0;
		while (set_dir_entry(&entry, dir) && entry)
			if (is_star_match(s, entry->d_name)
				&& match_visibility(s, entry->d_name))
				res[mc++] = ft_strdup(entry->d_name);
		closedir(dir);
	}
	return (res);
}

char	**globber(char **expanded)
{
	size_t	i;
	size_t	len;
	char	***glob;

	i = 0;
	len = ft_arrlen(expanded);
	glob = (char ***)ft_calloc(len + 1, sizeof(char **));
	while (expanded[i])
	{
		glob[i] = globber_help(expanded[i]);
		i++;
	}
	return (free_char2(expanded), join_mult_arrs(glob));
}
