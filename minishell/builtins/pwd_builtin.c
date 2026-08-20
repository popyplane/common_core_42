/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 00:02:29 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/23 00:06:40 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_err_no	pwd_builtin(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (ENO_GENERAL);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (ENO_SUCCESS);
}
