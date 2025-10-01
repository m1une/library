---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':question:'
    path: utilities/bit_ceil.hpp
    title: utilities/bit_ceil.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/unit_test/segtree.test.cpp
    title: verify/unit_test/segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/segtree/segtree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <functional>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"\
    monoid/monoid.hpp\"\n\n\n\n#include <concepts>\n#line 7 \"monoid/monoid.hpp\"\n\
    \nnamespace m1une {\n\ntemplate <typename T, auto operation, auto identity, bool\
    \ commutative>\nstruct monoid {\n    static_assert(std::is_invocable_r_v<T, decltype(operation),\
    \ T, T>, \"operation must work as T(T, T)\");\n    static_assert(std::is_invocable_r_v<T,\
    \ decltype(identity)>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires(typename T::value_type v) {\n\
    \    typename T::value_type;\n    { T::op(v, v) } -> std::same_as<typename T::value_type>;\n\
    \    { T::id() } -> std::same_as<typename T::value_type>;\n    { T::is_commutative\
    \ } -> std::convertible_to<bool>;\n};\n\n}  // namespace m1une\n\n\n#line 1 \"\
    utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n}  // namespace m1une\n\n\n#line 11 \"data_structure/segtree/segtree.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <Monoid M>\nstruct segment_tree {\n    using\
    \ T = typename M::value_type;\n\n   private:\n    int _n;\n    int _size;\n  \
    \  std::vector<T> _data;\n\n    void update(int k) {\n        _data[k] = M::op(_data[2\
    \ * k], _data[2 * k + 1]);\n    }\n\n   public:\n    segment_tree() : segment_tree(0)\
    \ {}\n    explicit segment_tree(int n) : segment_tree(std::vector<T>(n, M::id()))\
    \ {}\n    explicit segment_tree(const std::vector<T>& v) : _n(v.size()) {\n  \
    \      _size = bit_ceil((unsigned int)_n);\n        _data.assign(2 * _size, M::id());\n\
    \        for (int i = 0; i < _n; i++) {\n            _data[_size + i] = v[i];\n\
    \        }\n        for (int i = _size - 1; i >= 1; i--) {\n            update(i);\n\
    \        }\n    }\n\n    // Set value at position p\n    void set(int p, T x)\
    \ {\n        p += _size;\n        _data[p] = x;\n        for (int i = 1; p >>\
    \ i >= 1; i++) {\n            update(p >> i);\n        }\n    }\n\n    // Get\
    \ value at position p\n    T get(int p) const {\n        return _data[p + _size];\n\
    \    }\n\n    // Product of range [l, r)\n    T prod(int l, int r) const {\n \
    \       T sml = M::id(), smr = M::id();\n        l += _size;\n        r += _size;\n\
    \        while (l < r) {\n            if (l & 1) sml = M::op(sml, _data[l++]);\n\
    \            if (r & 1) smr = M::op(_data[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n        return M::op(sml, smr);\n    }\n\n \
    \   // Product of the whole range\n    T all_prod() const {\n        return _data[1];\n\
    \    }\n\n    // Find max_right r such that f(prod([l, r))) is true\n    int max_right(int\
    \ l, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (l == _n) return _n;\n        l += _size;\n\
    \        T sm = M::id();\n        do {\n            while (l % 2 == 0) l >>= 1;\n\
    \            if (!f(M::op(sm, _data[l]))) {\n                while (l < _size)\
    \ {\n                    l = (2 * l);\n                    if (f(M::op(sm, _data[l])))\
    \ {\n                        sm = M::op(sm, _data[l]);\n                     \
    \   l++;\n                    }\n                }\n                return l -\
    \ _size;\n            }\n            sm = M::op(sm, _data[l]);\n            l++;\n\
    \        } while ((l & -l) != l);\n        return _n;\n    }\n\n    // Find min_left\
    \ l such that f(prod([l, r))) is true\n    int min_left(int r, auto f) const {\n\
    \        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (r == 0) return 0;\n        r += _size;\n\
    \        T sm = M::id();\n        do {\n            r--;\n            while (r\
    \ > 1 && (r % 2)) r >>= 1;\n            if (!f(M::op(_data[r], sm))) {\n     \
    \           while (r < _size) {\n                    r = (2 * r + 1);\n      \
    \              if (f(M::op(_data[r], sm))) {\n                        sm = M::op(_data[r],\
    \ sm);\n                        r--;\n                    }\n                }\n\
    \                return r + 1 - _size;\n            }\n            sm = M::op(_data[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEGTREE_HPP\n#define M1UNE_SEGTREE_HPP 1\n\n#include <algorithm>\n\
    #include <functional>\n#include <type_traits>\n#include <vector>\n\n#include \"\
    monoid/monoid.hpp\"\n#include \"utilities/bit_ceil.hpp\"\n\nnamespace m1une {\n\
    \ntemplate <Monoid M>\nstruct segment_tree {\n    using T = typename M::value_type;\n\
    \n   private:\n    int _n;\n    int _size;\n    std::vector<T> _data;\n\n    void\
    \ update(int k) {\n        _data[k] = M::op(_data[2 * k], _data[2 * k + 1]);\n\
    \    }\n\n   public:\n    segment_tree() : segment_tree(0) {}\n    explicit segment_tree(int\
    \ n) : segment_tree(std::vector<T>(n, M::id())) {}\n    explicit segment_tree(const\
    \ std::vector<T>& v) : _n(v.size()) {\n        _size = bit_ceil((unsigned int)_n);\n\
    \        _data.assign(2 * _size, M::id());\n        for (int i = 0; i < _n; i++)\
    \ {\n            _data[_size + i] = v[i];\n        }\n        for (int i = _size\
    \ - 1; i >= 1; i--) {\n            update(i);\n        }\n    }\n\n    // Set\
    \ value at position p\n    void set(int p, T x) {\n        p += _size;\n     \
    \   _data[p] = x;\n        for (int i = 1; p >> i >= 1; i++) {\n            update(p\
    \ >> i);\n        }\n    }\n\n    // Get value at position p\n    T get(int p)\
    \ const {\n        return _data[p + _size];\n    }\n\n    // Product of range\
    \ [l, r)\n    T prod(int l, int r) const {\n        T sml = M::id(), smr = M::id();\n\
    \        l += _size;\n        r += _size;\n        while (l < r) {\n         \
    \   if (l & 1) sml = M::op(sml, _data[l++]);\n            if (r & 1) smr = M::op(_data[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ M::op(sml, smr);\n    }\n\n    // Product of the whole range\n    T all_prod()\
    \ const {\n        return _data[1];\n    }\n\n    // Find max_right r such that\
    \ f(prod([l, r))) is true\n    int max_right(int l, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (l == _n) return _n;\n        l += _size;\n\
    \        T sm = M::id();\n        do {\n            while (l % 2 == 0) l >>= 1;\n\
    \            if (!f(M::op(sm, _data[l]))) {\n                while (l < _size)\
    \ {\n                    l = (2 * l);\n                    if (f(M::op(sm, _data[l])))\
    \ {\n                        sm = M::op(sm, _data[l]);\n                     \
    \   l++;\n                    }\n                }\n                return l -\
    \ _size;\n            }\n            sm = M::op(sm, _data[l]);\n            l++;\n\
    \        } while ((l & -l) != l);\n        return _n;\n    }\n\n    // Find min_left\
    \ l such that f(prod([l, r))) is true\n    int min_left(int r, auto f) const {\n\
    \        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (r == 0) return 0;\n        r += _size;\n\
    \        T sm = M::id();\n        do {\n            r--;\n            while (r\
    \ > 1 && (r % 2)) r >>= 1;\n            if (!f(M::op(_data[r], sm))) {\n     \
    \           while (r < _size) {\n                    r = (2 * r + 1);\n      \
    \              if (f(M::op(_data[r], sm))) {\n                        sm = M::op(_data[r],\
    \ sm);\n                        r--;\n                    }\n                }\n\
    \                return r + 1 - _size;\n            }\n            sm = M::op(_data[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_SEGTREE_HPP\n"
  dependsOn:
  - monoid/monoid.hpp
  - utilities/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/segtree/segtree.hpp
  requiredBy: []
  timestamp: '2025-10-01 15:41:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/unit_test/segtree.test.cpp
documentation_of: data_structure/segtree/segtree.hpp
layout: document
title: Segment Tree
---

## Overview

A segment tree is a versatile data structure that allows for efficient range queries on an array. It can compute the result of any associative operation (defined by a monoid) over a given range `[l, r)` in logarithmic time. It also supports updating individual elements.

This implementation is generic and designed to be used with the [monoid](../../monoid/monoid.hpp) structures available in the library.

## Methods

* `segment_tree()`

  Constructs an empty segment tree.

  Time complexity: $O(1)$.

* `explicit segment_tree(int n)`

  Constructs a segment tree of size `n`, initialized with the identity element of the monoid.

  Time complexity: $O(N)$.

* `explicit segment_tree(const std::vector<T>& v)`

  Constructs a segment tree from an initial vector `v`.

  Time complexity: $O(N)$.

* `void set(int p, T x)`

  Sets the value at position `p` (0-indexed) to `x`.

  Time complexity: $O(\log N)$.

* `T get(int p) const`

  Returns the value at position `p` (0-indexed).

  Time complexity: $O(1)$.

* `T prod(int l, int r) const`

  Calculates the result of the monoid operation on the range `[l, r)` (0-indexed, half-open interval).

  Time complexity: $O(\log N)$.

* `T all_prod() const`

  Calculates the result of the monoid operation on the entire range `[0, n)`.

  Time complexity: $O(1)$.

* `int max_right(int l, auto f) const`

  Finds the largest `r` such that `l <= r <= n` and the predicate `f(prod(l, r))` is true. `f` must be a function that takes a monoid value and returns a boolean.

  Time complexity: $O(\log N)$.

* `int min_left(int r, auto f) const`

  Finds the smallest `l` such that `0 <= l <= r` and the predicate `f(prod(l, r))` is true. `f` must be a function that takes a monoid value and returns a boolean.

  Time complexity: $O(\log N)$.
