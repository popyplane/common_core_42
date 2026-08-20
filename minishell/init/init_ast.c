/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:13:58 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 16:57:47 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static void		init_leaf(t_node *node);
static t_bool	leave_leaf(int fd[2], int *pid);

void	init_ast(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE
		|| node->type == N_AND
		|| node->type == N_OR)
	{
		init_ast(node->left);
		if (!g_minishell.hd_sigint)
			init_ast(node->right);
	}
	else
		init_leaf(node);
}

static void	init_leaf(t_node *node)
{
	t_io_list	*io;
	int			fd[2];
	int			pid;

	if (node->value)
		node->exp_value = expander(node->value);
	io = node->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(fd);
			g_minishell.signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				handle_heredoc(io, fd);
			if (leave_leaf(fd, &pid))
				return ;
			io->fd_heredoc = fd[0];
		}
		else
			io->exp_value = expander(io->value);
		io = io->next;
	}
}

static t_bool	leave_leaf(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, handle_sigquit);
	g_minishell.signint_child = false;
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}
