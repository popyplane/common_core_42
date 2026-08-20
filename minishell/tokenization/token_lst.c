/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:24:42 by baptistevie       #+#    #+#             */
/*   Updated: 2023/12/07 16:57:48 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_bool	is_space(char c)
{
	if (!c)
		return (false);
	return (c == ' '
		|| c == '\t' || c == '\n'
		|| c == '\r' || c == '\v'
		|| c == '\f');
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	add_back_token(t_token *token, t_token **token_list)
{
	t_token	*curr_token;

	if (!*token_list)
	{
		*token_list = token;
		return ;
	}
	curr_token = *token_list;
	while (curr_token && curr_token->next)
		curr_token = curr_token->next;
	curr_token->next = token;
	token->prev = curr_token;
}
