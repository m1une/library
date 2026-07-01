---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dual_segtree.test.cpp
    title: verify/ds/segtree/dual_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/dual_segtree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <utility>\n#include <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
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
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/segtree/dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A generic Dual Segment Tree for range\
    \ monoid updates and point queries.\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct DualSegtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void all_apply(int k,\
    \ const T& x) {\n        _d[k] = Monoid::op(x, _d[k]);\n    }\n\n    void push(int\
    \ k) {\n        all_apply(2 * k, _d[k]);\n        all_apply(2 * k + 1, _d[k]);\n\
    \        _d[k] = Monoid::id();\n    }\n\n   public:\n    // Constructs an empty\
    \ dual segment tree.\n    DualSegtree() : DualSegtree(0) {}\n\n    // Constructs\
    \ a dual segment tree of size `n`, initialized with the identity element.\n  \
    \  explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n, Monoid::id()))\
    \ {}\n\n    // Constructs a dual segment tree from an existing vector.\n    explicit\
    \ DualSegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n\
    \    }\n    explicit DualSegtree(std::vector<T>&& v) : _n(int(v.size())) {\n \
    \       _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n\
    \        while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i]\
    \ = std::move(v[i]);\n    }\n\n    // Constructs a dual segment tree from a vector\
    \ of a different type U.\n    // It automatically adapts to the Monoid's initialization\
    \ requirements:\n    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val,\
    \ index) if the monoid requires global indices.\n    // 3. static_cast<T>(val)\
    \ as a fallback for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size())) {\n\
    \        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n\
    \        while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) {\n          \
    \  if constexpr (requires(U x) { Monoid::make(x); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i]);\n            } else if constexpr (requires(U x, int\
    \ idx) { Monoid::make(x, idx); }) {\n                _d[_size + i] = Monoid::make(v[i],\
    \ i);\n            } else {\n                _d[_size + i] = static_cast<T>(v[i]);\n\
    \            }\n        }\n    }\n\n    // Returns the number of elements.\n \
    \   int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Assigns x to the p-th element after applying pending updates on its path.\n\
    \    void set(int p, T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n\
    \        for (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p] = std::move(x);\n\
    \    }\n\n    // Returns the value of the p-th element after applying pending\
    \ updates on its path.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n\
    \        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _d[p];\n    }\n\n    // Returns the value of the p-th element.\n\
    \    T operator[](int p) {\n        return get(p);\n    }\n\n    // Applies x\
    \ to the p-th element.\n    void apply(int p, T x) {\n        assert(0 <= p &&\
    \ p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        all_apply(p, x);\n    }\n\n    // Applies x to all elements\
    \ in the range [l, r).\n    void apply(int l, int r, T x) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (l == r) return;\n\n        l += _size;\n\
    \        r += _size;\n\n        for (int i = _log; i >= 1; i--) {\n          \
    \  if (((l >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) !=\
    \ r) push((r - 1) >> i);\n        }\n\n        while (l < r) {\n            if\
    \ (l & 1) all_apply(l++, x);\n            if (r & 1) all_apply(--r, x);\n    \
    \        l >>= 1;\n            r >>= 1;\n        }\n    }\n\n    // Returns all\
    \ elements as a vector after applying all pending updates.\n    std::vector<T>\
    \ to_vector() {\n        for (int k = 1; k < _size; k++) push(k);\n        std::vector<T>\
    \ res;\n        res.reserve(_n);\n        for (int i = 0; i < _n; i++) res.push_back(_d[_size\
    \ + i]);\n        return res;\n    }\n\n    // Returns the elements in the range\
    \ [l, r) as a vector.\n    std::vector<T> to_vector(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        for (int i = l; i < r; i++) res.push_back(get(i));\n        return\
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DUAL_SEGTREE_HPP\n#define M1UNE_DUAL_SEGTREE_HPP 1\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"../../math/bit_ceil.hpp\"\n#include \"../../monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// A generic Dual Segment Tree for range monoid updates\
    \ and point queries.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct DualSegtree\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    int _n, _size,\
    \ _log;\n    std::vector<T> _d;\n\n    void all_apply(int k, const T& x) {\n \
    \       _d[k] = Monoid::op(x, _d[k]);\n    }\n\n    void push(int k) {\n     \
    \   all_apply(2 * k, _d[k]);\n        all_apply(2 * k + 1, _d[k]);\n        _d[k]\
    \ = Monoid::id();\n    }\n\n   public:\n    // Constructs an empty dual segment\
    \ tree.\n    DualSegtree() : DualSegtree(0) {}\n\n    // Constructs a dual segment\
    \ tree of size `n`, initialized with the identity element.\n    explicit DualSegtree(int\
    \ n) : DualSegtree(std::vector<T>(n, Monoid::id())) {}\n\n    // Constructs a\
    \ dual segment tree from an existing vector.\n    explicit DualSegtree(const std::vector<T>&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n;\
    \ i++) _d[_size + i] = v[i];\n    }\n    explicit DualSegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n;\
    \ i++) _d[_size + i] = std::move(v[i]);\n    }\n\n    // Constructs a dual segment\
    \ tree from a vector of a different type U.\n    // It automatically adapts to\
    \ the Monoid's initialization requirements:\n    // 1. Monoid::make(val) if it\
    \ exists.\n    // 2. Monoid::make(val, index) if the monoid requires global indices.\n\
    \    // 3. static_cast<T>(val) as a fallback for simple monoids.\n    template\
    \ <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x)\
    \ { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit DualSegtree(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) {\n            if constexpr (requires(U x) { Monoid::make(x); })\
    \ {\n                _d[_size + i] = Monoid::make(v[i]);\n            } else if\
    \ constexpr (requires(U x, int idx) { Monoid::make(x, idx); }) {\n           \
    \     _d[_size + i] = Monoid::make(v[i], i);\n            } else {\n         \
    \       _d[_size + i] = static_cast<T>(v[i]);\n            }\n        }\n    }\n\
    \n    // Returns the number of elements.\n    int size() const {\n        return\
    \ _n;\n    }\n\n    // Returns whether the tree is empty.\n    bool empty() const\
    \ {\n        return _n == 0;\n    }\n\n    // Assigns x to the p-th element after\
    \ applying pending updates on its path.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--)\
    \ push(p >> i);\n        _d[p] = std::move(x);\n    }\n\n    // Returns the value\
    \ of the p-th element after applying pending updates on its path.\n    T get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for (int\
    \ i = _log; i >= 1; i--) push(p >> i);\n        return _d[p];\n    }\n\n    //\
    \ Returns the value of the p-th element.\n    T operator[](int p) {\n        return\
    \ get(p);\n    }\n\n    // Applies x to the p-th element.\n    void apply(int\
    \ p, T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        all_apply(p, x);\n    }\n\
    \n    // Applies x to all elements in the range [l, r).\n    void apply(int l,\
    \ int r, T x) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l ==\
    \ r) return;\n\n        l += _size;\n        r += _size;\n\n        for (int i\
    \ = _log; i >= 1; i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n\
    \            if (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n    \
    \    while (l < r) {\n            if (l & 1) all_apply(l++, x);\n            if\
    \ (r & 1) all_apply(--r, x);\n            l >>= 1;\n            r >>= 1;\n   \
    \     }\n    }\n\n    // Returns all elements as a vector after applying all pending\
    \ updates.\n    std::vector<T> to_vector() {\n        for (int k = 1; k < _size;\
    \ k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n     \
    \   for (int i = 0; i < _n; i++) res.push_back(_d[_size + i]);\n        return\
    \ res;\n    }\n\n    // Returns the elements in the range [l, r) as a vector.\n\
    \    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        std::vector<T> res;\n        res.reserve(r - l);\n   \
    \     for (int i = l; i < r; i++) res.push_back(get(i));\n        return res;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dual_segtree.test.cpp
documentation_of: ds/segtree/dual_segtree.hpp
layout: document
title: Dual Segment Tree
---

## Overview

`m1une::ds::DualSegtree` is a generic dual segment tree for range
updates and point queries. Both updates and stored point values are elements of
the same monoid.

Use it when you only need point queries after range updates. If you also need
range queries, use `LazySegtree` instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

`apply(l, r, x)` updates each point value `v` in `[l, r)` to
`Monoid::op(x, v)`.

## Construction

* `DualSegtree()`: creates an empty tree.
* `DualSegtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `DualSegtree(const std::vector<T>& v)`: builds from monoid values.
* `DualSegtree(std::vector<T>&& v)`: builds from moved monoid values.
* `DualSegtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or
  `static_cast<T>(value)` is available.

Construction takes $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Pushes pending updates on the path and assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Pushes pending updates on the path and returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `void apply(int p, T x)` | Applies `x` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, T x)` | Applies `x` to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r - l) \log N)$ |

## Example

```cpp
#include "ds/segtree/dual_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    m1une::ds::DualSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});

    seg.apply(1, 4, 10);

    std::cout << seg.get(0) << "\n";  // 1
    std::cout << seg.get(2) << "\n";  // 13

    return 0;
}
```
