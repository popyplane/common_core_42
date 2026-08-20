#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef enum e_token_type
{
	T_STR,
	T_PIPE,
	T_AND,
	T_OR,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND_OUT,
	T_HEREDOC_IN,
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_O_PARENT,
	T_C_PARENT,
	T_NL
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_AND,
	N_OR
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}	t_parse_err_type;

typedef struct s_io_list
{
	t_io_type			type;
	char				*value;
	char				**exp_value;
	int					fd_heredoc;
	struct s_io_list	*prev;
	struct s_io_list	*next;
}	t_io_list;

typedef struct s_node
{
	t_node_type		type;
	t_io_list		*io_list;
	char			*value;
	char			**exp_value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*s;
}	t_parse_err;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

typedef enum e_ast_branch
{
	BRANCH_L,
	BRANCH_R
}	t_ast_branch;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char				*line;
	t_token				*tokens;
	t_token				*curr_token;
	t_node				*ast;
	int					exit_s;
	t_bool				signint_child;
	t_parse_err			parse_err;
	int					stdin;
	int					stdout;
	char				**env;
	t_env				*env_lst;
	t_bool				hd_sigint;
	struct termios		og_term;
}	t_minishell;

extern t_minishell	g_minishell;

#endif
