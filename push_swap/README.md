# Push_swap

Sort a stack of integers using only two stacks and a limited instruction set (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`), in as few moves as possible. 42 School project.

## Status

Unlike some of the other projects in this repo, this one didn't need an algorithmic rebuild, the sorting logic (index-based radix-style sort for large stacks, dedicated small-case handling for 2/3/5 elements) was already correct. Cleanup done for the portfolio (AI-assisted, Claude):

- **Weak argument validation.** The original character-by-character check allowed `-` or `+` at any position in a number and let a lone `-`/`+` silently parse as `0` instead of being rejected. Replaced with a proper `is_valid_arg` check (sign only at position 0, at least one digit required).
- **Dead code removed**: an unreachable branch in `push()` that checked a pointer-to-pointer against `NULL` (never true, since the pointer itself is always a valid stack-local address) was replaced with a correct `if (!*a) return;` empty-stack guard. Leftover commented-out debug code in `main()` was also removed.

## Verified

Checked with a Python simulator that replays the emitted instructions and confirms the stack ends fully sorted with stack B empty:

| Size | Instructions | Sorted correctly |
|---|---|---|
| 3 | 1 | yes |
| 5 | 8 | yes |
| 100 | 1084 | yes |
| 500 | 6784 | yes |

Error cases (`1 2 2` duplicate, `1 abc` non-numeric, `-` alone, `2147483648` overflow) all correctly print `Error` on stderr and exit without sorting.

## Build & run

```bash
make
./push_swap 2 1 3 6 5 8
```
