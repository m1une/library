---
title: Matroid Intersection
documentation_of: ../../matroid/matroid_intersection.hpp
---

## Overview

`matroid_intersection` finds a largest subset that is independent in two
matroids on the same ground set. It implements the unweighted augmenting-path
algorithm on the matroid exchange graph.

The ground set is `{0, 1, ..., ground_size - 1}`. You provide one independence
oracle for each matroid:

```cpp
bool oracle(const std::vector<int>& subset);
```

An oracle returns whether `subset` is independent in its matroid. The order of
the elements is unspecified and must not affect the answer. The vector contains
no duplicates and is only valid during the call.

`UniformMatroid`, `PartitionMatroid`, `GraphicMatroid`, `LinearMatroid`, and
`BinaryLinearMatroid` already provide this interface and can be passed
directly. Custom callables are supported as well.

This header solves the maximum-cardinality, unweighted problem. It does not
solve weighted matroid intersection.

## Interface

```cpp
template <class IndependenceOracle1, class IndependenceOracle2>
std::vector<int> matroid_intersection(
    int ground_size,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2);
```

The returned vector contains the elements of one maximum common independent
set in increasing order. Both oracles are copied into the function and may keep
mutable scratch storage internally, but they must consistently describe fixed
matroids throughout the call.

The canonical namespace and include are:

```cpp
#include "matroid/matroid_intersection.hpp"

m1une::matroid::matroid_intersection(...);
```

## How the Algorithm Uses the Oracles

Let $S$ be the current common independent set.

1. An outside element $x$ is a source when $S+x$ is independent in the first
   matroid.
2. It is a sink when $S+x$ is independent in the second matroid.
3. The exchange graph contains $y\to x$ when $S-y+x$ is independent in the
   first matroid.
4. It contains $x\to y$ when $S-y+x$ is independent in the second matroid.
5. A shortest source-to-sink path is toggled to increase $|S|$ by one.

If no such path exists, $S$ has maximum cardinality.

## Complexity

Let $N$ be `ground_size`, $R$ be the size of the returned set, and $C_1,C_2$
be the costs of the two oracle calls. The implementation uses

$$O(NR^2(C_1+C_2))$$

time in the worst case and $O(N)$ additional memory. Each oracle receives at
most $R+1$ elements; include the cost of scanning that vector in $C_i$.

This generic version is intended for small or medium explicit ground sets. A
problem-specific matching, flow, or linear-algebra algorithm is usually faster
when one exists.

## Example: Two Partition Matroids

Suppose every item has a color and a shape, and at most one item of each color
and each shape may be selected.

```cpp
#include "matroid/matroid_intersection.hpp"
#include "matroid/partition_matroid.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> color = {0, 0, 1, 1};
    std::vector<int> shape = {0, 1, 0, 2};

    m1une::matroid::PartitionMatroid by_color(color);
    m1une::matroid::PartitionMatroid by_shape(shape);
    auto selected = m1une::matroid::matroid_intersection(
        int(color.size()), by_color, by_shape);

    std::cout << selected.size() << "\n"; // 3
}
```
