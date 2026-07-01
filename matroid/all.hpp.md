---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: matroid/graphic_matroid.hpp
    title: Graphic Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/linear_matroid.hpp
    title: Linear Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/matroid_intersection.hpp
    title: Matroid Intersection
  - icon: ':heavy_check_mark:'
    path: matroid/partition_matroid.hpp
    title: Partition Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/uniform_matroid.hpp
    title: Uniform Matroid
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/all.hpp\"\n\n\n\n#line 1 \"matroid/graphic_matroid.hpp\"\
    \n\n\n\n#include <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace matroid {\n\nclass GraphicMatroid {\n   private:\n\
    \    int _vertex_count;\n    std::vector<std::pair<int, int>> _edges;\n\n   public:\n\
    \    GraphicMatroid() : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count,\
    \ std::vector<std::pair<int, int>> edges)\n        : _vertex_count(vertex_count),\
    \ _edges(std::move(edges)) {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n\
    \        for (auto [u, v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n\
    \            assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n\
    \    int size() const {\n        return int(_edges.size());\n    }\n\n    int\
    \ vertex_count() const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/linear_matroid.hpp\"\n\
    \n\n\n#include <array>\n#line 6 \"matroid/linear_matroid.hpp\"\n#include <cstdint>\n\
    #line 9 \"matroid/linear_matroid.hpp\"\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class Field>\nclass LinearMatroid {\n   private:\n    int _dimension;\n\
    \    std::vector<std::vector<Field>> _vectors;\n\n   public:\n    LinearMatroid()\
    \ : _dimension(0) {}\n\n    explicit LinearMatroid(std::vector<std::vector<Field>>\
    \ vectors)\n        : _dimension(vectors.empty() ? 0 : int(vectors[0].size())),\n\
    \          _vectors(std::move(vectors)) {\n#ifndef NDEBUG\n        for (const\
    \ auto& vector : _vectors) assert(int(vector.size()) == _dimension);\n#endif\n\
    \    }\n\n    int size() const {\n        return int(_vectors.size());\n    }\n\
    \n    int dimension() const {\n        return _dimension;\n    }\n\n    const\
    \ std::vector<std::vector<Field>>& vectors() const {\n        return _vectors;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   if (int(subset.size()) > _dimension) return false;\n\n        std::vector<std::vector<Field>>\
    \ basis(_dimension);\n        std::vector<char> has_pivot(_dimension, false);\n\
    \        for (int element : subset) {\n            assert(0 <= element && element\
    \ < int(_vectors.size()));\n            std::vector<Field> vector = _vectors[element];\n\
    \            bool inserted = false;\n            for (int column = 0; column <\
    \ _dimension; column++) {\n                if (vector[column] == Field(0)) continue;\n\
    \                if (!has_pivot[column]) {\n                    Field inverse\
    \ = Field(1) / vector[column];\n                    for (int j = column; j < _dimension;\
    \ j++) vector[j] *= inverse;\n                    basis[column] = std::move(vector);\n\
    \                    has_pivot[column] = true;\n                    inserted =\
    \ true;\n                    break;\n                }\n                Field\
    \ factor = vector[column];\n                for (int j = column; j < _dimension;\
    \ j++) {\n                    vector[j] -= factor * basis[column][j];\n      \
    \          }\n            }\n            if (!inserted) return false;\n      \
    \  }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\nclass BinaryLinearMatroid\
    \ {\n   private:\n    std::vector<std::uint64_t> _vectors;\n\n   public:\n   \
    \ BinaryLinearMatroid() = default;\n    explicit BinaryLinearMatroid(std::vector<std::uint64_t>\
    \ vectors)\n        : _vectors(std::move(vectors)) {}\n\n    int size() const\
    \ {\n        return int(_vectors.size());\n    }\n\n    int dimension() const\
    \ {\n        return 64;\n    }\n\n    const std::vector<std::uint64_t>& vectors()\
    \ const {\n        return _vectors;\n    }\n\n    bool independent(const std::vector<int>&\
    \ subset) const {\n        if (subset.size() > 64) return false;\n\n        std::array<std::uint64_t,\
    \ 64> basis = {};\n        for (int element : subset) {\n            assert(0\
    \ <= element && element < int(_vectors.size()));\n            std::uint64_t value\
    \ = _vectors[element];\n            for (int bit = 63; bit >= 0; bit--) {\n  \
    \              if ((value >> bit & 1) == 0) continue;\n                if (basis[bit]\
    \ == 0) {\n                    basis[bit] = value;\n                    break;\n\
    \                }\n                value ^= basis[bit];\n            }\n    \
    \        if (value == 0) return false;\n        }\n        return true;\n    }\n\
    \n    bool operator()(const std::vector<int>& subset) const {\n        return\
    \ independent(subset);\n    }\n};\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/matroid_intersection.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 7 \"matroid/matroid_intersection.hpp\"\n\nnamespace m1une {\nnamespace matroid\
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
    \ m1une\n\n\n#line 1 \"matroid/partition_matroid.hpp\"\n\n\n\n#line 8 \"matroid/partition_matroid.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\nclass PartitionMatroid {\n   private:\n\
    \    std::vector<int> _group;\n    std::vector<int> _capacity;\n\n    void validate()\
    \ const {\n#ifndef NDEBUG\n        for (int capacity : _capacity) assert(0 <=\
    \ capacity);\n        for (int group : _group) assert(0 <= group && group < int(_capacity.size()));\n\
    #endif\n    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit\
    \ PartitionMatroid(std::vector<int> group) : _group(std::move(group)) {\n    \
    \    int group_count = 0;\n        for (int value : _group) {\n            assert(0\
    \ <= value);\n            group_count = std::max(group_count, value + 1);\n  \
    \      }\n        _capacity.assign(group_count, 1);\n    }\n\n    PartitionMatroid(std::vector<int>\
    \ group, std::vector<int> capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/uniform_matroid.hpp\"\
    \n\n\n\n#line 6 \"matroid/uniform_matroid.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matroid {\n\nclass UniformMatroid {\n   private:\n    int _ground_size;\n  \
    \  int _rank;\n\n   public:\n    UniformMatroid() : _ground_size(0), _rank(0)\
    \ {}\n    UniformMatroid(int ground_size, int rank) : _ground_size(ground_size),\
    \ _rank(rank) {\n        assert(0 <= rank && rank <= ground_size);\n    }\n\n\
    \    int size() const {\n        return _ground_size;\n    }\n\n    int rank()\
    \ const {\n        return _rank;\n    }\n\n    bool independent(const std::vector<int>&\
    \ subset) const {\n        return int(subset.size()) <= _rank;\n    }\n\n    bool\
    \ operator()(const std::vector<int>& subset) const {\n        return independent(subset);\n\
    \    }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 9 \"matroid/all.hpp\"\
    \n\n\n"
  code: '#ifndef M1UNE_MATROID_ALL_HPP

    #define M1UNE_MATROID_ALL_HPP 1


    #include "graphic_matroid.hpp"

    #include "linear_matroid.hpp"

    #include "matroid_intersection.hpp"

    #include "partition_matroid.hpp"

    #include "uniform_matroid.hpp"


    #endif  // M1UNE_MATROID_ALL_HPP

    '
  dependsOn:
  - matroid/graphic_matroid.hpp
  - matroid/linear_matroid.hpp
  - matroid/matroid_intersection.hpp
  - matroid/partition_matroid.hpp
  - matroid/uniform_matroid.hpp
  isVerificationFile: false
  path: matroid/all.hpp
  requiredBy: []
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/matroids.test.cpp
documentation_of: matroid/all.hpp
layout: document
title: Matroid All
---

## Overview

`matroid/all.hpp` includes the standard matroid independence oracles and the
unweighted matroid-intersection algorithm.

Every oracle accepts a `const std::vector<int>&` subset and can be passed
directly to `m1une::matroid::matroid_intersection`.

Oracle subsets must contain distinct valid ground-set indices. The intersection
algorithm always satisfies this precondition.

## Included Headers

| Header | Contents |
| --- | --- |
| `matroid/uniform_matroid.hpp` | Uniform matroid $U_{r,n}$. |
| `matroid/partition_matroid.hpp` | Per-group capacity constraints. |
| `matroid/graphic_matroid.hpp` | Forest independence on graph edges. |
| `matroid/linear_matroid.hpp` | General field and 64-bit binary linear matroids. |
| `matroid/matroid_intersection.hpp` | Maximum-cardinality common independent set. |

## Example

```cpp
#include "matroid/all.hpp"
#include <vector>

int main() {
    m1une::matroid::UniformMatroid at_most_three(6, 3);
    m1une::matroid::PartitionMatroid one_per_group(
        std::vector<int>{0, 0, 1, 1, 2, 2});

    auto result = m1une::matroid::matroid_intersection(
        6, at_most_three, one_per_group);
}
```
