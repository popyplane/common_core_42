# Philosophers

The classic dining philosophers problem: N philosophers around a table, one fork between each pair, must eat/sleep/think forever without deadlocking or starving. 42 School project, implemented with POSIX threads and mutexes.

## Status

The code builds cleanly, but as found, the core exclusion mechanism the whole assignment is about didn't actually work: forks were stored as a value embedded directly in each philosopher's struct rather than a shared resource, so adjacent philosophers each had their own private copy of a "fork" instead of contending for the same mutex, real fork contention never happened. Four bugs, fixed with AI assistance (Claude) for the portfolio:

- **Forks weren't shared.** Each philosopher held `fork_l`/`fork_r` as its own embedded `pthread_mutex_t` value, copied by value at init instead of referencing a common array. Fixed by giving `t_data` a shared `forks` array and making each philosopher's `fork_l`/`fork_r` a pointer into it, so neighbors genuinely lock the same mutex.
- **`pthread_create` used the wrong pointer**: `&data->philo->thread` (always the first philosopher) instead of `&data->philo[i].thread`, so every thread's ID overwrote the same field.
- **Deadlock in the meal-limit exit path**: the success branch re-locked an already-held mutex and unlocked one that was never locked. Once all philosophers reached the meal limit, the program hung permanently instead of exiting.
- **Out-of-bounds read**: the death-check loop called the "has everyone hit the meal limit" check once per philosopher, passing a pointer to a single philosopher into a function that internally loops over the full array as if that pointer were array index 0. Fixed by checking it once per full sweep instead, matching what the function actually does.

Verified after fixing: `./philo 1 800 200 200` correctly detects and reports death by starvation (a lone philosopher has only one fork, can never pick up a second), `./philo 4 800 200 200 3` now exits cleanly once all four reach 3 meals instead of hanging, and a thread-level sample of `./philo 4 410 200 200` running shows every philosopher thread cycling through real eat/sleep/think, not blocked on a mutex.

## Build & run

```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [max_meals]
```
