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
    path: verify/ds/segtree/segtree.test.cpp
    title: verify/ds/segtree/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/segtree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <utility>\n#include <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/segtree/segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A generic Segment Tree utilizing C++20\
    \ Concepts for type safety.\n// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct Segtree {\n    using T = typename\
    \ Monoid::value_type;\n\n   private:\n    int _n, _size, _log;\n    std::vector<T>\
    \ _d;\n\n    void update(int k) {\n        _d[k] = Monoid::op(_d[2 * k], _d[2\
    \ * k + 1]);\n    }\n\n   public:\n    // Constructs an empty segment tree.\n\
    \    Segtree() : Segtree(0) {}\n\n    // Constructs a segment tree of size `n`,\
    \ initialized with the identity element.\n    explicit Segtree(int n) : Segtree(std::vector<T>(n,\
    \ Monoid::id())) {}\n\n    // Constructs a segment tree from an existing vector.\n\
    \    explicit Segtree(const std::vector<T>& v) : _n(int(v.size())) {\n       \
    \ _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n    \
    \    while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i]\
    \ = v[i];\n        for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n  \
    \  explicit Segtree(std::vector<T>&& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);\n\
    \        for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Constructs\
    \ a segment tree from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit Segtree(const std::vector<U>&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n;\
    \ i++) {\n            if constexpr (requires(U x) { Monoid::make(x); }) {\n  \
    \              _d[_size + i] = Monoid::make(v[i]);\n            } else if constexpr\
    \ (requires(U x, int idx) { Monoid::make(x, idx); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i], i);\n            } else {\n                _d[_size\
    \ + i] = static_cast<T>(v[i]);\n            }\n        }\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Returns the number of elements.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Sets the value of the element at index `p` to `x`.\n    void set(int p,\
    \ T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        _d[p]\
    \ = x;\n        for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n   \
    \ // Returns the value of the element at index `p`.\n    T get(int p) const {\n\
    \        assert(0 <= p && p < _n);\n        return _d[p + _size];\n    }\n\n \
    \   // Returns the value of the element at index `p`.\n    T operator[](int p)\
    \ const {\n        return get(p);\n    }\n\n    // Returns the product (result\
    \ of the monoid operation) in the range [l, r).\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        T sml = Monoid::id(),\
    \ smr = Monoid::id();\n        l += _size;\n        r += _size;\n        while\
    \ (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _d[l++]);\n        \
    \    if (r & 1) smr = Monoid::op(_d[--r], smr);\n            l >>= 1;\n      \
    \      r >>= 1;\n        }\n        return Monoid::op(sml, smr);\n    }\n\n  \
    \  // Returns the product of the entire array.\n    T all_prod() const {\n   \
    \     return _d[1];\n    }\n\n    // Returns all elements as a vector.\n    std::vector<T>\
    \ to_vector() const {\n        return to_vector(0, _n);\n    }\n\n    // Returns\
    \ the elements in the range [l, r) as a vector.\n    std::vector<T> to_vector(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        for (int i = l; i < r; i++) res.push_back(_d[_size\
    \ + i]);\n        return res;\n    }\n\n    // Finds the largest `r` such that\
    \ `f(prod(l, r))` is true.\n    // Uses a custom functor or lambda `f`.\n    template\
    \ <class F>\n    int max_right(int l, F f) const {\n        assert(0 <= l && l\
    \ <= _n);\n        assert(f(Monoid::id()));\n        if (l == _n) return _n;\n\
    \        l += _size;\n        T sm = Monoid::id();\n        do {\n           \
    \ while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm, _d[l]))) {\n\
    \                while (l < _size) {\n                    l = (2 * l);\n     \
    \               if (f(Monoid::op(sm, _d[l]))) {\n                        sm =\
    \ Monoid::op(sm, _d[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - _size;\n            }\n       \
    \     sm = Monoid::op(sm, _d[l]);\n            l++;\n        } while ((l & -l)\
    \ != l);\n        return _n;\n    }\n\n    // Finds the smallest `l` such that\
    \ `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int r, F\
    \ f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEGTREE_HPP\n#define M1UNE_SEGTREE_HPP 1\n\n#include <cassert>\n\
    #include <concepts>\n#include <utility>\n#include <vector>\n\n#include \"../../math/bit_ceil.hpp\"\
    \n#include \"../../monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A generic Segment Tree utilizing C++20 Concepts for type safety.\n// It requires\
    \ a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct Segtree {\n    using T = typename Monoid::value_type;\n\n  \
    \ private:\n    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void update(int\
    \ k) {\n        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n   public:\n\
    \    // Constructs an empty segment tree.\n    Segtree() : Segtree(0) {}\n\n \
    \   // Constructs a segment tree of size `n`, initialized with the identity element.\n\
    \    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}\n\n\
    \    // Constructs a segment tree from an existing vector.\n    explicit Segtree(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) _d[_size + i] = v[i];\n        for (int i = _size - 1; i >= 1;\
    \ i--) update(i);\n    }\n    explicit Segtree(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size\
    \ + i] = std::move(v[i]);\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Constructs a segment tree from a vector of a different type U.\n\
    \    // It automatically adapts to the Monoid's initialization requirements:\n\
    \    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index)\
    \ if the monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit Segtree(const std::vector<U>& v) : _n(int(v.size())) {\n  \
    \      _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n\
    \        while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) {\n          \
    \  if constexpr (requires(U x) { Monoid::make(x); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i]);\n            } else if constexpr (requires(U x, int\
    \ idx) { Monoid::make(x, idx); }) {\n                _d[_size + i] = Monoid::make(v[i],\
    \ i);\n            } else {\n                _d[_size + i] = static_cast<T>(v[i]);\n\
    \            }\n        }\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Returns the number of elements.\n    int size() const {\n   \
    \     return _n;\n    }\n\n    // Returns whether the tree is empty.\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Sets the value of\
    \ the element at index `p` to `x`.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        _d[p] = x;\n        for (int\
    \ i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return _d[p + _size];\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T operator[](int p) const {\n        return get(p);\n\
    \    }\n\n    // Returns the product (result of the monoid operation) in the range\
    \ [l, r).\n    T prod(int l, int r) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        T sml = Monoid::id(), smr = Monoid::id();\n        l += _size;\n\
    \        r += _size;\n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml,\
    \ _d[l++]);\n            if (r & 1) smr = Monoid::op(_d[--r], smr);\n        \
    \    l >>= 1;\n            r >>= 1;\n        }\n        return Monoid::op(sml,\
    \ smr);\n    }\n\n    // Returns the product of the entire array.\n    T all_prod()\
    \ const {\n        return _d[1];\n    }\n\n    // Returns all elements as a vector.\n\
    \    std::vector<T> to_vector() const {\n        return to_vector(0, _n);\n  \
    \  }\n\n    // Returns the elements in the range [l, r) as a vector.\n    std::vector<T>\
    \ to_vector(int l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        std::vector<T> res;\n        res.reserve(r - l);\n        for (int i\
    \ = l; i < r; i++) res.push_back(_d[_size + i]);\n        return res;\n    }\n\
    \n    // Finds the largest `r` such that `f(prod(l, r))` is true.\n    // Uses\
    \ a custom functor or lambda `f`.\n    template <class F>\n    int max_right(int\
    \ l, F f) const {\n        assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (l == _n) return _n;\n        l += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm,\
    \ _d[l]))) {\n                while (l < _size) {\n                    l = (2\
    \ * l);\n                    if (f(Monoid::op(sm, _d[l]))) {\n               \
    \         sm = Monoid::op(sm, _d[l]);\n                        l++;\n        \
    \            }\n                }\n                return l - _size;\n       \
    \     }\n            sm = Monoid::op(sm, _d[l]);\n            l++;\n        }\
    \ while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the smallest\
    \ `l` such that `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int\
    \ r, F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_SEGTREE_HPP\n"
  dependsOn:
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/segtree.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/segtree.test.cpp
documentation_of: ds/segtree/segtree.hpp
layout: document
title: Segment Tree
---

## Overview

`m1une::ds::Segtree` is a generic segment tree for point updates and
range queries. The query operation is supplied by a monoid, so the same data
structure can handle sums, minimums, maximums, gcd, affine composition, and other
associative operations.

Use it when updates affect one position at a time. For range updates, use
`LazySegtree` with an acted monoid instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

Ready-made monoids are available in `monoid/`.

## Construction

* `Segtree()`: creates an empty tree.
* `Segtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `Segtree(const std::vector<T>& v)`: builds from monoid values.
* `Segtree(std::vector<T>&& v)`: builds from moved monoid values.
* `Segtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
  is available.

All non-empty constructors build the tree in $O(N)$ time.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(1)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(1)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(r - l)$ |
| `int max_right<F>(int l, F f)` | Returns the largest `r` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |
| `int min_left<F>(int r, F f)` | Returns the smallest `l` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::Segtree<Sum> seg(std::vector<long long>{0, 0, 0, 0, 0});

    seg.set(0, 10);
    seg.set(2, 20);

    std::cout << seg.prod(0, 3) << "\n";  // 30

    return 0;
}
```
