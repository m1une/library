---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sqrt_tree.test.cpp
    title: verify/ds/range_query/sqrt_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/sqrt_tree.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/range_query/sqrt_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Static Sqrt Tree with O(1) monoid-product\
    \ queries.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SqrtTree {\n   \
    \ using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::size_t\
    \ _padded_size;\n    std::vector<T> _values;\n    std::vector<int> _layers;\n\
    \    std::vector<int> _layer_for_bit;\n    std::vector<std::vector<T>> _prefix;\n\
    \    std::vector<std::vector<T>> _suffix;\n    std::vector<std::vector<T>> _between;\n\
    \n    template <class U>\n    static T make_value(const U& value, int index) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else if constexpr (requires(U x, int i) { Monoid::make(x,\
    \ i); }) {\n            return Monoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    void build_layers()\
    \ {\n        _layers.clear();\n        _layer_for_bit.clear();\n        if (_n\
    \ <= 1) return;\n\n        int exponent = std::bit_width(_padded_size) - 1;\n\
    \        _layers.push_back(exponent);\n        while (_layers.back() != 0) {\n\
    \            int current = _layers.back();\n            _layers.push_back(current\
    \ == 1 ? 0 : (current + 1) / 2);\n        }\n\n        _layer_for_bit.assign(exponent,\
    \ -1);\n        for (int layer = 0; layer + 1 < int(_layers.size()); ++layer)\
    \ {\n            for (\n                int bit = _layers[layer + 1];\n      \
    \          bit < _layers[layer];\n                ++bit\n            ) {\n   \
    \             _layer_for_bit[bit] = layer;\n            }\n        }\n    }\n\n\
    \    void build_level(int layer) {\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node_count = _padded_size / node_size;\n\n        _prefix[layer].assign(_padded_size,\
    \ Monoid::id());\n        _suffix[layer].assign(_padded_size, Monoid::id());\n\
    \        _between[layer].assign(\n            node_count * block_count * block_count,\n\
    \            Monoid::id()\n        );\n\n        for (\n            std::size_t\
    \ block_start = 0;\n            block_start < _padded_size;\n            block_start\
    \ += block_size\n        ) {\n            std::size_t block_end = block_start\
    \ + block_size;\n            _prefix[layer][block_start] = _values[block_start];\n\
    \            for (\n                std::size_t index = block_start + 1;\n   \
    \             index < block_end;\n                ++index\n            ) {\n \
    \               _prefix[layer][index] = Monoid::op(\n                    _prefix[layer][index\
    \ - 1],\n                    _values[index]\n                );\n            }\n\
    \n            _suffix[layer][block_end - 1] = _values[block_end - 1];\n      \
    \      for (std::size_t index = block_end - 1; block_start < index;) {\n     \
    \           --index;\n                _suffix[layer][index] = Monoid::op(\n  \
    \                  _values[index],\n                    _suffix[layer][index +\
    \ 1]\n                );\n            }\n        }\n\n        for (std::size_t\
    \ node = 0; node < node_count; ++node) {\n            std::size_t node_start =\
    \ node * node_size;\n            std::size_t table_start =\n                node\
    \ * block_count * block_count;\n            for (std::size_t first = 0; first\
    \ < block_count; ++first) {\n                T product = Monoid::id();\n     \
    \           for (std::size_t last = first; last < block_count; ++last) {\n   \
    \                 std::size_t block_end =\n                        node_start\
    \ + (last + 1) * block_size;\n                    product = Monoid::op(\n    \
    \                    product,\n                        _prefix[layer][block_end\
    \ - 1]\n                    );\n                    _between[layer][\n       \
    \                 table_start + first * block_count + last\n                 \
    \   ] = product;\n                }\n            }\n        }\n    }\n\n    void\
    \ build() {\n        if (_n == 0) {\n            _padded_size = 0;\n         \
    \   _layers.clear();\n            _layer_for_bit.clear();\n            _prefix.clear();\n\
    \            _suffix.clear();\n            _between.clear();\n            return;\n\
    \        }\n\n        _padded_size = std::bit_ceil(std::size_t(_n));\n       \
    \ _values.resize(_padded_size, Monoid::id());\n        build_layers();\n     \
    \   int level_count = _layers.empty() ? 0 : int(_layers.size()) - 1;\n       \
    \ _prefix.resize(level_count);\n        _suffix.resize(level_count);\n       \
    \ _between.resize(level_count);\n        for (int layer = 0; layer < level_count;\
    \ ++layer) {\n            build_level(layer);\n        }\n    }\n\n   public:\n\
    \    SqrtTree() : _n(0), _padded_size(0) {}\n\n    explicit SqrtTree(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values) {\n        build();\n    }\n\n    explicit SqrtTree(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(std::move(values)) {\n        build();\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtTree(const std::vector<U>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values.size(), Monoid::id()) {\n        for (int index = 0; index\
    \ < _n; ++index) {\n            _values[index] = make_value(values[index], index);\n\
    \        }\n        build();\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   // Returns the ordered monoid product over [left, right).\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return Monoid::id();\n        --right;\n\
    \        if (left == right) return _values[left];\n\n        std::size_t first\
    \ = std::size_t(left);\n        std::size_t last = std::size_t(right);\n     \
    \   int differing_bit = std::bit_width(first ^ last) - 1;\n        int layer =\
    \ _layer_for_bit[differing_bit];\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node = first / node_size;\n        std::size_t first_block\
    \ = (first % node_size) / block_size;\n        std::size_t last_block = (last\
    \ % node_size) / block_size;\n\n        T result = _suffix[layer][first];\n  \
    \      if (first_block + 1 < last_block) {\n            std::size_t table_start\
    \ =\n                node * block_count * block_count;\n            result = Monoid::op(\n\
    \                result,\n                _between[layer][\n                 \
    \   table_start\n                    + (first_block + 1) * block_count\n     \
    \               + (last_block - 1)\n                ]\n            );\n      \
    \  }\n        return Monoid::op(result, _prefix[layer][last]);\n    }\n\n    T\
    \ all_prod() const {\n        return prod(0, _n);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP\n#define M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <cstddef>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Static Sqrt Tree with O(1) monoid-product\
    \ queries.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SqrtTree {\n   \
    \ using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::size_t\
    \ _padded_size;\n    std::vector<T> _values;\n    std::vector<int> _layers;\n\
    \    std::vector<int> _layer_for_bit;\n    std::vector<std::vector<T>> _prefix;\n\
    \    std::vector<std::vector<T>> _suffix;\n    std::vector<std::vector<T>> _between;\n\
    \n    template <class U>\n    static T make_value(const U& value, int index) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else if constexpr (requires(U x, int i) { Monoid::make(x,\
    \ i); }) {\n            return Monoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    void build_layers()\
    \ {\n        _layers.clear();\n        _layer_for_bit.clear();\n        if (_n\
    \ <= 1) return;\n\n        int exponent = std::bit_width(_padded_size) - 1;\n\
    \        _layers.push_back(exponent);\n        while (_layers.back() != 0) {\n\
    \            int current = _layers.back();\n            _layers.push_back(current\
    \ == 1 ? 0 : (current + 1) / 2);\n        }\n\n        _layer_for_bit.assign(exponent,\
    \ -1);\n        for (int layer = 0; layer + 1 < int(_layers.size()); ++layer)\
    \ {\n            for (\n                int bit = _layers[layer + 1];\n      \
    \          bit < _layers[layer];\n                ++bit\n            ) {\n   \
    \             _layer_for_bit[bit] = layer;\n            }\n        }\n    }\n\n\
    \    void build_level(int layer) {\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node_count = _padded_size / node_size;\n\n        _prefix[layer].assign(_padded_size,\
    \ Monoid::id());\n        _suffix[layer].assign(_padded_size, Monoid::id());\n\
    \        _between[layer].assign(\n            node_count * block_count * block_count,\n\
    \            Monoid::id()\n        );\n\n        for (\n            std::size_t\
    \ block_start = 0;\n            block_start < _padded_size;\n            block_start\
    \ += block_size\n        ) {\n            std::size_t block_end = block_start\
    \ + block_size;\n            _prefix[layer][block_start] = _values[block_start];\n\
    \            for (\n                std::size_t index = block_start + 1;\n   \
    \             index < block_end;\n                ++index\n            ) {\n \
    \               _prefix[layer][index] = Monoid::op(\n                    _prefix[layer][index\
    \ - 1],\n                    _values[index]\n                );\n            }\n\
    \n            _suffix[layer][block_end - 1] = _values[block_end - 1];\n      \
    \      for (std::size_t index = block_end - 1; block_start < index;) {\n     \
    \           --index;\n                _suffix[layer][index] = Monoid::op(\n  \
    \                  _values[index],\n                    _suffix[layer][index +\
    \ 1]\n                );\n            }\n        }\n\n        for (std::size_t\
    \ node = 0; node < node_count; ++node) {\n            std::size_t node_start =\
    \ node * node_size;\n            std::size_t table_start =\n                node\
    \ * block_count * block_count;\n            for (std::size_t first = 0; first\
    \ < block_count; ++first) {\n                T product = Monoid::id();\n     \
    \           for (std::size_t last = first; last < block_count; ++last) {\n   \
    \                 std::size_t block_end =\n                        node_start\
    \ + (last + 1) * block_size;\n                    product = Monoid::op(\n    \
    \                    product,\n                        _prefix[layer][block_end\
    \ - 1]\n                    );\n                    _between[layer][\n       \
    \                 table_start + first * block_count + last\n                 \
    \   ] = product;\n                }\n            }\n        }\n    }\n\n    void\
    \ build() {\n        if (_n == 0) {\n            _padded_size = 0;\n         \
    \   _layers.clear();\n            _layer_for_bit.clear();\n            _prefix.clear();\n\
    \            _suffix.clear();\n            _between.clear();\n            return;\n\
    \        }\n\n        _padded_size = std::bit_ceil(std::size_t(_n));\n       \
    \ _values.resize(_padded_size, Monoid::id());\n        build_layers();\n     \
    \   int level_count = _layers.empty() ? 0 : int(_layers.size()) - 1;\n       \
    \ _prefix.resize(level_count);\n        _suffix.resize(level_count);\n       \
    \ _between.resize(level_count);\n        for (int layer = 0; layer < level_count;\
    \ ++layer) {\n            build_level(layer);\n        }\n    }\n\n   public:\n\
    \    SqrtTree() : _n(0), _padded_size(0) {}\n\n    explicit SqrtTree(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values) {\n        build();\n    }\n\n    explicit SqrtTree(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(std::move(values)) {\n        build();\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) {\
    \ Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i); }\
    \ ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtTree(const std::vector<U>&\
    \ values)\n        : _n(int(values.size())),\n          _padded_size(0),\n   \
    \       _values(values.size(), Monoid::id()) {\n        for (int index = 0; index\
    \ < _n; ++index) {\n            _values[index] = make_value(values[index], index);\n\
    \        }\n        build();\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   // Returns the ordered monoid product over [left, right).\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return Monoid::id();\n        --right;\n\
    \        if (left == right) return _values[left];\n\n        std::size_t first\
    \ = std::size_t(left);\n        std::size_t last = std::size_t(right);\n     \
    \   int differing_bit = std::bit_width(first ^ last) - 1;\n        int layer =\
    \ _layer_for_bit[differing_bit];\n        int node_exponent = _layers[layer];\n\
    \        int block_exponent = _layers[layer + 1];\n        std::size_t node_size\
    \ = std::size_t(1) << node_exponent;\n        std::size_t block_size = std::size_t(1)\
    \ << block_exponent;\n        std::size_t block_count = node_size / block_size;\n\
    \        std::size_t node = first / node_size;\n        std::size_t first_block\
    \ = (first % node_size) / block_size;\n        std::size_t last_block = (last\
    \ % node_size) / block_size;\n\n        T result = _suffix[layer][first];\n  \
    \      if (first_block + 1 < last_block) {\n            std::size_t table_start\
    \ =\n                node * block_count * block_count;\n            result = Monoid::op(\n\
    \                result,\n                _between[layer][\n                 \
    \   table_start\n                    + (first_block + 1) * block_count\n     \
    \               + (last_block - 1)\n                ]\n            );\n      \
    \  }\n        return Monoid::op(result, _prefix[layer][last]);\n    }\n\n    T\
    \ all_prod() const {\n        return prod(0, _n);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_SQRT_TREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/sqrt_tree.hpp
  requiredBy: []
  timestamp: '2026-06-23 02:27:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sqrt_tree.test.cpp
documentation_of: ds/range_query/sqrt_tree.hpp
layout: document
title: Sqrt Tree
---

## Overview

`SqrtTree<Monoid>` is a static range-product structure based on recursive
square-root decomposition. It supports any associative monoid, including
non-idempotent and non-commutative operations.

At each level, every block stores:

* prefix products,
* suffix products,
* products between complete child blocks.

A query uses the highest bit at which its two endpoints differ to select the
correct decomposition layer directly. It then combines at most three stored
products.

## Complexity

| Operation | Complexity |
| --- | --- |
| Construction | $O(N\log\log N)$ time and memory |
| `prod(left, right)` | $O(1)$ |
| `all_prod()` | $O(1)$ |

Compared with `DisjointSparseTable`, Sqrt Tree retains constant-time queries
while reducing preprocessing and memory from $O(N\log N)$ to
$O(N\log\log N)$.

## Methods

| Method | Description |
| --- | --- |
| `SqrtTree(values)` | Builds the structure from an array. |
| `size()` | Returns the array length. |
| `empty()` | Returns whether the array is empty. |
| `prod(left, right)` | Returns the ordered monoid product over `[left, right)`. |
| `all_prod()` | Returns the product over the complete array. |

An empty range returns `Monoid::id()`.

As with the repository's sparse tables, construction from another element type
uses `Monoid::make(value)`, then `Monoid::make(value, index)`, then conversion
to the monoid value type, whichever is available.

## Example

```cpp
#include "ds/range_query/sqrt_tree.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> values = {1, 2, 3, 4, 5};
    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);

    std::cout << tree.prod(1, 4) << "\n";  // 9
}
```
