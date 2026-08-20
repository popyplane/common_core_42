/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:04:01 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/18 17:20:12 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	is_bin_op(void)
{
	t_token_type	type;

	if (!g_minishell.curr_token)
		return (false);
	type = g_minishell.curr_token->type;
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (true);
	return (false);
}

t_bool	is_redir(t_token_type type)
{
	if (!type)
		return (false);
	return (type == T_REDIR_IN
		|| type == T_REDIR_OUT
		|| type == T_APPEND_OUT
		|| type == T_HEREDOC_IN);
}

void	get_next_token(void)
{
	if (g_minishell.curr_token)
		g_minishell.curr_token = g_minishell.curr_token -> next;
}

int	ft_prec(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

int	curr_token_prec(void)
{
	return (ft_prec(g_minishell.curr_token->type));
}
