_This project has been created as part of the 42 curriculum by esaleh._

# Philosophers

## Description

Philosophers is a classic concurrency problem (the Dining Philosophers
problem) implemented in C using POSIX threads and mutexes. A number of
philosophers sit at a round table with one fork between each pair of them.
Each philosopher alternates between thinking, eating and sleeping, and must
pick up both the fork to their left and the fork to their right before
eating. The goal is to simulate this cycle correctly, without data races,
deadlocks, or a philosopher starving to death, while a dedicated monitor
routine watches for deaths in real time.

This repository contains the mandatory part (`philo`), one thread per
philosopher synchronized with mutexes. The bonus part (`philo_bonus`, one
process per philosopher synchronized with semaphores) is not implemented.

## Instructions

### Compilation

```sh
make
```

This builds the `philo` binary using `cc` with `-Wall -Wextra -Werror` and
`-pthread`. Other available rules: `clean`, `fclean`, `re`.

### Execution

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: number of philosophers, and also the number of forks.
- `time_to_die` (ms): if a philosopher hasn't started eating within this many
  milliseconds since the start of their last meal (or the start of the
  simulation), they die.
- `time_to_eat` (ms): how long a philosopher spends eating (holding both forks).
- `time_to_sleep` (ms): how long a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): if given, the
  simulation stops once every philosopher has eaten at least this many times;
  otherwise it runs until a philosopher dies.

Example:

```sh
./philo 5 800 200 200
./philo 5 800 200 200 7
```

Each state change is logged as `timestamp_in_ms philosopher_id message`
(`has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`).

## Resources

- [Dining philosophers problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming (LLNL tutorial)](https://hpc-tutorials.llnl.gov/posix/)
- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`, `man usleep`

### AI Usage

AI was used as a learning and discussion tool throughout the project. It
helped clarify concurrency concepts (threads, mutexes, synchronization),
review implementation ideas, and discuss debugging strategies. All design
decisions, implementation, testing, and final code were completed and
validated by the author.
