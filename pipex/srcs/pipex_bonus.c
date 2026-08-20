/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:04:34 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/07/04 15:24:06 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	filein;
	int	fileout;
	int	i;
	int	j;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
		{
			i = 3;
			here_doc(argv, argc);
		}
		else
		{
			i = 2;
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		fileout = open_file(argv[argc - 1], 3 - i);
		j = i - 1;
		while (j < argc - 3)
			child_process(argv[++j], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	else
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	return (0);
}
