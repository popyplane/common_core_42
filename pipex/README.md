# Pipex

Reimplements a shell pipe (`cmd1 | cmd2`) using `fork`, `pipe`, `dup2` and `execve`. 42 School project. Includes the bonus: heredoc mode and pipelines of more than two commands.

## Status

The core pipe/fork/exec logic in the mandatory part was correct. Three bugs found and fixed for the portfolio (AI-assisted, Claude):

- **`libft` was missing.** It had been dropped from git history at some point; the Makefile expects it at `./libft` and fails to build without it. Restored from this repo's own `minishell/libft` (same author, matching function signatures).
- **Use-after-free in the bonus heredoc reader.** `get_next_line()` in `utils_bonus.c` built the line into a heap buffer, pointed the caller's `*line` at it, then immediately `free()`'d that same buffer before returning. Every call site (`here_doc()`'s delimiter check and the write to the pipe) then read freed memory. Fixed by transferring ownership to the caller instead of freeing locally, and having `here_doc()` free each line once it's actually done with it.
- **First command silently skipped in pipelines of 3+ commands** (bonus). `pipex_bonus`'s `main()` reused one loop counter for two different jobs — selecting the output file's open mode, and walking the command list — so on chains longer than two commands the first command was never forked and the last command ran twice (once piped into a dead end, once for real). Caught by testing `grep hello | tr a-z A-Z | wc -w` through the bonus binary and getting the wrong count. Fixed by giving the command-walking loop its own counter, independent of the mode-selection one.

## Verified

- Mandatory: `./pipex infile "grep hello" "wc -l" outfile` matches the equivalent shell pipe.
- Bonus, 2/3/4-command chains and the heredoc mode all cross-checked against the equivalent shell pipeline, all matching.
- Bonus rebuilt with AddressSanitizer and run through the heredoc path: no use-after-free, no leaks reported, clean exit.

## Build & run

```bash
make            # mandatory
make bonus      # bonus (heredoc + N-command pipelines)

./pipex infile "cmd1" "cmd2" outfile
./pipex_bonus infile "cmd1" "cmd2" "cmd3" outfile
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" outfile
```
