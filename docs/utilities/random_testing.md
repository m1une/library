---
title: Random Testing
documentation_of: ../../utilities/random_testing.hpp
---

## Overview

This header removes the repetitive loop around competitive-programming stress
tests. It supports two workflows:

* `random_test` repeatedly checks a Boolean property;
* `compare_randomly` generates small cases and compares an optimized solver
  against a brute-force oracle.

Testing stops at the first failure. The returned seed and zero-based trial make
the failure reproducible.

## Quick Use During a Contest

```cpp
template <class Property>
RandomTestResult stress_test(
    Property property,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);

template <class Generator, class Solver, class Oracle>
RandomTestResult stress_test(
    Generator generator,
    Solver solver,
    Oracle oracle,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);
```

The shortest interface needs only one lambda:

```cpp
stress_test([](Random& random) {
    auto input = generate_small_case(random);
    return solve(input) == brute(input);
});
```

Or keep generation and the two solutions separate:

```cpp
stress_test(generate_small_case, solve, brute);
```

The included `Random` helpers keep generators short:

```cpp
stress_test([](Random& rng) {
    auto values = rng.sequence(20, -10, 10);
    auto text = rng.string(20, "abc");
    auto tree = rng.tree(20);
    auto graph = rng.graph(20, 30);
    auto weighted_graph = rng.weighted_graph(20, 30, -10, 10);
    auto dag = rng.dag(20, 30);
    return check(values, text, tree, graph, weighted_graph, dag);
});
```

Both forms run 1000 trials with a fixed default seed. Optional trailing
arguments select the trial count and seed:

```cpp
stress_test(generate_small_case, solve, brute, 10000, 123456789);
```

`stress_test` returns normally after every test passes. On failure, it prints
the seed and trial and then calls `std::abort`. The three-function form also
prints the input, expected result, and actual result when they are streamable
or iterable. This means the call does not need an `assert` or result check.

## Configuration and Result

```cpp
struct RandomTestConfig {
    int trials = 1000;
    std::uint64_t seed = default_random_test_seed;
};

struct RandomTestResult {
    std::uint64_t seed;
    int requested_trials;
    int completed_trials;
    int failed_trial;

    bool passed() const;
    explicit operator bool() const;
};
```

The fixed default seed makes ordinary runs deterministic. Supply a different
seed when exploring more cases. On success, `completed_trials` equals
`requested_trials` and `failed_trial` is `-1`. On failure,
`completed_trials == failed_trial` is the number of earlier successful trials.

## Property Tests

```cpp
template <class Property>
RandomTestResult random_test(
    RandomTestConfig config,
    Property property);
```

`random_test(property)` is shorthand using the default configuration.

The property may have either signature and must return something convertible
to `bool`:

```cpp
bool property(Random& random);
bool property(Random& random, int trial);
```

Each call advances the same seeded `Random` generator.

## Optimized Solver Against Brute Force

```cpp
template <class Generator, class Solver, class Oracle,
          class OnFailure = IgnoreRandomTestFailure,
          class Equal = std::equal_to<>>
RandomTestResult compare_randomly(
    RandomTestConfig config,
    Generator generator,
    Solver solver,
    Oracle oracle,
    OnFailure on_failure = {},
    Equal equal = {});
```

`compare_randomly(generator, solver, oracle)` is shorthand using the default
configuration. Unlike `stress_test`, the lower-level functions return a failed
result instead of terminating the program.

`generator` receives `Random&` and optionally the trial number. Its result must
be copyable. The harness gives separate copies to `solver` and `oracle`, so
either function may mutate its input. Results are compared with `equal`.

On a mismatch, `on_failure` is called as follows before testing stops:

```cpp
on_failure(test_case, expected, actual, trial, seed);
```

The callback is optional. Use it to print the counterexample in the format most
helpful for the current problem.

If a failure reports seed `S` and trial `T`, rerun with the same seed and at
least `T + 1` trials. Generation is deterministic as long as the generator
makes the same sequence of random calls.

## Example

```cpp
#include "utilities/random_testing.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    using namespace m1une::utilities;
    RandomTestConfig config;
    config.trials = 10000;
    config.seed = 123456789;

    auto result = compare_randomly(
        config,
        [](Random& random) {
            int n = int(random.uniform(0, 10));
            std::vector<int> values(n);
            for (int& value : values) value = int(random.uniform(-5, 5));
            return values;
        },
        [](std::vector<int>& values) {
            std::sort(values.begin(), values.end());
            return values;
        },
        [](std::vector<int>& values) {
            // Replace this with a deliberately simple oracle for the problem.
            for (int i = 0; i < int(values.size()); i++) {
                for (int j = i + 1; j < int(values.size()); j++) {
                    if (values[j] < values[i]) std::swap(values[i], values[j]);
                }
            }
            return values;
        },
        [](const auto& input, const auto& expected, const auto& actual,
           int trial, std::uint64_t seed) {
            std::cerr << "mismatch: seed=" << seed << " trial=" << trial
                      << " size=" << input.size() << "\n";
            (void)expected;
            (void)actual;
        });

    return result ? 0 : 1;
}
```

The harness adds only $O(1)$ work around each trial, excluding case copies and
the supplied generator, solvers, comparison, and failure callback.
