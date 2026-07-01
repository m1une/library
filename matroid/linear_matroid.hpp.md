---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroid_intersection.test.cpp
    title: verify/matroid/matroid_intersection.test.cpp
  - icon: ':x:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/linear_matroid.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace matroid {\n\ntemplate <class Field>\nclass LinearMatroid\
    \ {\n   private:\n    int _dimension;\n    std::vector<std::vector<Field>> _vectors;\n\
    \n   public:\n    LinearMatroid() : _dimension(0) {}\n\n    explicit LinearMatroid(std::vector<std::vector<Field>>\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATROID_LINEAR_MATROID_HPP\n#define M1UNE_MATROID_LINEAR_MATROID_HPP\
    \ 1\n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace matroid {\n\ntemplate <class\
    \ Field>\nclass LinearMatroid {\n   private:\n    int _dimension;\n    std::vector<std::vector<Field>>\
    \ _vectors;\n\n   public:\n    LinearMatroid() : _dimension(0) {}\n\n    explicit\
    \ LinearMatroid(std::vector<std::vector<Field>> vectors)\n        : _dimension(vectors.empty()\
    \ ? 0 : int(vectors[0].size())),\n          _vectors(std::move(vectors)) {\n#ifndef\
    \ NDEBUG\n        for (const auto& vector : _vectors) assert(int(vector.size())\
    \ == _dimension);\n#endif\n    }\n\n    int size() const {\n        return int(_vectors.size());\n\
    \    }\n\n    int dimension() const {\n        return _dimension;\n    }\n\n \
    \   const std::vector<std::vector<Field>>& vectors() const {\n        return _vectors;\n\
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
    \ m1une\n\n#endif  // M1UNE_MATROID_LINEAR_MATROID_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/linear_matroid.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:07:14+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/matroid/matroids.test.cpp
  - verify/matroid/matroid_intersection.test.cpp
documentation_of: matroid/linear_matroid.hpp
layout: document
title: Linear Matroid
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
