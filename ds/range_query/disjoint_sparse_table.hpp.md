---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/disjoint_sparse_table.test.cpp
    title: verify/ds/range_query/disjoint_sparse_table.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/disjoint_sparse_table.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line\
    \ 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/range_query/disjoint_sparse_table.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A Disjoint Sparse Table for static\
    \ range queries.\n// It supports any associative monoid, including non-idempotent\
    \ and non-commutative ones.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ DisjointSparseTable {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n;\n    std::vector<std::vector<T>> _st;\n\n    void build() {\n   \
    \     if (_n == 0) return;\n\n        for (int k = 0; k < int(_st.size()); k++)\
    \ {\n            int half = 1 << k;\n            int block = half << 1;\n    \
    \        for (int start = 0; start < _n; start += block) {\n                int\
    \ mid = std::min(start + half, _n);\n                int end = std::min(start\
    \ + block, _n);\n\n                _st[k][mid - 1] = _st[0][mid - 1];\n      \
    \          for (int i = mid - 2; i >= start; i--) {\n                    _st[k][i]\
    \ = Monoid::op(_st[0][i], _st[k][i + 1]);\n                }\n\n             \
    \   if (mid == end) continue;\n                _st[k][mid] = _st[0][mid];\n  \
    \              for (int i = mid + 1; i < end; i++) {\n                    _st[k][i]\
    \ = Monoid::op(_st[k][i - 1], _st[0][i]);\n                }\n            }\n\
    \        }\n    }\n\n   public:\n    // Constructs an empty disjoint sparse table.\n\
    \    DisjointSparseTable() : _n(0) {}\n\n    // Constructs a disjoint sparse table\
    \ from an existing vector in O(N log N) time.\n    explicit DisjointSparseTable(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n, Monoid::id()));\n        for (int i = 0; i < _n; i++) {\n\
    \            _st[0][i] = v[i];\n        }\n        build();\n    }\n    explicit\
    \ DisjointSparseTable(std::vector<T>&& v) : _n(int(v.size())) {\n        if (_n\
    \ == 0) return;\n\n        int max_log = std::bit_width((unsigned int)_n);\n \
    \       _st.assign(max_log, std::vector<T>(_n, Monoid::id()));\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \        build();\n    }\n\n    // Constructs a disjoint sparse table from a vector\
    \ of a different type U.\n    // It automatically adapts to the Monoid's initialization\
    \ requirements:\n    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val,\
    \ index) if the monoid requires global indices.\n    // 3. static_cast<T>(val)\
    \ as a fallback for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit DisjointSparseTable(const std::vector<U>& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n, Monoid::id()));\n \
    \       for (int i = 0; i < _n; i++) {\n            if constexpr (requires(U x)\
    \ { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n \
    \           } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        build();\n    }\n\n    // Returns the product (result of the monoid\
    \ operation) in the range [l, r) in O(1) time.\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return\
    \ Monoid::id();\n\n        r--;\n        if (l == r) return _st[0][l];\n\n   \
    \     int k = std::bit_width((unsigned int)(l ^ r)) - 1;\n        return Monoid::op(_st[k][l],\
    \ _st[k][r]);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DISJOINT_SPARSE_TABLE_HPP\n#define M1UNE_DISJOINT_SPARSE_TABLE_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <concepts>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A Disjoint Sparse Table for static\
    \ range queries.\n// It supports any associative monoid, including non-idempotent\
    \ and non-commutative ones.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ DisjointSparseTable {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n;\n    std::vector<std::vector<T>> _st;\n\n    void build() {\n   \
    \     if (_n == 0) return;\n\n        for (int k = 0; k < int(_st.size()); k++)\
    \ {\n            int half = 1 << k;\n            int block = half << 1;\n    \
    \        for (int start = 0; start < _n; start += block) {\n                int\
    \ mid = std::min(start + half, _n);\n                int end = std::min(start\
    \ + block, _n);\n\n                _st[k][mid - 1] = _st[0][mid - 1];\n      \
    \          for (int i = mid - 2; i >= start; i--) {\n                    _st[k][i]\
    \ = Monoid::op(_st[0][i], _st[k][i + 1]);\n                }\n\n             \
    \   if (mid == end) continue;\n                _st[k][mid] = _st[0][mid];\n  \
    \              for (int i = mid + 1; i < end; i++) {\n                    _st[k][i]\
    \ = Monoid::op(_st[k][i - 1], _st[0][i]);\n                }\n            }\n\
    \        }\n    }\n\n   public:\n    // Constructs an empty disjoint sparse table.\n\
    \    DisjointSparseTable() : _n(0) {}\n\n    // Constructs a disjoint sparse table\
    \ from an existing vector in O(N log N) time.\n    explicit DisjointSparseTable(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n, Monoid::id()));\n        for (int i = 0; i < _n; i++) {\n\
    \            _st[0][i] = v[i];\n        }\n        build();\n    }\n    explicit\
    \ DisjointSparseTable(std::vector<T>&& v) : _n(int(v.size())) {\n        if (_n\
    \ == 0) return;\n\n        int max_log = std::bit_width((unsigned int)_n);\n \
    \       _st.assign(max_log, std::vector<T>(_n, Monoid::id()));\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \        build();\n    }\n\n    // Constructs a disjoint sparse table from a vector\
    \ of a different type U.\n    // It automatically adapts to the Monoid's initialization\
    \ requirements:\n    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val,\
    \ index) if the monoid requires global indices.\n    // 3. static_cast<T>(val)\
    \ as a fallback for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit DisjointSparseTable(const std::vector<U>& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n, Monoid::id()));\n \
    \       for (int i = 0; i < _n; i++) {\n            if constexpr (requires(U x)\
    \ { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n \
    \           } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        build();\n    }\n\n    // Returns the product (result of the monoid\
    \ operation) in the range [l, r) in O(1) time.\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return\
    \ Monoid::id();\n\n        r--;\n        if (l == r) return _st[0][l];\n\n   \
    \     int k = std::bit_width((unsigned int)(l ^ r)) - 1;\n        return Monoid::op(_st[k][l],\
    \ _st[k][r]);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_DISJOINT_SPARSE_TABLE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/disjoint_sparse_table.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/disjoint_sparse_table.test.cpp
documentation_of: ds/range_query/disjoint_sparse_table.hpp
layout: document
title: Disjoint Sparse Table
---

## Overview

A Disjoint Sparse Table that answers static range queries in $O(1)$ time after an $O(N \log N)$ preprocessing step. It operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept.

Unlike a normal Sparse Table, the monoid operation does not need to be idempotent. It can be used for operations like addition, multiplication, matrix multiplication, and other associative operations.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `DisjointSparseTable()` | Constructs an empty disjoint sparse table. | $O(1)$ |
| `DisjointSparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "ds/range_query/disjoint_sparse_table.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    m1une::ds::DisjointSparseTable<m1une::monoid::Add<long long>> dst(A);

    // Get sum of range [0, 3) -> 5 + 2 + 8 = 15
    std::cout << dst.prod(0, 3) << "\n";

    // Get sum of range [2, 5) -> 8 + 1 + 3 = 12
    std::cout << dst.prod(2, 5) << "\n";

    return 0;
}
```
