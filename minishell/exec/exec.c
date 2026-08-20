/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:55:18 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/20 14:49:34 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_err_no	exec_pipe(t_node *tree);
static t_err_no	exec_pipe_child(t_node *node, int fd[2], t_ast_branch branch);

t_err_no	exec_node(t_node *tree, t_bool piped)
{
	t_err_no	status;

	if (!tree)
		return (ENO_GENERAL);
	if (tree->type == N_PIPE)
		exec_pipe(tree);
	else if (tree->type == N_OR)
	{
		status = exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return ((int)status);
		return (exec_node(tree->right, false));
	}
	else if (tree->type == N_AND)
	{
		status = exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return (exec_node(tree->right, false));
		return ((int)status);
	}
	else
		exec_cmd(tree, piped);
	return (ENO_GENERAL);
}

static t_err_no	exec_pipe(t_node *tree)
{
	t_err_no	status;
	int			fd[2];
	pid_t		pid_l;
	pid_t		pid_r;

	g_minishell.signint_child = true;
	pipe(fd);
	pid_l = fork();
	if (pid_l == 0)
		exec_pipe_child(tree->left, fd, BRANCH_L);
	else
	{
		pid_r = fork();
		if (!pid_r)
			exec_pipe_child(tree->right, fd, BRANCH_R);
		else
		{
			(close(fd[0]), close(fd[1]),
				waitpid(pid_l, (int*)&status, 0),
				waitpid(pid_r, (int*)&status, 0));
			g_minishell.signint_child = false;
			return (get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

static t_err_no	exec_pipe_child(t_node *node, int fd[2], t_ast_branch branch)
{
	int	status;

	if (branch == BRANCH_L)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (branch == BRANCH_R)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	status = exec_node(node, true);
	(clean_minishell(), exit(status));
}

t_err_no	get_exit_status(t_err_no status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
