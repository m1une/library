---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroid_intersection.test.cpp
    title: verify/matroid/matroid_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/matroid_intersection.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class IndependenceOracle1, class IndependenceOracle2>\nstd::vector<int>\
    \ matroid_intersection(int ground_size, IndependenceOracle1 oracle1,\n       \
    \                               IndependenceOracle2 oracle2) {\n    assert(0 <=\
    \ ground_size);\n\n    std::vector<char> selected(ground_size, false);\n    std::vector<int>\
    \ elements;\n    std::vector<int> position(ground_size, -1);\n\n    while (true)\
    \ {\n        std::vector<char> source(ground_size, false);\n        std::vector<char>\
    \ sink(ground_size, false);\n        std::vector<int> distance(ground_size, -1);\n\
    \        std::vector<int> previous(ground_size, -1);\n        std::vector<int>\
    \ queue;\n        queue.reserve(ground_size);\n\n        for (int x = 0; x < ground_size;\
    \ x++) {\n            if (selected[x]) continue;\n            elements.push_back(x);\n\
    \            source[x] = oracle1(elements);\n            sink[x] = oracle2(elements);\n\
    \            elements.pop_back();\n            if (source[x]) {\n            \
    \    distance[x] = 0;\n                queue.push_back(x);\n            }\n  \
    \      }\n\n        int target = -1;\n        for (int head = 0; head < int(queue.size())\
    \ && target == -1; head++) {\n            int v = queue[head];\n            if\
    \ (!selected[v] && sink[v]) {\n                target = v;\n                break;\n\
    \            }\n\n            if (selected[v]) {\n                int index =\
    \ position[v];\n                assert(index != -1 && elements[index] == v);\n\
    \                for (int x = 0; x < ground_size; x++) {\n                   \
    \ if (selected[x] || distance[x] != -1) continue;\n                    elements[index]\
    \ = x;\n                    bool independent = oracle1(elements);\n          \
    \          elements[index] = v;\n                    if (!independent) continue;\n\
    \                    distance[x] = distance[v] + 1;\n                    previous[x]\
    \ = v;\n                    queue.push_back(x);\n                }\n         \
    \   } else {\n                for (int y : elements) {\n                    if\
    \ (distance[y] != -1) continue;\n                    int index = position[y];\n\
    \                    assert(index != -1 && elements[index] == y);\n          \
    \          elements[index] = v;\n                    bool independent = oracle2(elements);\n\
    \                    elements[index] = y;\n                    if (!independent)\
    \ continue;\n                    distance[y] = distance[v] + 1;\n            \
    \        previous[y] = v;\n                    queue.push_back(y);\n         \
    \       }\n            }\n        }\n\n        if (target == -1) break;\n    \
    \    for (int v = target; v != -1; v = previous[v]) selected[v] = !selected[v];\n\
    \n        elements.clear();\n        std::fill(position.begin(), position.end(),\
    \ -1);\n        for (int x = 0; x < ground_size; x++) {\n            if (!selected[x])\
    \ continue;\n            position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n    }\n\n    return elements;\n}\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATROID_MATROID_INTERSECTION_HPP\n#define M1UNE_MATROID_MATROID_INTERSECTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace matroid {\n\ntemplate <class IndependenceOracle1, class IndependenceOracle2>\n\
    std::vector<int> matroid_intersection(int ground_size, IndependenceOracle1 oracle1,\n\
    \                                      IndependenceOracle2 oracle2) {\n    assert(0\
    \ <= ground_size);\n\n    std::vector<char> selected(ground_size, false);\n  \
    \  std::vector<int> elements;\n    std::vector<int> position(ground_size, -1);\n\
    \n    while (true) {\n        std::vector<char> source(ground_size, false);\n\
    \        std::vector<char> sink(ground_size, false);\n        std::vector<int>\
    \ distance(ground_size, -1);\n        std::vector<int> previous(ground_size, -1);\n\
    \        std::vector<int> queue;\n        queue.reserve(ground_size);\n\n    \
    \    for (int x = 0; x < ground_size; x++) {\n            if (selected[x]) continue;\n\
    \            elements.push_back(x);\n            source[x] = oracle1(elements);\n\
    \            sink[x] = oracle2(elements);\n            elements.pop_back();\n\
    \            if (source[x]) {\n                distance[x] = 0;\n            \
    \    queue.push_back(x);\n            }\n        }\n\n        int target = -1;\n\
    \        for (int head = 0; head < int(queue.size()) && target == -1; head++)\
    \ {\n            int v = queue[head];\n            if (!selected[v] && sink[v])\
    \ {\n                target = v;\n                break;\n            }\n\n  \
    \          if (selected[v]) {\n                int index = position[v];\n    \
    \            assert(index != -1 && elements[index] == v);\n                for\
    \ (int x = 0; x < ground_size; x++) {\n                    if (selected[x] ||\
    \ distance[x] != -1) continue;\n                    elements[index] = x;\n   \
    \                 bool independent = oracle1(elements);\n                    elements[index]\
    \ = v;\n                    if (!independent) continue;\n                    distance[x]\
    \ = distance[v] + 1;\n                    previous[x] = v;\n                 \
    \   queue.push_back(x);\n                }\n            } else {\n           \
    \     for (int y : elements) {\n                    if (distance[y] != -1) continue;\n\
    \                    int index = position[y];\n                    assert(index\
    \ != -1 && elements[index] == y);\n                    elements[index] = v;\n\
    \                    bool independent = oracle2(elements);\n                 \
    \   elements[index] = y;\n                    if (!independent) continue;\n  \
    \                  distance[y] = distance[v] + 1;\n                    previous[y]\
    \ = v;\n                    queue.push_back(y);\n                }\n         \
    \   }\n        }\n\n        if (target == -1) break;\n        for (int v = target;\
    \ v != -1; v = previous[v]) selected[v] = !selected[v];\n\n        elements.clear();\n\
    \        std::fill(position.begin(), position.end(), -1);\n        for (int x\
    \ = 0; x < ground_size; x++) {\n            if (!selected[x]) continue;\n    \
    \        position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n    }\n\n    return elements;\n}\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATROID_MATROID_INTERSECTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/matroid_intersection.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/matroids.test.cpp
  - verify/matroid/matroid_intersection.test.cpp
documentation_of: matroid/matroid_intersection.hpp
layout: document
title: Matroid Intersection
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
