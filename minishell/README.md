# Minishell

A bash-like interactive shell written in C: parsing, pipes, redirections, variable expansion, and signal handling that matches real bash behavior. 42 School project (paired).

## Status

The architecture below (tokenizer, AST-based parser, executor) is the original coursework design. At the point this repo was picked up for the portfolio, it didn't actually work: the build was broken (the Makefile referenced source files a later commit had deleted), and once that was patched, the shell crashed on every single command. Four real bugs were found and fixed with AI assistance (Claude) to get it into the working state described here:

- **`tokenization/tokenization_appender.c`**: the root cause. `is_separator(line[i])` treated `line` (a `char **`) as an array of pointers instead of dereferencing it first, so it read garbage memory as soon as any token was more than one character long. This alone caused the shell to crash on `pwd`, `exit`, anything.
- **`tokenization/token_lst.c`**: `add_back_token` checked `!token_list` (a pointer to a pointer, never null) instead of `!*token_list`, so it never correctly detected an empty list.
- **`builtins/echo_builtin.c`**: `while (args[++i] != NULL ...)` incremented before checking, silently skipping the first argument, so `echo hello world` printed only `world`.
- **`expand/pre_expander.c`**: `handle_dquotes` checked `res[*i]` (the short accumulator string being built) instead of `s[*i]` (the actual source string) for the closing quote, reading out of bounds indefinitely, an infinite loop/hang on any double-quoted string.
- Also fixed: a double-free in argument joining (`ft_strjoin_char`/`join_args` disagreed on who owned freeing the input strings), a missing null-check in `get_next_token`, and the Makefile's `READLINE_PATH` was hardcoded to a 42-cluster path, now detects Homebrew's readline automatically.

## Architecture

A line of input goes through: tokenizer → recursive-descent parser producing a binary AST (`N_CMD`/`N_PIPE`/`N_AND`/`N_OR` nodes) → a tree-walking executor using `fork`/`pipe`/`dup2`/`execve`. Built-ins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.

Variable expansion runs in bash's real order: quote/`$VAR` substitution, empty-string cleanup, word-splitting, wildcard (`*`) globbing, then quote-stripping. Heredocs run in a forked child with their own `SIGINT` handling, and a quoted heredoc delimiter correctly disables `$` expansion in the body. Signal behavior matches bash: `SIGINT` at the prompt clears the line without exiting, `SIGQUIT` only prints `Quit: 3` while a child process is actually running.

**Known limitation**: `()` subshell grouping has token types defined in the enum but the parser never consumes them.

## Build & run

```bash
make
./minishell
```
