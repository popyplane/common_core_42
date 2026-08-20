/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:03:08 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/18 18:30:30 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*parse(void)
{
	t_node	*ast;

	g_minishell.curr_token = g_minishell.tokens;
	ast = expression(0);
	if (g_minishell.curr_token)
		return (set_parse_err(E_SYNTAX), ast);
	return (ast);
}

t_node	*get_cmd(void)
{
	if (g_minishell.parse_err.type)
		return (NULL);
	if (is_bin_op() || g_minishell.curr_token->type == T_C_PARENT)
		return (set_parse_err(E_SYNTAX), NULL);
	return (append_cmd());
}

t_node	*expression(int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				n_prec;
	t_token_type	operator;

	if (g_minishell.parse_err.type || !g_minishell.curr_token)
		return (NULL);
	left = get_cmd();
	if (!left)
		return (NULL);
	while (is_bin_op() && curr_token_prec() >= min_prec)
	{
		operator = g_minishell.curr_token->type;
		get_next_token();
		if (!g_minishell.curr_token)
			return (set_parse_err(E_SYNTAX), left);
		n_prec = ft_prec(operator) + 1;
		right = expression(n_prec);
		if (!right)
			return (left);
		left = combine(operator, left, right);
		if (!left)
			return (clear_ast(&left), clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*combine(t_token_type operator, t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = new_node(get_node_type(operator));
	if (!node)
		return (set_parse_err(E_MEM), NULL);
	node->left = left;
	node->right = right;
	return (node);
}
