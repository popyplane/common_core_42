# cpp_rank4

C++98 exercises from 42 School's CPP Module 00 through Module 04: iostreams and classes, orthodox canonical form, memberwise operators, a fixed-point number class, inheritance, polymorphism and abstract classes. 15 exercises across five modules.

## Status

Every exercise's Makefile had the same silent bug, plus one exercise (Account) didn't exist at all. Fixed with AI assistance (Claude) for the portfolio:

- **Every Makefile silently dropped `-Wall -Wextra -Werror -std=c++98`.** The object-file rule matched sources as `%.c` while the actual files are `.cpp`, and separately `SRCS_DIR` (`src/`) already ended in a slash while the pattern added another one (`$(SRCS_DIR)/%.c` = `src//foo.c`, never matching the real `src/foo.cpp`). Both bugs meant `$(OBJS)` never substituted and silently fell back to the raw `.cpp` source list, so `$(NAME): $(OBJS)` compiled and linked the sources directly in one flagless `c++ src/main.cpp ... -o binary` call, completely bypassing the recipe that carries the compiler flags. Every exercise built "successfully" with zero warnings enforced. Fixed the pattern in all 16 Makefiles so object files actually get built through the flagged rule.
- **cpp00/ex00 (megaphone)**: `-Wsign-compare` once `-Wextra` actually applied — `for (int i = 0; i < strlen(str); i++)` compared a signed `int` against `strlen`'s `size_t`. Changed the loop variable to `size_t`.
- **cpp00/ex01 (phonebook)**: `int _nbContacts = -1;` used a C++11 default member initializer, invalid in strict C++98. Moved the initialization into the constructor's initializer list.
- **cpp03/ex00, ex01, ex02 (ClapTrap/ScavTrap/FragTrap)**: same C++11 default-member-initializer issue on `_hitPoints`, `_energyPoints`, `_attackDamage` in `ClapTrap.hpp`, present identically in all three exercises' copies of the header. Fixed the same way: removed the in-class initializers, added them to `ClapTrap`'s constructor initializer list.
- **cpp04/ex01 (Brain)**: `-Wmisleading-indentation` in `operator=` — a `for` loop nested inside an unbraced `if` was followed by a `return` at the same indentation, reading as part of the loop. Added braces around the `if` body.
- **cpp01/ex05 (harl)**: `main()` ignored `argc`/`argv` entirely and unconditionally called `complain()` with all four hardcoded levels plus `"TEST"`, so `./harl DEBUG` and `./harl WARNING` produced identical output regardless of the argument. This defeats the point of the exercise (filtering by the level given on the command line). Found while running a functional smoke test, not from a compiler warning. Fixed `main()` to read `argv[1]` and call `complain()` once with it, printing a usage message if no argument is given.
- **cpp00/ex02 (Account) didn't exist.** `inc/Account.hpp` (subject-provided interface) and `src/tests.cpp` (subject-provided test driver) were present, but there was no `Account.cpp` and no Makefile, so the exercise had never been implemented. Wrote `src/Account.cpp` from scratch in C++98 against the interface and the behavior implied by `tests.cpp`, plus a Makefile matching the other exercises' structure. **This implementation is entirely AI-authored (Claude), not original graded work** — it never existed before this cleanup. A stray file `cpp00/ex02/19920104_091532.log` looked like captured output from a previous (correct) run against the same `tests.cpp` test data; it was used to cross-check the new implementation's output byte-for-byte before being deleted as leftover run output rather than source.

## Verified

- Rebuilt every exercise from clean (`make fclean && make`) and confirmed the compiler invocation itself carries `-Wall -Wextra -Werror -std=c++98` (visible in the build log, not just a non-error exit code), with zero warnings across all 16 exercises plus the new Account build.
- megaphone: uppercases and echoes multiple arguments, prints the default message with no arguments.
- phonebook: manual ADD then SEARCH cycle through stdin, confirmed the added contact's fields round-trip correctly.
- zombieGreetings / zombieHorde: constructors, `announce()`, and destructors all fire in the right order and count.
- helloBrain: pointer and reference both alias the same address as the original string, values match.
- uselessViolence: HumanA (armed at construction) and HumanB (armed later) both attack correctly through a `Weapon&`.
- replace: `WORLD` → `PLANET` on a mixed-case test file, only the exact-case match was replaced.
- harl: re-tested after the fix — `DEBUG` prints only the debug message, `WARNING` prints only the warning message, an unrecognized level prints the "doesn't exist" fallback, and no argument prints usage.
- Fixed (cpp02/ex00-ex02): constructed from int and float, converted back with `toInt()`/`toFloat()`, values round-trip within fixed-point precision.
- ClapTrap/ScavTrap/FragTrap: attack/takeDamage/beRepaired sequences produce sane HP/EP numbers, including going negative on lethal damage and the "out of energy" branch.
- Animals/Brain/AAnimals: virtual dispatch through base pointers calls the derived `makeSound()`, WrongAnimal/WrongCat correctly do *not* dispatch polymorphically (the point of that exercise), and Brain's copy constructor performs a real deep copy of the `_ideas` array (checked construction/destruction counts, not just that it compiles).
- Account: ran the subject-provided `tests.cpp` and diffed its output against the leftover reference log (`19920104_091532.log`, since deleted) with timestamps normalized out. Every line matched exactly — creation/deposit/withdrawal amounts, refused withdrawals, running totals in `displayAccountsInfos()`, and closing balances — except for the order objects are destroyed in, which is unspecified `std::vector` destructor behavior (this machine's libc++ destroys back-to-front; the reference log's libstdc++ destroyed front-to-back) and not something `Account.cpp` or the un-modifiable `tests.cpp` controls.
- `git status` shows only the expected Makefile/source diffs and the two new Account files; no `.obj` directories or binaries left behind.

## Build & run

```bash
cd cpp0X/exYY && make && ./binary
```

Binary names vary by exercise (`megaphone`, `phonebook`, `account`, `zombieGreetings`, `zombieHorde`, `helloBrain`, `uselessViolence`, `replace`, `harl`, `fixed`, `ClapTrap`, `ScavTrap`, `FragTrap`, `Animals`, `Brain`, `AAnimals`); check each directory's Makefile for `NAME`. `harl` and `replace` take command-line arguments (`./harl WARNING`, `./replace file.txt OLD NEW`); the rest run standalone or read from stdin.
