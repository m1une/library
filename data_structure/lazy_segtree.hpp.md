---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: utilities/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/lazy_segtree.hpp\"\n\n\n\n#include <vector>\n\
    #include <cassert>\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(\n\
    \    typename AM::value_type a, typename AM::value_type b,\n    typename AM::operator_type\
    \ f, typename AM::operator_type g\n) {\n    // 1. Value Monoid\n    typename AM::value_type;\n\
    \    { AM::id() } -> std::same_as<typename AM::value_type>;\n    { AM::op(a, b)\
    \ } -> std::same_as<typename AM::value_type>;\n\n    // 2. Operator Monoid\n \
    \   typename AM::operator_type;\n    { AM::op_id() } -> std::same_as<typename\
    \ AM::operator_type>;\n    { AM::op_comp(f, g) } -> std::same_as<typename AM::operator_type>;\
    \ // Composition order: f(g(x))\n\n    // 3. Mapping: Operator x Value -> Value\n\
    \    { AM::mapping(f, a) } -> std::same_as<typename AM::value_type>;\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"utilities/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\
    \n\n#line 8 \"data_structure/lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\n// A highly generic Lazy Segment Tree utilizing C++20 Concepts\
    \ for type safety.\n// It operates on any Acted Monoid structure satisfying the\
    \ `m1une::acted_monoid::IsActedMonoid` concept.\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n,\
    \ _size, _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    // Recalculates\
    \ the value of the node k from its children.\n    void update(int k) {\n     \
    \   _d[k] = ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n    // Applies\
    \ the operator f to the node k and updates its lazy tag if it's an internal node.\n\
    \    void all_apply(int k, F f) {\n        _d[k] = ActedMonoid::mapping(f, _d[k]);\n\
    \        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f, _lz[k]);\n\
    \        }\n    }\n\n    // Propagates the lazy tag of the node k down to its\
    \ children.\n    void push(int k) {\n        all_apply(2 * k, _lz[k]);\n     \
    \   all_apply(2 * k + 1, _lz[k]);\n        _lz[k] = ActedMonoid::op_id();\n  \
    \  }\n\n   public:\n    // Constructs an empty lazy segment tree.\n    LazySegtree()\
    \ : LazySegtree(0) {}\n\n    // Constructs a lazy segment tree of size `n`, initialized\
    \ with the identity element.\n    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n,\
    \ ActedMonoid::id())) {}\n\n    // Constructs a lazy segment tree from an existing\
    \ vector.\n    explicit LazySegtree(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::utilities::bit_ceil((unsigned int)(_n));\n       \
    \ _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n  \
    \      _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n        for (int\
    \ i = _size - 1; i >= 1; i--) update(i);\n    }\n    explicit LazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::utilities::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; i++) _d[_size + i] =\
    \ std::move(v[i]);\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Assigns x to the p-th element.\n    void set(int p, T x) {\n\
    \        assert(0 <= p && p < _n);\n        p += _size;\n        for (int i =\
    \ _log; i >= 1; i--) push(p >> i);\n        _d[p] = x;\n        for (int i = 1;\
    \ i <= _log; i++) update(p >> i);\n    }\n\n    // Returns the value of the p-th\
    \ element.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n        p +=\
    \ _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n        return\
    \ _d[p];\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return ActedMonoid::id();\n\n       \
    \ l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        T sml = ActedMonoid::id(),\
    \ smr = ActedMonoid::id();\n        while (l < r) {\n            if (l & 1) sml\
    \ = ActedMonoid::op(sml, _d[l++]);\n            if (r & 1) smr = ActedMonoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ ActedMonoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire\
    \ array.\n    T all_prod() const { return _d[1]; }\n\n    // Applies the operator\
    \ f to the p-th element.\n    void apply(int p, F f) {\n        assert(0 <= p\
    \ && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        _d[p] = ActedMonoid::mapping(f, _d[p]);\n        for (int i\
    \ = 1; i <= _log; i++) update(p >> i);\n    }\n\n    // Applies the operator f\
    \ to all elements in the range [l, r).\n    void apply(int l, int r, F f) {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n\n\
    \        l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        {\n       \
    \     int l2 = l, r2 = r;\n            while (l < r) {\n                if (l\
    \ & 1) all_apply(l++, f);\n                if (r & 1) all_apply(--r, f);\n   \
    \             l >>= 1;\n                r >>= 1;\n            }\n            l\
    \ = l2;\n            r = r2;\n        }\n\n        for (int i = 1; i <= _log;\
    \ i++) {\n            if (((l >> i) << i) != l) update(l >> i);\n            if\
    \ (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n    }\n\n    // Finds\
    \ the largest r such that g(prod(l, r)) is true.\n    template <class F_pred>\n\
    \    int max_right(int l, F_pred g) {\n        assert(0 <= l && l <= _n);\n  \
    \      assert(g(ActedMonoid::id()));\n        if (l == _n) return _n;\n      \
    \  l += _size;\n        for (int i = _log; i >= 1; i--) push(l >> i);\n      \
    \  T sm = ActedMonoid::id();\n        do {\n            while (l % 2 == 0) l >>=\
    \ 1;\n            if (!g(ActedMonoid::op(sm, _d[l]))) {\n                while\
    \ (l < _size) {\n                    push(l);\n                    l = (2 * l);\n\
    \                    if (g(ActedMonoid::op(sm, _d[l]))) {\n                  \
    \      sm = ActedMonoid::op(sm, _d[l]);\n                        l++;\n      \
    \              }\n                }\n                return l - _size;\n     \
    \       }\n            sm = ActedMonoid::op(sm, _d[l]);\n            l++;\n  \
    \      } while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the\
    \ smallest l such that g(prod(l, r)) is true.\n    template <class F_pred>\n \
    \   int min_left(int r, F_pred g) {\n        assert(0 <= r && r <= _n);\n    \
    \    assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n        r +=\
    \ _size;\n        for (int i = _log; i >= 1; i--) push((r - 1) >> i);\n      \
    \  T sm = ActedMonoid::id();\n        do {\n            r--;\n            while\
    \ (r > 1 && (r % 2)) r >>= 1;\n            if (!g(ActedMonoid::op(_d[r], sm)))\
    \ {\n                while (r < _size) {\n                    push(r);\n     \
    \               r = (2 * r + 1);\n                    if (g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                        sm = ActedMonoid::op(_d[r], sm);\n        \
    \                r--;\n                    }\n                }\n            \
    \    return r + 1 - _size;\n            }\n            sm = ActedMonoid::op(_d[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_LAZY_SEGTREE_HPP\n#define M1UNE_LAZY_SEGTREE_HPP 1\n\n#include\
    \ <vector>\n#include <cassert>\n#include \"acted_monoid/concept.hpp\"\n#include\
    \ \"utilities/bit_ceil.hpp\"\n\nnamespace m1une {\nnamespace data_structure {\n\
    \n// A highly generic Lazy Segment Tree utilizing C++20 Concepts for type safety.\n\
    // It operates on any Acted Monoid structure satisfying the `m1une::acted_monoid::IsActedMonoid`\
    \ concept.\ntemplate <m1une::acted_monoid::IsActedMonoid ActedMonoid>\nstruct\
    \ LazySegtree {\n    using T = typename ActedMonoid::value_type;\n    using F\
    \ = typename ActedMonoid::operator_type;\n\n   private:\n    int _n, _size, _log;\n\
    \    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    // Recalculates the value\
    \ of the node k from its children.\n    void update(int k) {\n        _d[k] =\
    \ ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n    // Applies the operator\
    \ f to the node k and updates its lazy tag if it's an internal node.\n    void\
    \ all_apply(int k, F f) {\n        _d[k] = ActedMonoid::mapping(f, _d[k]);\n \
    \       if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f, _lz[k]);\n\
    \        }\n    }\n\n    // Propagates the lazy tag of the node k down to its\
    \ children.\n    void push(int k) {\n        all_apply(2 * k, _lz[k]);\n     \
    \   all_apply(2 * k + 1, _lz[k]);\n        _lz[k] = ActedMonoid::op_id();\n  \
    \  }\n\n   public:\n    // Constructs an empty lazy segment tree.\n    LazySegtree()\
    \ : LazySegtree(0) {}\n\n    // Constructs a lazy segment tree of size `n`, initialized\
    \ with the identity element.\n    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n,\
    \ ActedMonoid::id())) {}\n\n    // Constructs a lazy segment tree from an existing\
    \ vector.\n    explicit LazySegtree(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::utilities::bit_ceil((unsigned int)(_n));\n       \
    \ _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n  \
    \      _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n        for (int\
    \ i = _size - 1; i >= 1; i--) update(i);\n    }\n    explicit LazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::utilities::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; i++) _d[_size + i] =\
    \ std::move(v[i]);\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Assigns x to the p-th element.\n    void set(int p, T x) {\n\
    \        assert(0 <= p && p < _n);\n        p += _size;\n        for (int i =\
    \ _log; i >= 1; i--) push(p >> i);\n        _d[p] = x;\n        for (int i = 1;\
    \ i <= _log; i++) update(p >> i);\n    }\n\n    // Returns the value of the p-th\
    \ element.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n        p +=\
    \ _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n        return\
    \ _d[p];\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return ActedMonoid::id();\n\n       \
    \ l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        T sml = ActedMonoid::id(),\
    \ smr = ActedMonoid::id();\n        while (l < r) {\n            if (l & 1) sml\
    \ = ActedMonoid::op(sml, _d[l++]);\n            if (r & 1) smr = ActedMonoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ ActedMonoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire\
    \ array.\n    T all_prod() const { return _d[1]; }\n\n    // Applies the operator\
    \ f to the p-th element.\n    void apply(int p, F f) {\n        assert(0 <= p\
    \ && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        _d[p] = ActedMonoid::mapping(f, _d[p]);\n        for (int i\
    \ = 1; i <= _log; i++) update(p >> i);\n    }\n\n    // Applies the operator f\
    \ to all elements in the range [l, r).\n    void apply(int l, int r, F f) {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return;\n\n\
    \        l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1;\
    \ i--) {\n            if (((l >> i) << i) != l) push(l >> i);\n            if\
    \ (((r >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        {\n       \
    \     int l2 = l, r2 = r;\n            while (l < r) {\n                if (l\
    \ & 1) all_apply(l++, f);\n                if (r & 1) all_apply(--r, f);\n   \
    \             l >>= 1;\n                r >>= 1;\n            }\n            l\
    \ = l2;\n            r = r2;\n        }\n\n        for (int i = 1; i <= _log;\
    \ i++) {\n            if (((l >> i) << i) != l) update(l >> i);\n            if\
    \ (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n    }\n\n    // Finds\
    \ the largest r such that g(prod(l, r)) is true.\n    template <class F_pred>\n\
    \    int max_right(int l, F_pred g) {\n        assert(0 <= l && l <= _n);\n  \
    \      assert(g(ActedMonoid::id()));\n        if (l == _n) return _n;\n      \
    \  l += _size;\n        for (int i = _log; i >= 1; i--) push(l >> i);\n      \
    \  T sm = ActedMonoid::id();\n        do {\n            while (l % 2 == 0) l >>=\
    \ 1;\n            if (!g(ActedMonoid::op(sm, _d[l]))) {\n                while\
    \ (l < _size) {\n                    push(l);\n                    l = (2 * l);\n\
    \                    if (g(ActedMonoid::op(sm, _d[l]))) {\n                  \
    \      sm = ActedMonoid::op(sm, _d[l]);\n                        l++;\n      \
    \              }\n                }\n                return l - _size;\n     \
    \       }\n            sm = ActedMonoid::op(sm, _d[l]);\n            l++;\n  \
    \      } while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the\
    \ smallest l such that g(prod(l, r)) is true.\n    template <class F_pred>\n \
    \   int min_left(int r, F_pred g) {\n        assert(0 <= r && r <= _n);\n    \
    \    assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n        r +=\
    \ _size;\n        for (int i = _log; i >= 1; i--) push((r - 1) >> i);\n      \
    \  T sm = ActedMonoid::id();\n        do {\n            r--;\n            while\
    \ (r > 1 && (r % 2)) r >>= 1;\n            if (!g(ActedMonoid::op(_d[r], sm)))\
    \ {\n                while (r < _size) {\n                    push(r);\n     \
    \               r = (2 * r + 1);\n                    if (g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                        sm = ActedMonoid::op(_d[r], sm);\n        \
    \                r--;\n                    }\n                }\n            \
    \    return r + 1 - _size;\n            }\n            sm = ActedMonoid::op(_d[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  - utilities/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/lazy_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-06 18:52:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/lazy_segtree.hpp
layout: document
title: Lazy Segment Tree
---

## Overview

A highly generic Lazy Segment Tree that supports both range queries and range updates (modifications) in $O(\log N)$ time. It operates on any Acted Monoid structure that satisfies the `m1une::acted_monoid::IsActedMonoid` concept.

## Template Parameters

* `ActedMonoid`: A struct representing the mathematical acted monoid, combining the `value_type`, `operator_type`, algebraic identities, internal operations, and the cross-mapping function.

## Methods

* `LazySegtree(int n)`
  Initializes an array of size $n$ with the value monoid's identity element. Time complexity: $O(N)$.

* `LazySegtree(const std::vector<T>& v)`
  Builds the lazy segment tree from the given vector in $O(N)$ time.

* `void set(int p, T x)`
  Assigns $x$ to the $p$-th element. Time complexity: $O(\log N)$.

* `T get(int p)`
  Returns the $p$-th element. Time complexity: $O(\log N)$.

* `T prod(int l, int r)`
  Returns the result of the monoid operation over the range $[l, r)$. Time complexity: $O(\log N)$.

* `T all_prod()`
  Returns the product of the entire array. Time complexity: $O(1)$.

* `void apply(int p, F f)`
  Applies the operator $f$ to the $p$-th element. Time complexity: $O(\log N)$.

* `void apply(int l, int r, F f)`
  Applies the operator $f$ to all elements in the range $[l, r)$. Time complexity: $O(\log N)$.

* `int max_right<G>(int l, G g)`
  Returns the largest index $r$ such that `g(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

* `int min_left<G>(int r, G g)`
  Returns the smallest index $l$ such that `g(prod(l, r))` is `true`. Time complexity: $O(\log N)$.

## Example

```cpp
#include "data_structure/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

int main() {
    int n = 6;
    std::vector<long long> v = {1, 3, 2, 5, 4, 0};

    // Use Range Add Range Min acted monoid
    using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;
    m1une::data_structure::LazySegtree<AM> seg(v);

    // Get min of range [1, 5) -> min(3, 2, 5, 4) = 2
    std::cout << seg.prod(1, 5) << "\n";

    // Add 10 to all elements in range [1, 4) -> v becomes {1, 13, 12, 15, 4, 0}
    seg.apply(1, 4, 10);

    // Get min of range [1, 5) -> min(13, 12, 15, 4) = 4
    std::cout << seg.prod(1, 5) << "\n";

    return 0;
}
```
