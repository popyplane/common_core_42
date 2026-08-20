/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:56:25 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/19 17:11:23 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_err_no	check_redir(t_node *node);
t_err_no	redir_io(t_io_list *io_list, t_err_no *status);
void		open_file(t_io_list *io_list, int *fd);

t_err_no	check_redir(t_node *node)
{
	t_io_list	*tmp_io;
	t_err_no	tmp_status;

	tmp_io = node->io_list;
	while (tmp_io)
	{
		if ((tmp_io->type == IO_IN
				|| tmp_io->type == IO_OUT
				|| tmp_io->type == IO_APPEND)
			&& redir_io(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_HEREDOC)
			(dup2(tmp_io->fd_heredoc, 0), close(tmp_io->fd_heredoc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

t_err_no	redir_io(t_io_list *io_list, t_err_no *status)
{
	int	fd;

	if (!io_list->exp_value || io_list->exp_value[1])
	{
		*status = print_and_ret_err((t_err){ENO_GENERAL,
				ERRMSG_AMBIGUOUS,
				io_list->value});
		return (*status);
	}
	open_file(io_list, &fd);
	if (fd == -1)
	{
		if (io_list->type == IO_IN)
			*status = print_and_ret_err(check_read(io_list->exp_value[0]));
		else
			*status = print_and_ret_err(check_write(io_list->exp_value[0]));
		return (*status);
	}
	if (io_list->type == IO_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = ENO_SUCCESS;
	return (*status);
}

void	open_file(t_io_list *io_list, int *fd)
{
	if (!io_list)
	{
		*fd = -1;
		return ;
	}
	if (io_list->type == IO_IN)
		*fd = open(io_list->exp_value[0], O_RDONLY);
	else if (io_list->type == IO_OUT)
		*fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (io_list->type == IO_APPEND)
		*fd = open(io_list->exp_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
}
