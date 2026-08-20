/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:57:40 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 17:03:41 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_path			get_path(char *cmd);
static t_path	get_env_path(char *path, char *cmd);

t_path	get_path(char *cmd)
{
	char	*value;

	if (*cmd == '\0')
		return ((t_path){
			(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){check_exec(cmd, false), cmd});
	value = get_envlst_val("PATH");
	if (value)
		return (get_env_path(value, cmd));
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, cmd}, NULL});
}

static t_path	get_env_path(char *path, char *cmd)
{
	size_t	i;
	t_err	err;
	char	*cmd_path;
	char	**splited_path;

	splited_path = ft_split(path, ':');
	i = -1;
	while (splited_path[++i])
	{
		cmd_path = ft_garbage_collector(ft_strjoin_char(
					ft_strdup(splited_path[i]), ft_strdup(cmd), '/'), false);
		err = check_exec(cmd_path, true);
		if (err.no == ENO_SUCCESS)
			return ((t_path){(t_err){ENO_SUCCESS, 42, cmd_path}, cmd_path});
	}
	free_char2(splited_path);
	return ((t_path){(t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd}, NULL});
}
