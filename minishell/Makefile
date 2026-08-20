NAME = minishell

LIBFT		:= libft.a
LIBFT_PATH	:= "libft"

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

BUILTINS	=	builtins/env_builtin.c \
				builtins/export_builtin.c \
				builtins/cd_builtin.c \
				builtins/exit_builtin.c \
				builtins/pwd_builtin.c \
				builtins/echo_builtin.c \
				builtins/unset_builtin.c

CLEAR		=	clear/clean_minishell.c \
				clear/clear_parser.c \
				clear/garbage_collector.c

EXEC		=	exec/check.c \
				exec/exec_cmd.c \
				exec/exec_error.c \
				exec/exec_builtin.c \
				exec/exec.c \
				exec/redir.c

EXPAND		=	expand/asterisks.c \
				expand/expander_split.c \
				expand/expander_utils.c \
				expand/expander.c \
				expand/globber_utils.c \
				expand/globber.c \
				expand/expand_heredoc.c \
				expand/pre_expander.c \
				expand/quotes.c

INIT		=	init/env_utils.c \
				init/get_path.c \
				init/handle_heredoc.c \
				init/init_ast.c \
				init/init_envlst.c \
				init/signal.c

PARSING		=	parsing/append_cmd.c \
				parsing/nodes.c \
				parsing/parse_error.c \
				parsing/parse_utils.c \
				parsing/parser.c

TOKEN		=	tokenization/token_lst.c \
				tokenization/token_utils.c \
				tokenization/tokenization_appender.c \
				tokenization/tokenize.c

SRCS			=	$(BUILTINS) \
					$(CLEAR) \
					$(EXEC) \
					$(EXPAND) \
					$(INIT) \
					$(PARSING) \
					$(TOKEN) \
					main.c

OBJS		:=	$(SRCS:.c=.o)

READLINE_PATH	?=	$(shell brew --prefix readline 2>/dev/null || echo /goinfre/homebrew/opt/readline)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ -Iincludes -I$(READLINE_PATH)/include
		
all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
