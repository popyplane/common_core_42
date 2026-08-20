/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:55:03 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/25 21:37:11 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_bool	check_flag(char *str);

t_err_no	echo_builtin(char **args)
{
	int		i;
	t_bool	flag;

	i = 1;
	flag = false;
	while (args[i] != NULL && check_flag(args[i]) == 1)
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == false)
		ft_putstr_fd("\n", 1);
	return (ENO_SUCCESS);
}

static t_bool	check_flag(char *str)
{
	if (*str != '-')
		return (false);
	while (*(++str))
		if (*str != 'n')
			return (false);
	return (true);
}
