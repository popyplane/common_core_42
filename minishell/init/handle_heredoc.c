/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:58:13 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 17:21:06 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void			handle_heredoc(t_io_list *io, int fd[2]);
static t_bool	is_delimiter(char *delimiter, char *str);

void	handle_heredoc(t_io_list *io, int fd[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, handle_heredoc_sigint);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(io->value, line))
			break ;
		if (!*quotes)
			expand_heredoc(line, fd[1]);
		else
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
	}
	clean_minishell();
	exit(0);
}

void	handle_heredoc_sigint(int signum)
{
	(void)signum;
	clean_minishell();
	exit(SIGINT);
}

static t_bool	is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!(*delimiter));
}
