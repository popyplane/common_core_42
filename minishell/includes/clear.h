/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:17:08 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 15:22:37 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAR_H
# define CLEAR_H

# include "minishell.h"

/*  clean_minishell.c */
void	clean_minishell(void);

/*  clear_parser.c */
void	clear_io_list(t_io_list **lst);
void	clear_cmd_node(t_node *node);
void	recursive_clear_ast(t_node *node);
void	clear_ast(t_node **ast);

/*  garbage_collector.c */
void	*ft_garbage_collector(void *ptr, t_bool clean);

#endif
