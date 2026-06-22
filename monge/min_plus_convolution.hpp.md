---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: monge/all.hpp
    title: Monge All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_algorithms.test.cpp
    title: verify/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monge/monge_dp_optimization.test.cpp
    title: verify/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monge/min_plus_convolution.hpp\"\n\n\n\n#include <functional>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace monge {\n\nnamespace convolution_detail\
    \ {\n\ntemplate <class T, class Compare>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare) {\n    if\
    \ (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size =\
    \ int(arbitrary.size());\n    int second_size = int(structured.size());\n    int\
    \ result_size = first_size + second_size - 1;\n    std::vector<T> result(result_size);\n\
    \n    auto solve = [&](auto self, int result_left, int result_right, int candidate_left,\n\
    \                     int candidate_right) -> void {\n        if (result_left\
    \ == result_right) return;\n        int index = (result_left + result_right) /\
    \ 2;\n        int left = candidate_left > index - second_size + 1 ? candidate_left\n\
    \                                                            : index - second_size\
    \ + 1;\n        int right = candidate_right < index + 1 ? candidate_right : index\
    \ + 1;\n\n        int best = left;\n        T best_value = arbitrary[best] + structured[index\
    \ - best];\n        for (int candidate = left + 1; candidate < right; candidate++)\
    \ {\n            T current = arbitrary[candidate] + structured[index - candidate];\n\
    \            if (compare(current, best_value)) {\n                best = candidate;\n\
    \                best_value = current;\n            }\n        }\n        result[index]\
    \ = best_value;\n        self(self, result_left, index, candidate_left, best +\
    \ 1);\n        self(self, index + 1, result_right, best, candidate_right);\n \
    \   };\n\n    solve(solve, 0, result_size, 0, first_size);\n    return result;\n\
    }\n\n}  // namespace convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence) {\n    for\
    \ (int i = 1; i + 1 < int(sequence.size()); i++) {\n        if (sequence[i] -\
    \ sequence[i - 1] < sequence[i + 1] - sequence[i]) {\n            return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const\
    \ std::vector<T>& arbitrary,\n                                           const\
    \ std::vector<T>& convex) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ convex, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\n#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\
    \ 1\n\n#include <functional>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ monge {\n\nnamespace convolution_detail {\n\ntemplate <class T, class Compare>\n\
    std::vector<T> structured_convolution(const std::vector<T>& arbitrary,\n     \
    \                                 const std::vector<T>& structured,\n        \
    \                              Compare compare) {\n    if (arbitrary.empty() ||\
    \ structured.empty()) return {};\n\n    int first_size = int(arbitrary.size());\n\
    \    int second_size = int(structured.size());\n    int result_size = first_size\
    \ + second_size - 1;\n    std::vector<T> result(result_size);\n\n    auto solve\
    \ = [&](auto self, int result_left, int result_right, int candidate_left,\n  \
    \                   int candidate_right) -> void {\n        if (result_left ==\
    \ result_right) return;\n        int index = (result_left + result_right) / 2;\n\
    \        int left = candidate_left > index - second_size + 1 ? candidate_left\n\
    \                                                            : index - second_size\
    \ + 1;\n        int right = candidate_right < index + 1 ? candidate_right : index\
    \ + 1;\n\n        int best = left;\n        T best_value = arbitrary[best] + structured[index\
    \ - best];\n        for (int candidate = left + 1; candidate < right; candidate++)\
    \ {\n            T current = arbitrary[candidate] + structured[index - candidate];\n\
    \            if (compare(current, best_value)) {\n                best = candidate;\n\
    \                best_value = current;\n            }\n        }\n        result[index]\
    \ = best_value;\n        self(self, result_left, index, candidate_left, best +\
    \ 1);\n        self(self, index + 1, result_right, best, candidate_right);\n \
    \   };\n\n    solve(solve, 0, result_size, 0, first_size);\n    return result;\n\
    }\n\n}  // namespace convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence) {\n    for\
    \ (int i = 1; i + 1 < int(sequence.size()); i++) {\n        if (sequence[i] -\
    \ sequence[i - 1] < sequence[i + 1] - sequence[i]) {\n            return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const\
    \ std::vector<T>& arbitrary,\n                                           const\
    \ std::vector<T>& convex) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ convex, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave(const\
    \ std::vector<T>& arbitrary,\n                                            const\
    \ std::vector<T>& concave) {\n    return convolution_detail::structured_convolution(arbitrary,\
    \ concave, std::greater<>());\n}\n\n}  // namespace monge\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monge/min_plus_convolution.hpp
  requiredBy:
  - monge/all.hpp
  timestamp: '2026-06-23 01:05:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monge/monge_algorithms.test.cpp
  - verify/monge/monge_dp_optimization.test.cpp
documentation_of: monge/min_plus_convolution.hpp
layout: document
title: Structured Min-Plus Convolution
---

## Overview

For arrays `a` and `b`, min-plus convolution is

$$
c[k] = \min_{i+j=k}(a[i] + b[j]).
$$

When `b` is a discrete convex sequence, the minimizing index in `a` is
nondecreasing with `k`. `min_plus_convolution_convex` uses this Monge structure
to avoid the naive quadratic algorithm.

The header also provides the symmetric max-plus operation when the second
sequence is concave.

## Functions

```cpp
template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave
);
```

The first sequence is arbitrary. The second sequence must have nondecreasing
adjacent differences for min-plus, or nonincreasing adjacent differences for
max-plus.

If either sequence is empty, the result is empty. Otherwise its length is
`arbitrary.size() + structured.size() - 1`.

The precondition helpers are:

```cpp
template <class T>
bool is_convex_sequence(const std::vector<T>& sequence);

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence);
```

Sequences of length at most two satisfy both properties. The convolution
functions do not run these checks automatically.

## Complexity

For input lengths `N` and `M`, the implementation uses
$O((N + M)\log(N + M))$ time and $O(N + M)$ memory.

The element type must support addition, subtraction, and comparison.
Intermediate values and adjacent differences must fit in the type.

## Example

```cpp
#include "monge/min_plus_convolution.hpp"
#include <vector>

int main() {
    std::vector<long long> arbitrary = {5, 1, 8, 3};
    std::vector<long long> convex = {0, 1, 4, 9};

    auto result =
        m1une::monge::min_plus_convolution_convex(arbitrary, convex);
}
```
