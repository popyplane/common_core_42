/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_appender.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:46:06 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/12 12:45:59 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_bool	handle_separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_separator(T_APPEND_OUT, line, token_list));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_separator(T_HEREDOC_IN, line, token_list));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_separator(T_REDIR_IN, line, token_list));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_separator(T_REDIR_OUT, line, token_list));
	else if (!ft_strncmp(*line, "&&", 2))
		return (append_separator(T_AND, line, token_list));
	else if (!ft_strncmp(*line, "||", 2))
		return (append_separator(T_OR, line, token_list));
	else
		return (append_separator(T_PIPE, line, token_list));
}

t_bool	append_str(char **line, t_token **token_list)
{
	t_token	*token;
	char	*value;
	size_t	i;

	if (!(*line))
		return (false);
	i = 0;
	while ((*line)[i] && !is_separator(*line + i))
	{
		if (is_quote((*line)[i]) && !skip_quotes(*line, &i))
			return (false);
		else
			i++;
	}
	value = ft_substr(*line, 0, i);
	if (!value)
		return (false);
	token = new_token(T_STR, value);
	if (!token)
		return (free(value), false);
	*line += i;
	return (add_back_token(token, token_list), true);
}

t_bool	append_separator(t_token_type type, char **line, t_token **token_list)
{
	t_token	*token;

	token = new_token(type, NULL);
	if (!token)
		return (false);
	add_back_token(token, token_list);
	(*line)++;
	if (type == T_APPEND_OUT
		|| type == T_HEREDOC_IN
		|| type == T_AND
		|| type == T_OR)
		(*line)++;
	return (true);
}
