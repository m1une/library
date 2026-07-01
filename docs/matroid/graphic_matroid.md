---
title: Graphic Matroid
documentation_of: ../../matroid/graphic_matroid.hpp
---

## Overview

`GraphicMatroid` uses the edges of an undirected graph as its ground set. A
subset is independent exactly when the selected edges form a forest.

Element `i` corresponds to `edges()[i]`. Parallel edges are supported; loops
are always dependent.

Oracle inputs must contain distinct valid edge indices.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `GraphicMatroid(int vertex_count, std::vector<std::pair<int, int>> edges)` | Stores the graph. | $O(E)$ |
| `int size() const` | Returns the number of ground elements (edges). | $O(1)$ |
| `int vertex_count() const` | Returns the graph's vertex count. | $O(1)$ |
| `const std::vector<std::pair<int, int>>& edges() const` | Returns the indexed edge list. | $O(1)$ |
| `bool independent(const std::vector<int>& subset) const` | Checks whether the selected edges are acyclic. | $O(V+|S|\alpha(V))$ |
| `bool operator()(const std::vector<int>& subset) const` | Independence-oracle shorthand. | $O(V+|S|\alpha(V))$ |

## Example

```cpp
#include "matroid/graphic_matroid.hpp"
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> edges = {
    {0, 1}, {1, 2}, {2, 0}, {2, 3}
};
m1une::matroid::GraphicMatroid matroid(4, edges);

bool forest = matroid(std::vector<int>{0, 1, 3}); // true
bool cycle = matroid(std::vector<int>{0, 1, 2});  // false
```
