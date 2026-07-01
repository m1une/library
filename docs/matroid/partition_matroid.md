---
title: Partition Matroid
documentation_of: ../../matroid/partition_matroid.hpp
---

## Overview

`PartitionMatroid` assigns every ground element to one group and limits how
many elements may be selected from each group.

The one-argument constructor gives every group capacity one. The two-argument
constructor accepts individual capacities.

Oracle inputs must contain distinct valid ground-set indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `PartitionMatroid(std::vector<int> group)` | Creates capacity-one groups. Group ids must be non-negative and dense enough to allocate through the maximum id. | $O(N+G)$ |
| `PartitionMatroid(std::vector<int> group, std::vector<int> capacity)` | Uses `capacity[g]` for group `g`. | $O(N+G)$ |
| `int size() const` | Returns the ground-set size. | $O(1)$ |
| `int group_count() const` | Returns the number of groups. | $O(1)$ |
| `const std::vector<int>& groups() const` | Returns the group of every element. | $O(1)$ |
| `const std::vector<int>& capacities() const` | Returns the capacities. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Checks all group capacities. | $O(G+|S|)$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(G+|S|)$ |

## Example

```cpp
#include "matroid/partition_matroid.hpp"
#include <vector>

std::vector<int> group = {0, 0, 1, 1, 1};
std::vector<int> capacity = {1, 2};
m1une::matroid::PartitionMatroid matroid(group, capacity);

bool ok = matroid(std::vector<int>{0, 2, 4}); // true
```
