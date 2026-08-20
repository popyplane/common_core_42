/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:19:26 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 17:21:50 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static t_env	*new_envlst(char *key, char *value);

char	*get_envlst_val(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

void	envlst_addback(t_env *new)
{
	t_env	*curr;

	if (!g_minishell.env_lst)
	{
		g_minishell.env_lst = new;
		return ;
	}
	curr = g_minishell.env_lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

void	update_envlst(char *key, char *value, t_bool create)
{
	t_env	*envlst;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		envlst_addback(new_envlst(key, value));
}

static t_env	*new_envlst(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}
