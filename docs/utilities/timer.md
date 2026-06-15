---
title: Timer
documentation_of: ../../utilities/timer.hpp
---

## Overview

A small wrapper around `std::chrono::steady_clock` for measuring elapsed time during local tests, heuristics, or randomized algorithms.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Timer(double limit_seconds = 0.0)` | Starts the timer and stores an optional time limit in seconds. | $O(1)$ |
| `void reset()` | Restarts the timer from the current time. | $O(1)$ |
| `void set_limit(double limit_seconds)` | Updates the time limit. | $O(1)$ |
| `double elapsed() const` | Returns elapsed seconds as a floating-point value. | $O(1)$ |
| `long long elapsed_ms() const` | Returns elapsed milliseconds. | $O(1)$ |
| `bool expired() const` | Returns whether `elapsed() >= limit_seconds`. | $O(1)$ |

## Example

```cpp
#include "utilities/timer.hpp"

int main() {
    m1une::utilities::Timer timer(1.9);

    while (!timer.expired()) {
        // Do local search, random trials, or stress testing.
    }
}
```
