/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:02:09 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 17:02:12 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	heredoc_writer(char *s, size_t i, int fd)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (s[i] == '?')
		return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
	while (s[i] && s[i] != '$' && s[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = ft_garbage_collector(ft_substr(s, start, i), false);
		tmp = get_envlst_val(tmp);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i);
}

void	expand_heredoc(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			i += heredoc_writer(s, i, fd);
		else
			i += (ft_putchar_fd(s[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
