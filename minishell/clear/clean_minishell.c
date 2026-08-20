/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:28:33 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 17:48:45 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

static void	clear_envlst(void);

void	clean_minishell(void)
{
	ft_garbage_collector(NULL, true);
	clear_ast(&g_minishell.ast);
	clear_envlst();
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.og_term);
}

static void	clear_envlst(void)
{
	t_env	*envlst;
	t_env	*envlst_tofree;

	envlst = g_minishell.env_lst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree);
	}
	g_minishell.env_lst = NULL;
}
