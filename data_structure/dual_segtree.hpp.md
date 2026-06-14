---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dual_segtree.test.cpp
    title: verify/data_structure/dual_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/dual_segtree.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <concepts>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"data_structure/dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// A generic Dual Segment\
    \ Tree for range updates and point queries.\n// It uses the operator monoid and\
    \ mapping from an ActedMonoid.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct DualSegtree {\n    using T = typename ActedMonoid::value_type;\n    using\
    \ F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n, _size,\
    \ _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    int node_length(int k) const\
    \ {\n        int level = std::bit_width((unsigned int)k) - 1;\n        return\
    \ _size >> level;\n    }\n\n    int node_left(int k) const {\n        int level\
    \ = std::bit_width((unsigned int)k) - 1;\n        int len = _size >> level;\n\
    \        return (k - (1 << level)) * len;\n    }\n\n    void all_apply(int k,\
    \ const F& f) {\n        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f,\
    \ _lz[k]);\n        } else {\n            _d[k - _size] = mapping_at(f, _d[k -\
    \ _size], 0);\n        }\n    }\n\n    void push(int k) {\n        all_apply(2\
    \ * k, _lz[k]);\n        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k)\
    \ / 2));\n        _lz[k] = ActedMonoid::op_id();\n    }\n\n   public:\n    //\
    \ Constructs an empty dual segment tree.\n    DualSegtree() : DualSegtree(0) {}\n\
    \n    // Constructs a dual segment tree of size `n`, initialized with the identity\
    \ element.\n    explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n, ActedMonoid::id()))\
    \ {}\n\n    // Constructs a dual segment tree from an existing vector.\n    explicit\
    \ DualSegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(_size, ActedMonoid::id());\n\
    \        _lz.assign(_size, ActedMonoid::op_id());\n        for (int i = 0; i <\
    \ _n; i++) _d[i] = v[i];\n    }\n    explicit DualSegtree(std::vector<T>&& v)\
    \ : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(_size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[i] = std::move(v[i]);\n    }\n\n    //\
    \ Constructs a dual segment tree from a vector of a different type U.\n    //\
    \ It automatically adapts to the ActedMonoid's initialization requirements:\n\
    \    // 1. ActedMonoid::make(val) if it exists.\n    // 2. ActedMonoid::make(val,\
    \ index) if the acted monoid requires global indices.\n    // 3. static_cast<T>(val)\
    \ as a fallback for simple value types.\n    template <typename U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(_size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) {\n            if constexpr (requires(U\
    \ x) { ActedMonoid::make(x); }) {\n                _d[i] = ActedMonoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { ActedMonoid::make(x,\
    \ idx); }) {\n                _d[i] = ActedMonoid::make(v[i], i);\n          \
    \  } else {\n                _d[i] = static_cast<T>(v[i]);\n            }\n  \
    \      }\n    }\n\n    // Returns the number of elements.\n    int size() const\
    \ {\n        return _n;\n    }\n\n    // Returns whether the tree is empty.\n\
    \    bool empty() const {\n        return _n == 0;\n    }\n\n    // Assigns x\
    \ to the p-th element after applying pending updates on its path.\n    void set(int\
    \ p, T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p - _size] = std::move(x);\n\
    \    }\n\n    // Returns the value of the p-th element after applying pending\
    \ updates on its path.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n\
    \        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _d[p - _size];\n    }\n\n    // Returns the value of the p-th\
    \ element.\n    T operator[](int p) {\n        return get(p);\n    }\n\n    //\
    \ Applies the operator f to the p-th element.\n    void apply(int p, F f) {\n\
    \        assert(0 <= p && p < _n);\n        p += _size;\n        for (int i =\
    \ _log; i >= 1; i--) push(p >> i);\n        _d[p - _size] = mapping_at(f, _d[p\
    \ - _size], 0);\n    }\n\n    // Applies the operator f to all elements in the\
    \ range [l, r).\n    void apply(int l, int r, F f) {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        if (l == r) return;\n\n        int base_l = l;\n\
    \        l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        while (l <\
    \ r) {\n            if (l & 1) {\n                all_apply(l, shift_operator(f,\
    \ node_left(l) - base_l));\n                l++;\n            }\n            if\
    \ (r & 1) {\n                --r;\n                all_apply(r, shift_operator(f,\
    \ node_left(r) - base_l));\n            }\n            l >>= 1;\n            r\
    \ >>= 1;\n        }\n    }\n\n    // Returns all elements as a vector after applying\
    \ all pending updates.\n    std::vector<T> to_vector() {\n        for (int k =\
    \ 1; k < _size; k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n\
    \        for (int i = 0; i < _n; i++) res.push_back(_d[i]);\n        return res;\n\
    \    }\n\n    // Returns the elements in the range [l, r) as a vector.\n    std::vector<T>\
    \ to_vector(int l, int r) {\n        assert(0 <= l && l <= r && r <= _n);\n  \
    \      std::vector<T> res;\n        res.reserve(r - l);\n        for (int i =\
    \ l; i < r; i++) res.push_back(get(i));\n        return res;\n    }\n};\n\n} \
    \ // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DUAL_SEGTREE_HPP\n#define M1UNE_DUAL_SEGTREE_HPP 1\n\n#include\
    \ <bit>\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"acted_monoid/concept.hpp\"\n#include \"math/bit_ceil.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// A generic Dual Segment\
    \ Tree for range updates and point queries.\n// It uses the operator monoid and\
    \ mapping from an ActedMonoid.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\n\
    struct DualSegtree {\n    using T = typename ActedMonoid::value_type;\n    using\
    \ F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n, _size,\
    \ _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    int node_length(int k) const\
    \ {\n        int level = std::bit_width((unsigned int)k) - 1;\n        return\
    \ _size >> level;\n    }\n\n    int node_left(int k) const {\n        int level\
    \ = std::bit_width((unsigned int)k) - 1;\n        int len = _size >> level;\n\
    \        return (k - (1 << level)) * len;\n    }\n\n    void all_apply(int k,\
    \ const F& f) {\n        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f,\
    \ _lz[k]);\n        } else {\n            _d[k - _size] = mapping_at(f, _d[k -\
    \ _size], 0);\n        }\n    }\n\n    void push(int k) {\n        all_apply(2\
    \ * k, _lz[k]);\n        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k)\
    \ / 2));\n        _lz[k] = ActedMonoid::op_id();\n    }\n\n   public:\n    //\
    \ Constructs an empty dual segment tree.\n    DualSegtree() : DualSegtree(0) {}\n\
    \n    // Constructs a dual segment tree of size `n`, initialized with the identity\
    \ element.\n    explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n, ActedMonoid::id()))\
    \ {}\n\n    // Constructs a dual segment tree from an existing vector.\n    explicit\
    \ DualSegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(_size, ActedMonoid::id());\n\
    \        _lz.assign(_size, ActedMonoid::op_id());\n        for (int i = 0; i <\
    \ _n; i++) _d[i] = v[i];\n    }\n    explicit DualSegtree(std::vector<T>&& v)\
    \ : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(_size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[i] = std::move(v[i]);\n    }\n\n    //\
    \ Constructs a dual segment tree from a vector of a different type U.\n    //\
    \ It automatically adapts to the ActedMonoid's initialization requirements:\n\
    \    // 1. ActedMonoid::make(val) if it exists.\n    // 2. ActedMonoid::make(val,\
    \ index) if the acted monoid requires global indices.\n    // 3. static_cast<T>(val)\
    \ as a fallback for simple value types.\n    template <typename U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(_size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) {\n            if constexpr (requires(U\
    \ x) { ActedMonoid::make(x); }) {\n                _d[i] = ActedMonoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { ActedMonoid::make(x,\
    \ idx); }) {\n                _d[i] = ActedMonoid::make(v[i], i);\n          \
    \  } else {\n                _d[i] = static_cast<T>(v[i]);\n            }\n  \
    \      }\n    }\n\n    // Returns the number of elements.\n    int size() const\
    \ {\n        return _n;\n    }\n\n    // Returns whether the tree is empty.\n\
    \    bool empty() const {\n        return _n == 0;\n    }\n\n    // Assigns x\
    \ to the p-th element after applying pending updates on its path.\n    void set(int\
    \ p, T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p - _size] = std::move(x);\n\
    \    }\n\n    // Returns the value of the p-th element after applying pending\
    \ updates on its path.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n\
    \        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _d[p - _size];\n    }\n\n    // Returns the value of the p-th\
    \ element.\n    T operator[](int p) {\n        return get(p);\n    }\n\n    //\
    \ Applies the operator f to the p-th element.\n    void apply(int p, F f) {\n\
    \        assert(0 <= p && p < _n);\n        p += _size;\n        for (int i =\
    \ _log; i >= 1; i--) push(p >> i);\n        _d[p - _size] = mapping_at(f, _d[p\
    \ - _size], 0);\n    }\n\n    // Applies the operator f to all elements in the\
    \ range [l, r).\n    void apply(int l, int r, F f) {\n        assert(0 <= l &&\
    \ l <= r && r <= _n);\n        if (l == r) return;\n\n        int base_l = l;\n\
    \        l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        while (l <\
    \ r) {\n            if (l & 1) {\n                all_apply(l, shift_operator(f,\
    \ node_left(l) - base_l));\n                l++;\n            }\n            if\
    \ (r & 1) {\n                --r;\n                all_apply(r, shift_operator(f,\
    \ node_left(r) - base_l));\n            }\n            l >>= 1;\n            r\
    \ >>= 1;\n        }\n    }\n\n    // Returns all elements as a vector after applying\
    \ all pending updates.\n    std::vector<T> to_vector() {\n        for (int k =\
    \ 1; k < _size; k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n\
    \        for (int i = 0; i < _n; i++) res.push_back(_d[i]);\n        return res;\n\
    \    }\n\n    // Returns the elements in the range [l, r) as a vector.\n    std::vector<T>\
    \ to_vector(int l, int r) {\n        assert(0 <= l && l <= r && r <= _n);\n  \
    \      std::vector<T> res;\n        res.reserve(r - l);\n        for (int i =\
    \ l; i < r; i++) res.push_back(get(i));\n        return res;\n    }\n};\n\n} \
    \ // namespace data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:52:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dual_segtree.test.cpp
documentation_of: data_structure/dual_segtree.hpp
layout: document
title: Dual Segment Tree
---

## Overview

`m1une::data_structure::DualSegtree` is a generic dual segment tree for range
updates and point queries. It is parameterized by an acted monoid and uses its
operator monoid for lazy tags and its `mapping` function to apply an operator to
one value.

Use it when you only need point queries after range updates. If you also need
range queries, use `LazySegtree` instead.

## Template Parameters

* `ActedMonoid`: A type satisfying `m1une::acted_monoid::IsActedMonoid`.

The acted monoid must provide:

* `using value_type = T`
* `using operator_type = F`
* `op_id()` and `op_comp(f, g)` for update operators
* `mapping(f, x)` to apply an operator to a value

The value monoid members required by `IsActedMonoid` are used for initialization
compatibility with the rest of the library. Ready-made acted monoids are
available in `acted_monoid/`.

## Construction

* `DualSegtree()`: creates an empty tree.
* `DualSegtree(int n)`: creates `n` elements initialized with
  `ActedMonoid::id()`.
* `DualSegtree(const std::vector<T>& v)`: builds from acted-monoid values.
* `DualSegtree(std::vector<T>&& v)`: builds from moved acted-monoid values.
* `DualSegtree(const std::vector<U>& v)`: builds from another value type when
  `ActedMonoid::make(value)`, `ActedMonoid::make(value, index)`, or
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
| `void apply(int p, F f)` | Applies operator `f` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, F f)` | Applies operator `f` to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r-l)\log N)$ |

## Example

```cpp
#include "data_structure/dual_segtree.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::data_structure::DualSegtree<AM> seg(std::vector<long long>{1, 2, 3, 4});

    seg.apply(1, 4, 10);

    std::cout << seg.get(0).sum << "\n";  // 1
    std::cout << seg.get(2).sum << "\n";  // 13

    return 0;
}
```
