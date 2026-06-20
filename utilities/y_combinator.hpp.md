---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/utilities/extra_utilities.test.cpp
    title: verify/utilities/extra_utilities.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/y_combinator.hpp\"\n\n\n\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename\
    \ F>\nstruct YCombinator {\n   private:\n    F _f;\n\n   public:\n    explicit\
    \ YCombinator(F&& f) : _f(std::forward<F>(f)) {}\n\n    template <typename...\
    \ Args>\n    decltype(auto) operator()(Args&&... args) {\n        return _f(*this,\
    \ std::forward<Args>(args)...);\n    }\n\n    template <typename... Args>\n  \
    \  decltype(auto) operator()(Args&&... args) const {\n        return _f(*this,\
    \ std::forward<Args>(args)...);\n    }\n};\n\ntemplate <typename F>\nauto y_combinator(F&&\
    \ f) {\n    return YCombinator<std::decay_t<F>>(std::forward<F>(f));\n}\n\n} \
    \ // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_Y_COMBINATOR_HPP\n#define M1UNE_Y_COMBINATOR_HPP 1\n\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace utilities\
    \ {\n\ntemplate <typename F>\nstruct YCombinator {\n   private:\n    F _f;\n\n\
    \   public:\n    explicit YCombinator(F&& f) : _f(std::forward<F>(f)) {}\n\n \
    \   template <typename... Args>\n    decltype(auto) operator()(Args&&... args)\
    \ {\n        return _f(*this, std::forward<Args>(args)...);\n    }\n\n    template\
    \ <typename... Args>\n    decltype(auto) operator()(Args&&... args) const {\n\
    \        return _f(*this, std::forward<Args>(args)...);\n    }\n};\n\ntemplate\
    \ <typename F>\nauto y_combinator(F&& f) {\n    return YCombinator<std::decay_t<F>>(std::forward<F>(f));\n\
    }\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_Y_COMBINATOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/y_combinator.hpp
  requiredBy: []
  timestamp: '2026-06-16 01:13:59+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/utilities/extra_utilities.test.cpp
documentation_of: utilities/y_combinator.hpp
layout: document
title: Y Combinator
---

## Overview

Helper for writing recursive lambdas without declaring a separate function object.

## Functions

| Function | Description |
| --- | --- |
| `y_combinator(lambda)` | Wraps a lambda so it can call itself through its first argument. |

## Example

```cpp
#include "utilities/y_combinator.hpp"
#include <iostream>

int main() {
    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long {
        if (n == 0) return 1;
        return n * self(n - 1);
    });

    long long x = fact(10);
    std::cout << x << "\n";
}
```
