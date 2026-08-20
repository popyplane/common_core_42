/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:06:54 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/19 18:57:56 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/*	check.c	 */
t_err		check_exec(char *file, t_bool cmd);
t_err		check_read(char *file);
t_err		check_write(char *file);

/*	exec_builtin.c  */
t_err_no	exec_builtin(char **args);
t_bool		is_builtin(char *arg);

/*	exec_cmd.c  */
t_err_no	exec_cmd(t_node	*node, t_bool piped);
void		reset_stds(t_bool piped);

/*	exec_error.c  */
t_err_no	print_and_ret_err(t_err err);

/*	exec.c  */
t_err_no	exec_node(t_node *tree, t_bool piped);
t_err_no	get_exit_status(t_err_no status);

/*	redir.c  */
t_err_no	check_redir(t_node *node);
t_err_no	redir_io(t_io_list *io_list, t_err_no *status);
void		open_file(t_io_list *io_list, int *fd);

#endif
