---
title: Linear Matroid
documentation_of: ../../matroid/linear_matroid.hpp
---

## Overview

`LinearMatroid<Field>` uses vectors over a field as its ground elements. A
subset is independent exactly when its vectors are linearly independent.

`BinaryLinearMatroid` is the faster specialization for vectors over
$\mathbb{F}_2$ that fit in 64 bits.

Oracle inputs must contain distinct valid vector indices.

## Requirements

For `LinearMatroid<Field>`, `Field` must support construction from `0` and `1`,
equality, subtraction, multiplication, and division. Static modular integers
over a prime modulus satisfy these requirements.

All input vectors must have the same dimension.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `LinearMatroid(std::vector<std::vector<Field>> vectors)` | Stores the field vectors. | $O(ND)$ |
| `int size() const` | Returns the number of ground elements. | $O(1)$ |
| `int dimension() const` | Returns vector dimension $D$. | $O(1)$ |
| `const std::vector<std::vector<Field>>& vectors() const` | Returns the vectors. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Tests independence by Gaussian elimination. | $O(|S|D^2)$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(|S|D^2)$ |
| `BinaryLinearMatroid(std::vector<std::uint64_t> vectors)` | Stores binary vectors. | $O(N)$ |
| `bool BinaryLinearMatroid::independent(const std::vector<int>& subset) const` | Tests XOR-basis independence. | $O(64|S|)$ |

`BinaryLinearMatroid` also provides `size()`, `dimension()`, `vectors()`, and
`operator()` with the same meanings. Its `dimension()` returns `64`.

## Example

```cpp
#include "matroid/linear_matroid.hpp"
#include <cstdint>
#include <vector>

std::vector<std::uint64_t> vectors = {1, 2, 3, 4};
m1une::matroid::BinaryLinearMatroid matroid(vectors);

bool independent = matroid(std::vector<int>{0, 1}); // true
bool dependent = matroid(std::vector<int>{0, 1, 2}); // false: 1 xor 2 = 3
```
