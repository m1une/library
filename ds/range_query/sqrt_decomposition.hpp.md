---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sqrt_decomposition.test.cpp
    title: verify/ds/range_query/sqrt_decomposition.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/sqrt_decomposition.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n#include\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/range_query/sqrt_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Mutable square-root decomposition\
    \ for point assignments and range products.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct SqrtDecomposition {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<T>\
    \ _values;\n    std::vector<T> _block_product;\n\n    template <class U>\n   \
    \ static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    void initialize_blocks() {\n\
    \        if (_n == 0) {\n            _block_size = 1;\n            _block_count\
    \ = 0;\n            _block_product.clear();\n            return;\n        }\n\
    \        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) ++_block_size;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \        _block_product.assign(_block_count, Monoid::id());\n        for (int\
    \ block = 0; block < _block_count; ++block) {\n            rebuild_block(block);\n\
    \        }\n    }\n\n    void rebuild_block(int block) {\n        assert(0 <=\
    \ block && block < _block_count);\n        int left = block * _block_size;\n \
    \       int right = std::min(_n, left + _block_size);\n        T product = Monoid::id();\n\
    \        for (int index = left; index < right; ++index) {\n            product\
    \ = Monoid::op(product, _values[index]);\n        }\n        _block_product[block]\
    \ = std::move(product);\n    }\n\n   public:\n    SqrtDecomposition()\n      \
    \  : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtDecomposition(int\
    \ n)\n        : _n(n), _block_size(1), _block_count(0), _values(n, Monoid::id())\
    \ {\n        assert(0 <= n);\n        initialize_blocks();\n    }\n\n    explicit\
    \ SqrtDecomposition(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _values(values)\
    \ {\n        initialize_blocks();\n    }\n\n    explicit SqrtDecomposition(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _block_size(1),\n    \
    \      _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks();\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtDecomposition(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(values.size(), Monoid::id()) {\n\
    \        for (int index = 0; index < _n; ++index) {\n            _values[index]\
    \ = make_value(values[index], index);\n        }\n        initialize_blocks();\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block) const {\n        assert(0 <= block\
    \ && block < _block_count);\n        int left = block * _block_size;\n       \
    \ return {left, std::min(_n, left + _block_size)};\n    }\n\n    const std::vector<T>&\
    \ values() const {\n        return _values;\n    }\n\n    const std::vector<T>&\
    \ block_products() const {\n        return _block_product;\n    }\n\n    const\
    \ T& get(int index) const {\n        assert(0 <= index && index < _n);\n     \
    \   return _values[index];\n    }\n\n    const T& operator[](int index) const\
    \ {\n        return get(index);\n    }\n\n    // Assigns one element and rebuilds\
    \ its block.\n    void set(int index, T value) {\n        assert(0 <= index &&\
    \ index < _n);\n        _values[index] = std::move(value);\n        rebuild_block(block_of(index));\n\
    \    }\n\n    // Returns the ordered monoid product over [left, right).\n    T\
    \ prod(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        T result = Monoid::id();\n        while (left < right\
    \ && left % _block_size != 0) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        while (left + _block_size <= right) {\n            result\
    \ = Monoid::op(\n                result,\n                _block_product[left\
    \ / _block_size]\n            );\n            left += _block_size;\n        }\n\
    \        while (left < right) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        return result;\n    }\n\n    T all_prod() const {\n      \
    \  T result = Monoid::id();\n        for (const T& product : _block_product) {\n\
    \            result = Monoid::op(result, product);\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP\n#define M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <concepts>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Mutable square-root decomposition\
    \ for point assignments and range products.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct SqrtDecomposition {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<T>\
    \ _values;\n    std::vector<T> _block_product;\n\n    template <class U>\n   \
    \ static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    void initialize_blocks() {\n\
    \        if (_n == 0) {\n            _block_size = 1;\n            _block_count\
    \ = 0;\n            _block_product.clear();\n            return;\n        }\n\
    \        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) ++_block_size;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \        _block_product.assign(_block_count, Monoid::id());\n        for (int\
    \ block = 0; block < _block_count; ++block) {\n            rebuild_block(block);\n\
    \        }\n    }\n\n    void rebuild_block(int block) {\n        assert(0 <=\
    \ block && block < _block_count);\n        int left = block * _block_size;\n \
    \       int right = std::min(_n, left + _block_size);\n        T product = Monoid::id();\n\
    \        for (int index = left; index < right; ++index) {\n            product\
    \ = Monoid::op(product, _values[index]);\n        }\n        _block_product[block]\
    \ = std::move(product);\n    }\n\n   public:\n    SqrtDecomposition()\n      \
    \  : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtDecomposition(int\
    \ n)\n        : _n(n), _block_size(1), _block_count(0), _values(n, Monoid::id())\
    \ {\n        assert(0 <= n);\n        initialize_blocks();\n    }\n\n    explicit\
    \ SqrtDecomposition(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _values(values)\
    \ {\n        initialize_blocks();\n    }\n\n    explicit SqrtDecomposition(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _block_size(1),\n    \
    \      _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks();\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtDecomposition(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(values.size(), Monoid::id()) {\n\
    \        for (int index = 0; index < _n; ++index) {\n            _values[index]\
    \ = make_value(values[index], index);\n        }\n        initialize_blocks();\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block) const {\n        assert(0 <= block\
    \ && block < _block_count);\n        int left = block * _block_size;\n       \
    \ return {left, std::min(_n, left + _block_size)};\n    }\n\n    const std::vector<T>&\
    \ values() const {\n        return _values;\n    }\n\n    const std::vector<T>&\
    \ block_products() const {\n        return _block_product;\n    }\n\n    const\
    \ T& get(int index) const {\n        assert(0 <= index && index < _n);\n     \
    \   return _values[index];\n    }\n\n    const T& operator[](int index) const\
    \ {\n        return get(index);\n    }\n\n    // Assigns one element and rebuilds\
    \ its block.\n    void set(int index, T value) {\n        assert(0 <= index &&\
    \ index < _n);\n        _values[index] = std::move(value);\n        rebuild_block(block_of(index));\n\
    \    }\n\n    // Returns the ordered monoid product over [left, right).\n    T\
    \ prod(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        T result = Monoid::id();\n        while (left < right\
    \ && left % _block_size != 0) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        while (left + _block_size <= right) {\n            result\
    \ = Monoid::op(\n                result,\n                _block_product[left\
    \ / _block_size]\n            );\n            left += _block_size;\n        }\n\
    \        while (left < right) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        return result;\n    }\n\n    T all_prod() const {\n      \
    \  T result = Monoid::id();\n        for (const T& product : _block_product) {\n\
    \            result = Monoid::op(result, product);\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_DS_RANGE_QUERY_SQRT_DECOMPOSITION_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/sqrt_decomposition.hpp
  requiredBy: []
  timestamp: '2026-06-23 02:29:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sqrt_decomposition.test.cpp
documentation_of: ds/range_query/sqrt_decomposition.hpp
layout: document
title: Square-Root Decomposition
---

## Overview

`SqrtDecomposition<Monoid>` divides a mutable array into blocks of approximately
$\sqrt N$ elements. Each block stores its ordered monoid product.

It supports point assignments and range products without the complexity of a
segment tree. Any associative monoid is supported, including
non-commutative operations.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N)$ |
| `set(index, value)` | $O(\sqrt N)$ |
| `prod(left, right)` | $O(\sqrt N)$ |
| `all_prod()` | $O(\sqrt N)$ |
| `get(index)` | $O(1)$ |

Ranges are zero-based and half-open.

## Methods

| Method | Description |
| --- | --- |
| `SqrtDecomposition(n)` | Creates `n` identity elements. |
| `SqrtDecomposition(values)` | Builds from an array. |
| `size()`, `empty()` | Return the array size and whether it is empty. |
| `set(index, value)` | Assigns an element and rebuilds its block. |
| `get(index)`, `operator[](index)` | Return an element. |
| `prod(left, right)` | Returns the ordered product over `[left, right)`. |
| `all_prod()` | Returns the product over the complete array. |

Construction from another element type uses `Monoid::make(value)`, then
`Monoid::make(value, index)`, then conversion to the monoid value type,
whichever is available.

## Block Access

For custom square-root-decomposition algorithms, the structure exposes:

* `block_size()` and `block_count()`
* `block_of(index)`
* `block_range(block)`
* `values()`
* `block_products()`

These views are read-only so the cached products cannot silently become stale.
Use `set` to modify an element.

## Example

```cpp
#include "ds/range_query/sqrt_decomposition.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {1, 2, 3, 4, 5};
    m1une::ds::SqrtDecomposition<m1une::monoid::Add<long long>> blocks(values);

    std::cout << blocks.prod(1, 4) << "\n";  // 9
    blocks.set(2, 10);
    std::cout << blocks.prod(1, 4) << "\n";  // 16
}
```
