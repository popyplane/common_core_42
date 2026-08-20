/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baptistevieilhescaze <baptistevieilhesc    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:51:57 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/21 18:20:55 by baptistevie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		export_list(void);
static t_err_no	export_err_msg(char *identifier);

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_err_no	export_builtin(char **argv)
{
	int				i;
	t_err_no		exit_s;
	char			*key;

	exit_s = 0;
	i = 1;
	if (!argv[1])
		return (export_list(), 0);
	while (argv[i])
	{
		if (check_key(argv[i]) == 0)
			exit_s = export_err_msg(argv[i]);
		else
		{
			key = extract_envlst_key(argv[i]);
			if (get_envlst_val(key))
				update_envlst(key, extract_value(argv[i]), false);
			else
				update_envlst(key, extract_value(argv[i]), true);
		}
		i++;
	}
	return (exit_s);
}

static void	export_list(void)
{
	t_env	*list;
	size_t	i;

	list = g_minishell.env_lst;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

static t_err_no	export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (ENO_GENERAL);
}
