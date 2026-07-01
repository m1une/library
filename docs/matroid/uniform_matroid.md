---
title: Uniform Matroid
documentation_of: ../../matroid/uniform_matroid.hpp
---

## Overview

`UniformMatroid` represents the uniform matroid $U_{r,n}$. Its ground set is
`{0, 1, ..., n - 1}`, and a subset is independent exactly when it contains at
most $r$ elements.

Oracle inputs must contain distinct valid ground-set indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `UniformMatroid(int ground_size, int rank)` | Constructs $U_{r,n}$. Requires `0 <= rank <= ground_size`. | $O(1)$ |
| `int size() const` | Returns the ground-set size. | $O(1)$ |
| `int rank() const` | Returns $r$. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Tests whether `subset.size() <= rank()`. | $O(1)$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(1)$ |

## Example

```cpp
#include "matroid/uniform_matroid.hpp"
#include <vector>

m1une::matroid::UniformMatroid matroid(5, 2);
bool ok = matroid(std::vector<int>{1, 4}); // true
```
