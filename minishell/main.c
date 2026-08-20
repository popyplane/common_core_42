#include "minishell.h"

t_minishell	g_minishell;

static void	ft_init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.env = env;
	init_envlst();
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.og_term);
}

static void	ft_start_execution(void)
{
	signal(SIGQUIT, handle_sigquit);
	init_ast(g_minishell.ast);
	if (g_minishell.hd_sigint)
	{
		clear_ast(&g_minishell.ast);
		g_minishell.hd_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.og_term);
	g_minishell.exit_s = exec_node(g_minishell.ast, false);
	clear_ast(&g_minishell.ast);
}

int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	ft_init_minishell(env);
	while (1)
	{
		init_signals();
		g_minishell.line = readline(PROMPT);
		if (!g_minishell.line)
			(clean_minishell(),
				ft_putstr_fd("exit\n", 1), exit(g_minishell.exit_s));
		if (g_minishell.line[0])
			add_history(g_minishell.line);
		g_minishell.tokens = tokenize();
		if (!g_minishell.tokens)
			continue ;
		g_minishell.ast = parse();
		if (g_minishell.parse_err.type)
		{
			handle_parse_err();
			continue ;
		}
		ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
	return (clean_minishell(), g_minishell.exit_s);
}
