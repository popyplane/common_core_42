/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:23:15 by mafoulon          #+#    #+#             */
/*   Updated: 2023/12/20 15:23:17 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

/*  asterisks.c  */
t_bool	is_star_match(char *pattern, char *s);

/*  expand_heredoc.c  */
void	expand_heredoc(char *s, int fd);

/*  expander_split.c  */
char	**expander_split(char const *s);

/*  expander_utils.c  */
void	free_char2(char **tofree);
void	free_char3(char ***tofree);
char	*clean_empty_strs(char *str);
t_bool	is_valid_char(char c);

/*  expander.c  */
char	**expander(char *s);

/*  globber_utils.c  */
t_bool	contains_asterisk(char *s);
size_t	ft_arrlen(char **s);
size_t	match_count(char *pattern);
char	**join_mult_arrs(char ***s);

/*  globber.c  */
char	**globber(char **expanded);

/*  pre_expander.c  */
char	*handle_squotes(char *s, size_t *i);
char	*handle_dquotes(char *s, size_t *i);
char	*handle_dollar(char *s, size_t *i);
char	*handle_normal_str(char *s, size_t *i);

/*  quotes.c  */
char	*strip_quotes(char *s);

#endif
