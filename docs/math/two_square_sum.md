---
title: Sum of Two Squares
documentation_of: ../../math/two_square_sum.hpp
---

## Overview

Find representations of an integer as a sum of two non-negative squares.

```cpp
#include "math/two_square_sum.hpp"
```

All names are in `m1une::math`.

For example, `25` has four ordered non-negative representations:

```text
0^2 + 5^2
3^2 + 4^2
4^2 + 3^2
5^2 + 0^2
```

so `two_square_sum(25)` returns the pairs `(0, 5)`, `(3, 4)`, `(4, 3)`, and
`(5, 0)`.

## API

```cpp
std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value);

std::vector<std::pair<uint64_t, uint64_t>>
represent_as_two_square_sum(uint64_t value);

bool is_two_square_sum(uint64_t value);
```

| Function | Description |
| --- | --- |
| `two_square_sum(value)` | Returns all ordered non-negative pairs `(a, b)` such that `value = a * a + b * b`. |
| `represent_as_two_square_sum(value)` | Alias of `two_square_sum(value)`. |
| `is_two_square_sum(value)` | Returns whether at least one representation exists. |

The returned vector is sorted in lexicographic order and contains no duplicate
pairs. Both `(a, b)` and `(b, a)` are included when they are different.

`two_square_sum(0)` returns one pair: `(0, 0)`.

## Criterion

By Fermat's theorem on sums of two squares, an integer has a representation as
$a^2 + b^2$ exactly when every prime congruent to `3` modulo `4` appears with an
even exponent in its prime factorization.

This is the condition tested by `is_two_square_sum`.

For construction, each prime congruent to `1` modulo `4` is first represented as
a Gaussian integer norm, and all choices of conjugate factors are combined.
Prime powers congruent to `3` modulo `4` only contribute to a real scale factor
because their exponents must be even.

## Complexity

The function first factors `value` with Pollard-Rho from
`prime_factorization.hpp`. After factorization, the construction is linear in
the number of generated Gaussian-factor choices and the number of returned
pairs.

For a prime factorization

$$
value = 2^e \prod p_i^{\alpha_i} \prod q_j^{2\beta_j},
$$

where every `p_i` is `1` modulo `4` and every `q_j` is `3` modulo `4`, the
number of Gaussian-factor choices is

$$
(e + 1) \prod_i (\alpha_i + 1).
$$

The returned vector contains at most twice this many pairs before duplicate
removal.

## Example

```cpp
#include "math/two_square_sum.hpp"

#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    uint64_t value = 65;
    std::vector<std::pair<uint64_t, uint64_t>> pairs =
        m1une::math::two_square_sum(value);

    for (const auto& pair : pairs) {
        std::cout << pair.first << " " << pair.second << "\n";
    }
}
```
