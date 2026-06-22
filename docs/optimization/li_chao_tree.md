---
title: Li Chao Tree
documentation_of: ../../optimization/li_chao_tree.hpp
---

## Overview

`LiChaoTree<T, Objective>` maintains linear functions over a fixed integral
coordinate domain. Unlike the monotone-slope convex hull trick, lines may be
inserted in any order.

It supports both lines over the complete domain and lines restricted to a
half-open coordinate segment.

## Construction

```cpp
LiChaoTree(T left, T right);
```

The coordinate domain is `[left, right)`. It is fixed at construction, but
nodes are allocated only where insertion visits, so a large integer domain is
practical.

The aliases `MinLiChaoTree<T>` and `MaxLiChaoTree<T>` select minimum and maximum
queries. `T` must be a signed integral type.

Evaluation uses the widened type described by `LinearFunction<T>` in
`convex_hull_trick.hpp`.

## Methods

Let $U$ be the number of integer coordinates in the domain.

| Method | Description | Complexity |
| --- | --- | --- |
| `add_line(slope, intercept)` | Adds a line over the complete domain. | $O(\log U)$ |
| `add_segment(l, r, slope, intercept)` | Adds a line only over `[l, r)`. | $O(\log^2 U)$ |
| `query(x)` | Returns the optimum at `x`, or `nullopt` if no line covers it. | $O(\log U)$ |
| `get(x)` | Returns the optimum and requires some line to cover `x`. | $O(\log U)$ |
| `left_bound()`, `right_bound()` | Return domain endpoints. | $O(1)$ |
| `node_count()` | Returns allocated node count. | $O(1)$ |
| `reserve(capacity)` | Reserves node storage. | $O(N)$ |
| `clear()` | Removes every line while retaining the domain. | $O(N)$ |

## Example

```cpp
#include "optimization/li_chao_tree.hpp"

#include <iostream>

int main() {
    m1une::optimization::MinLiChaoTree<long long> tree(-1000, 1001);
    tree.add_line(2, 3);
    tree.add_line(-1, 8);
    tree.add_segment(-10, 11, 0, -5);

    long long answer = static_cast<long long>(tree.get(4));
    std::cout << answer << "\n";
}
```
