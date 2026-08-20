# cpp_rank5

C++ modules cpp05 through cpp09 of the 42 School common core: exceptions and orthodox canonical form (Bureaucrat/Form/AForm), casting (ScalarConverter, Serializer, dynamic_cast identification), templates (function templates, iterators, a generic Array), STL containers (easyfind, Span, a stack built on deque), and the final container exercises (BitcoinExchange, reverse Polish notation calculator, PmergeMe merge-insert sort). 16 exercises total across cpp05/ex00-ex03, cpp06/ex00-ex02, cpp07/ex00-ex02, cpp08/ex00-ex02, cpp09/ex00-ex02.

## Status

Every Makefile in this module had the same bug found earlier in cpp_rank4: the object-file pattern rule was written to match `.c` sources (`$(OBJ_DIR)/%.o:$(SRCS_DIR)/%.c`) while every source file here is `.cpp`. Because the pattern never matched, `$(OBJS)` silently fell back to the raw `.cpp` paths themselves instead of `.o` files, so `make` skipped the dedicated compile rule entirely and either linked the sources directly with no enforced flags (cpp05, whose link recipe carries no `$(FLAGS) $(STD_FLAG)`) or recompiled everything from scratch on every build with no incremental `.obj` step (cpp06 through cpp09, whose link recipe happens to repeat the flags). In both cases `-Werror` was never actually gating a real per-file compile step the way the Makefile intended. Fixed in all 16 Makefiles by correcting the pattern to `$(SRCS_DIR)%.cpp` (also dropping a stray extra `/` since `SRCS_DIR` already ends in one).

With the flags genuinely enforced, several real bugs surfaced. Fixed with AI assistance (Claude) for the portfolio:

- **AForm/Form (cpp05/ex01, ex02, ex03): `-Wignored-qualifiers` on `const int getSignGR()`/`getExecGR()`.** A `const` on a return type that isn't a class type has no effect and is rejected under `-Werror`. Removed the `const` from both getters' return types in `Form.hpp`/`AForm.hpp` and their `.cpp` definitions.
- **AForm/Form (same three exercises): `getExecGR()` returned the wrong member.** It returned `_signGradeRequired` instead of `_execGradeRequired` in all three copies of the file (`Form.cpp` in ex01, `AForm.cpp` in ex02 and ex03). Since `execute()` checks the executor's grade against `getExecGR()`, this meant executing a form was checked against its *signing* threshold instead of its *execution* threshold, e.g. `PresidentialPardonForm` (sign grade 25, exec grade 5) would let anyone with grade 25 execute it instead of requiring grade 5. Fixed to return `_execGradeRequired`. Confirmed fixed by rerunning the ex02/ex03 test drivers: `RobotomyRequestForm` (sign 72, exec 45) now correctly lets an "Average" bureaucrat sign but rejects their execute attempt with `GradeTooLowException`, which the pre-fix code would have let through.
- **cpp06/ex00 (ScalarConverter): `-Winfinite-recursion` in `operator=`.** The assignment operator's body was `*this = src; return (*this);`, i.e. it called itself. The class has no members to copy, so the body should be a no-op. Fixed to just return `*this`.
- **cpp06/ex02 (Base): `main.cpp` was entirely missing**, so `make` failed with "No rule to make target `src/main.cpp'". Looking at `Base.hpp` (a `Base` with a virtual destructor and three empty derived classes `A`/`B`/`C`, plus free functions `generate()`, `identify(Base*)`, `identify(Base&)`), this is the classic "generate a random derived object, identify it via pointer and via reference using `dynamic_cast`" exercise. Wrote a new `main.cpp` from scratch implementing that driver (this is AI-authored code, not original graded work, since no main.cpp ever existed here to begin with). Writing it exposed two further real bugs in the pre-existing `Base.cpp`, both of which blocked compilation once the file was actually built for the first time: `std::srand(std::ctime(0))` passed a `char*` from `ctime` where `time()` (returning `time_t`) was clearly intended, and `identify(Base &p)` opened with `if (!p) ...`, applying unary `!` to a class type with no such operator (dead code left over from a pointer-null-check that doesn't apply to a bound reference). Fixed the seed to `std::srand(static_cast<unsigned int>(std::time(0)))` and removed the reference null-check.
- **cpp07/ex02 (Array): segfault on `operator=`.** `_data = new T(_size);` allocated a single `T` (constructed with the value `_size`) instead of an array of `_size` elements (`new T[_size]`), while the very next lines wrote to `_data[0]` through `_data[_size - 1]` and the destructor called `delete[] _data`, mismatched with the scalar `new`. This corrupted the heap and the provided `main.cpp` test driver reliably crashed with SIGSEGV (exit code 139) partway through. Fixed to `new T[_size]`, confirmed by rerunning the driver: it now exits 0 and correctly exercises default/sized/copy construction, deep-copy independence between `intArray` and `copyArray`, the assignment operator, an out-of-bounds `operator[]` throwing `std::out_of_range`, and a `std::string` instantiation.
- **cpp08/ex01 (Span): `-Wsign-compare`.** `evaluateSpan` computed `int span = calculateSpan(...)` (which returns `unsigned int`) and then compared `span < _minSpan` where `_minSpan` is `unsigned int`, an `int`-vs-`unsigned int` comparison. Changed `span`'s type to `unsigned int` to match, which is also what it actually holds.

Exercises not listed above (cpp05/ex00, cpp06/ex01, cpp07/ex00, cpp07/ex01, cpp08/ex00, cpp08/ex02, cpp09/ex00, cpp09/ex01, cpp09/ex02) had no bugs beyond the shared Makefile issue: their logic was already correct once the flags were genuinely applied.

## Verified

For every one of the 16 exercises: ran `make fclean && make` from a clean tree and confirmed zero warnings and zero errors under `-Wall -Wextra -Werror -std=c++98` (plus `-g` where the Makefile specifies it), then ran the binary at least once.

- cpp05/ex00-ex03: ran each `bureaucrat*` binary, confirmed grade out-of-range exceptions, form sign/execute exception paths (`GradeTooLowException`, `GradeTooHighException`, `FormNotSignedException`), the `ShrubberyCreationForm`/`RobotomyRequestForm`/`PresidentialPardonForm` behaviors including the post-fix sign-vs-execute grade distinction, and the ex03 `Intern` factory including its invalid-name exception.
- cpp06/ex00: ran `scalarConverter`'s built-in test cases covering ints, floats, doubles, chars, `nan`/`inf` literals and invalid literals, checked the conversions by hand.
- cpp06/ex01: ran `serializer`, confirmed the pointer survives a round trip through `serialize`/`deserialize` unchanged.
- cpp06/ex02: ran the new `base` binary across several separate invocations one second apart, confirmed `generate()`/`identify()` produce varying, matching A/B/C results by pointer and by reference each time.
- cpp07/ex00: ran `whatever`, confirmed `swap`/`min`/`max` on both `int` and `std::string`.
- cpp07/ex01: ran `iter`, confirmed it iterates arrays of `int` and of `std::string`.
- cpp07/ex02: ran `array` post-fix, confirmed no crash and correct behavior for default/sized/copy/assignment construction, out-of-bounds exception, and a `std::string` array.
- cpp08/ex00: ran `easyfind` against `vector`, `deque`, and `list`, including `const` container overloads, checked found/not-found cases.
- cpp08/ex01: ran `span`, hand-verified the sample set `{6,3,17,9,11}` gives shortest span 2 and longest span 14, and checked the capacity-exceeded, not-enough-elements, and `INT_MIN`/`INT_MAX` edge cases.
- cpp08/ex02: ran `mutantStack`, confirmed it iterates like a `std::list` while behaving like a stack.
- cpp09/ex00: ran `btc` against the provided `input.txt`, checked several date/rate lookups by hand against `data.csv`, and confirmed the negative-value, malformed-date, and overflow error cases.
- cpp09/ex01: ran `RPN` against several expressions (`3 4 +`, `5 1 2 + 4 * + 3 -`, `8 9 * 9 -`) and hand-verified the results (7, 14, 63).
- cpp09/ex02: ran `PmergeMe` on a small hand-picked set and a random 15-element set, confirmed the "Before"/"After" output is correctly sorted and that both the `std::vector` and `std::deque` timings are printed.

## Build & run

Each exercise is a standalone Makefile project:

```bash
cd cpp0X/exYY
make
./<binary> [args]
```

`make fclean` removes the binary and the `.obj` directory; `make re` does a full rebuild.
