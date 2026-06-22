---
title: Structured Min-Plus Convolution
documentation_of: ../../monge/min_plus_convolution.hpp
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
