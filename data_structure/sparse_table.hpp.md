---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  - icon: ':heavy_check_mark:'
    path: tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  - icon: ':heavy_check_mark:'
    path: tree/tree.hpp
    title: Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/sparse_table.test.cpp
    title: verify/data_structure/sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/sparse_table.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inverse(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"data_structure/sparse_table.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// A Sparse Table utilizing\
    \ C++20 Concepts for type safety.\n// It requires a Monoid struct that satisfies\
    \ `m1une::monoid::IsMonoid`.\n// [IMPORTANT] For O(1) range queries to work correctly,\
    \ the monoid operation MUST be idempotent.\n// i.e., Monoid::op(x, x) == x must\
    \ hold (e.g., Min, Max, GCD, Bitwise AND/OR).\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct SparseTable {\n    using T = typename Monoid::value_type;\n\n\
    \   private:\n    int _n;\n    std::vector<std::vector<T>> _st;\n\n   public:\n\
    \    // Constructs an empty sparse table.\n    SparseTable() : _n(0) {}\n\n  \
    \  // Constructs a sparse table from an existing vector in O(N log N) time.\n\
    \    explicit SparseTable(const std::vector<T>& v) : _n(int(v.size())) {\n   \
    \     if (_n == 0) return;\n\n        // Compute the maximum power of 2 needed\n\
    \        int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Initialize the base level\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = v[i];\n        }\n\n        //\
    \ Build the sparse table\n        for (int k = 1; k < max_log; k++) {\n      \
    \      for (int i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] =\
    \ Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n\
    \        }\n    }\n    explicit SparseTable(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0; i +\
    \ (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Constructs a sparse table from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit SparseTable(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Compile-time branching based on the available\
    \ make() signature\n        for (int i = 0; i < _n; i++) {\n            if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0;\
    \ i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Returns the product (result of the monoid operation) in the range [l, r) in\
    \ O(1) time.\n    // Requires the monoid operation to be idempotent.\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        if\
    \ (l == r) return Monoid::id();\n\n        // Calculate the largest power of 2\
    \ less than or equal to the interval length\n        int k = std::bit_width((unsigned\
    \ int)(r - l)) - 1;\n        return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SPARSE_TABLE_HPP\n#define M1UNE_SPARSE_TABLE_HPP 1\n\n#include\
    \ <bit>\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\n// A Sparse Table utilizing C++20 Concepts for type safety.\n\
    // It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n// [IMPORTANT]\
    \ For O(1) range queries to work correctly, the monoid operation MUST be idempotent.\n\
    // i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max, GCD, Bitwise AND/OR).\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable {\n    using T =\
    \ typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::vector<std::vector<T>>\
    \ _st;\n\n   public:\n    // Constructs an empty sparse table.\n    SparseTable()\
    \ : _n(0) {}\n\n    // Constructs a sparse table from an existing vector in O(N\
    \ log N) time.\n    explicit SparseTable(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        // Compute the maximum power of 2\
    \ needed\n        int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Initialize the base level\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = v[i];\n        }\n\n        //\
    \ Build the sparse table\n        for (int k = 1; k < max_log; k++) {\n      \
    \      for (int i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] =\
    \ Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n\
    \        }\n    }\n    explicit SparseTable(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0; i +\
    \ (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Constructs a sparse table from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit SparseTable(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Compile-time branching based on the available\
    \ make() signature\n        for (int i = 0; i < _n; i++) {\n            if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0;\
    \ i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Returns the product (result of the monoid operation) in the range [l, r) in\
    \ O(1) time.\n    // Requires the monoid operation to be idempotent.\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        if\
    \ (l == r) return Monoid::id();\n\n        // Calculate the largest power of 2\
    \ less than or equal to the interval length\n        int k = std::bit_width((unsigned\
    \ int)(r - l)) - 1;\n        return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_SPARSE_TABLE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/sparse_table.hpp
  requiredBy:
  - tree/sparse_table_lca.hpp
  - tree/all.hpp
  - tree/tree.hpp
  timestamp: '2026-06-17 20:59:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
  - verify/data_structure/sparse_table.test.cpp
documentation_of: data_structure/sparse_table.hpp
layout: document
title: Sparse Table
---

## Overview

A Sparse Table that answers static range queries in $O(1)$ time after an $O(N \log N)$ preprocessing step. It operates on any Monoid structure satisfying the `m1une::monoid::IsMonoid` concept.

**[IMPORTANT]** For $O(1)$ range queries to work correctly, the monoid operation MUST be **idempotent**. This means that `Monoid::op(x, x) == x` must hold for all valid values of `x` (e.g., Min, Max, GCD, Bitwise AND/OR). It cannot be used for operations like addition or multiplication.

## Template Parameters

* `Monoid`: A struct representing the mathematical monoid, providing `value_type`, `id()`, and `op(a, b)`. It must be an idempotent monoid.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SparseTable()` | Constructs an empty sparse table. | $O(1)$ |
| `SparseTable(const std::vector<T>& v)` | Builds from `v`. | $O(N \log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(1)$ |

## Example

```cpp
#include "data_structure/sparse_table.hpp"
#include "monoid/min.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> A = {5, 2, 8, 1, 3};

    // Initialize Sparse Table with Min Monoid
    m1une::data_structure::SparseTable<m1une::monoid::Min<long long>> st(A);

    // Get minimum of range [0, 3) -> min(5, 2, 8) = 2
    std::cout << st.prod(0, 3) << "\n";

    // Get minimum of range [2, 5) -> min(8, 1, 3) = 1
    std::cout << st.prod(2, 5) << "\n";

    return 0;
}
```
