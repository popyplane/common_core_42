/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:45:43 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/19 19:03:48 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_err_no		exec_cmd(t_node	*node, t_bool piped);
static t_err_no	exec_child(t_node *node);
void			reset_stds(t_bool piped);

t_err_no	exec_cmd(t_node	*node, t_bool piped)
{
	t_err_no	tmp_status;

	if (!node->exp_value)
	{
		tmp_status = check_redir(node);
		return (reset_stds(piped), (tmp_status && ENO_GENERAL));
	}
	else if (is_builtin(node->exp_value[0]))
	{
		tmp_status = check_redir(node);
		if (tmp_status != ENO_SUCCESS)
			return (reset_stds(piped), ENO_GENERAL);
		tmp_status = exec_builtin(node->exp_value);
		return (reset_stds(piped), tmp_status);
	}
	else
		return (exec_child(node));
}

static t_err_no	exec_child(t_node *node)
{
	t_path		path_status;
	t_err_no	tmp_status;
	int			fork_pid;

	g_minishell.signint_child = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = check_redir(node);
		if (tmp_status != ENO_SUCCESS)
			(clean_minishell(), exit(ENO_GENERAL));
		path_status = get_path((node->exp_value)[0]);
		if (path_status.err.no != ENO_SUCCESS)
		{
			tmp_status = print_and_ret_err(path_status.err);
			(clean_minishell(), exit(tmp_status));
		}
		if (execve(path_status.path, node->exp_value, g_minishell.env)
			== -1)
			(clean_minishell(), exit(ENO_GENERAL));
	}
	waitpid(fork_pid, (int *)&tmp_status, 0);
	g_minishell.signint_child = false;
	return (get_exit_status(tmp_status));
}

void	reset_stds(t_bool piped)
{
	if (piped)
		return ;
	dup2(g_minishell.stdin, 0);
	dup2(g_minishell.stdout, 1);
}
