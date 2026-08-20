/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:55:04 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/21 13:19:32 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_err_no	exec_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (echo_builtin(args));
	if (!ft_strcmp(args[0], "cd"))
		return (cd_builtin(args[1]));
	if (!ft_strcmp(args[0], "env"))
		return (env_builtin());
	if (!ft_strcmp(args[0], "pwd"))
		return (pwd_builtin());
	if (!ft_strcmp(args[0], "export"))
		return (export_builtin(args));
	if (!ft_strcmp(args[0], "unset"))
		return (unset_builtin(args));
	if (!ft_strcmp(args[0], "exit"))
		exit_builtin(args);
	//return (exit_builtin(args));
	return (ENO_GENERAL);
}

t_bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	return (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"));
}
