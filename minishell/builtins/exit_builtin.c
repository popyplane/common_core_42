/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:08:04 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/25 21:38:27 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_bool	is_str_a_number(char *str);
static int		exittoi(char *str);
static void		skip_spaces_and_get_sign(char **str, int *sign);

void	exit_builtin(char **args)
{
	t_err_no	exit_s;

	exit_s = g_minishell.exit_s;
	if (args[1])
	{
		if (args[2] && is_str_a_number(args[1]))
		{
			exit_s = print_and_ret_err(
					(t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(clean_minishell(), exit(exit_s));
		}
		else
			exit_s = exittoi(args[1]);
	}
	(clean_minishell(), exit(exit_s));
}

static t_bool	is_str_a_number(char *str)
{
	str--;
	while (*(++str))
		if (!ft_isdigit(*str))
			return (false);
	return (true);
}

static void	skip_spaces_and_get_sign(char **str, int *sign)
{
	while (**str && is_space(**str))
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign *= -1;
		(*str)++;
	}
}

static int	exittoi(char *str)
{
	char				*tmp;
	int					sign;
	unsigned long long	result;

	tmp = str;
	sign = 1;
	skip_spaces_and_get_sign(&tmp, &sign);
	if (!is_str_a_number(tmp))
		(clean_minishell(),
			exit(print_and_ret_err((t_err){ENO_EXEC_255,
					ERRMSG_NUMERIC_REQUI, str})));
	result = 0;
	while (*(++tmp))
	{
		result = (result * 10) + (*tmp - '0');
		if (result > LONG_MAX)
			(clean_minishell(),
				exit(print_and_ret_err((t_err){ENO_EXEC_255,
						ERRMSG_NUMERIC_REQUI, str})));
	}
	return ((result * sign) % 256);
}
