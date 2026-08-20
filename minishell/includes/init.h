/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:56:55 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 15:22:48 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

/*	env_utils.c  */
char	*get_envlst_val(char *key);
void	envlst_addback(t_env *new);
void	update_envlst(char *key, char *value, t_bool create);

/*	get_path.c  */
t_path	get_path(char *cmd);

/*	handle_heredoc.c  */
void	handle_heredoc(t_io_list *io, int fd[2]);
void	handle_heredoc_sigint(int signum);

/*	init_ast.c  */
void	init_ast(t_node *node);

/*	init_envlst.c  */
void	init_envlst(void);
char	*extract_envlst_key(char *str);
char	*extract_value(char *str);
char	*extract_key(char *str);

/*	signal.c  */
void	init_signals(void);
void	handle_sigquit(int n);

#endif
