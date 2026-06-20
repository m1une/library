---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/utilities/basic_utilities.test.cpp
    title: verify/utilities/basic_utilities.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/timer.hpp\"\n\n\n\n#include <chrono>\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\nstruct Timer {\n   private:\n    using clock\
    \ = std::chrono::steady_clock;\n\n    clock::time_point _start;\n    double _limit;\n\
    \n   public:\n    explicit Timer(double limit_seconds = 0.0) : _start(clock::now()),\
    \ _limit(limit_seconds) {}\n\n    void reset() {\n        _start = clock::now();\n\
    \    }\n\n    void set_limit(double limit_seconds) {\n        _limit = limit_seconds;\n\
    \    }\n\n    double elapsed() const {\n        return std::chrono::duration<double>(clock::now()\
    \ - _start).count();\n    }\n\n    long long elapsed_ms() const {\n        return\
    \ std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - _start).count();\n\
    \    }\n\n    bool expired() const {\n        return elapsed() >= _limit;\n  \
    \  }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TIMER_HPP\n#define M1UNE_TIMER_HPP 1\n\n#include <chrono>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct Timer {\n   private:\n  \
    \  using clock = std::chrono::steady_clock;\n\n    clock::time_point _start;\n\
    \    double _limit;\n\n   public:\n    explicit Timer(double limit_seconds = 0.0)\
    \ : _start(clock::now()), _limit(limit_seconds) {}\n\n    void reset() {\n   \
    \     _start = clock::now();\n    }\n\n    void set_limit(double limit_seconds)\
    \ {\n        _limit = limit_seconds;\n    }\n\n    double elapsed() const {\n\
    \        return std::chrono::duration<double>(clock::now() - _start).count();\n\
    \    }\n\n    long long elapsed_ms() const {\n        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now()\
    \ - _start).count();\n    }\n\n    bool expired() const {\n        return elapsed()\
    \ >= _limit;\n    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\
    #endif  // M1UNE_TIMER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/timer.hpp
  requiredBy: []
  timestamp: '2026-06-15 23:35:14+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/utilities/basic_utilities.test.cpp
documentation_of: utilities/timer.hpp
layout: document
title: Timer
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
