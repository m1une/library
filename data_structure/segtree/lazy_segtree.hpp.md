---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: monoid/acted_monoid.hpp
    title: Acted Monoid
  - icon: ':question:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':question:'
    path: utilities/bit_ceil.hpp
    title: utilities/bit_ceil.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/unit_test/lazy_segtree.test.cpp
    title: verify/unit_test/lazy_segtree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/segtree/lazy_segtree.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <functional>\n#include <type_traits>\n#include <vector>\n\
    \n#line 1 \"monoid/acted_monoid.hpp\"\n\n\n\n#include <concepts>\n#line 7 \"monoid/acted_monoid.hpp\"\
    \n\n#line 1 \"monoid/monoid.hpp\"\n\n\n\n#line 7 \"monoid/monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <typename T, auto operation, auto identity, bool commutative>\n\
    struct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    template <typename T>\nconcept Monoid = requires {\n    typename T::value_type;\n\
    \    { T::op } -> std::convertible_to<std::function<typename T::value_type(typename\
    \ T::value_type, typename T::value_type)>>;\n    { T::id } -> std::convertible_to<std::function<typename\
    \ T::value_type()>>;\n    { T::is_commutative } -> std::convertible_to<bool>;\n\
    };\n\n}  // namespace m1une\n\n\n#line 9 \"monoid/acted_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\ntemplate <Monoid Data, Monoid Act, auto mapping>\nstruct acted_monoid\
    \ {\n    using data_monoid = Data;\n    using act_monoid = Act;\n\n    using data_type\
    \ = typename Data::value_type;\n    using act_type = typename Act::value_type;\n\
    \n    static_assert(std::is_convertible_v<decltype(mapping), std::function<data_type(act_type,\
    \ data_type)>>,\n                  \"mapping must work as data_type(data_type,\
    \ act_type)\");\n\n    static constexpr auto data_op = Data::op;\n    static constexpr\
    \ auto data_id = Data::id;\n    static constexpr bool data_is_commutative = Data::is_commutative;\n\
    \    static constexpr auto act_op = Act::op;\n    static constexpr auto act_id\
    \ = Act::id;\n    static constexpr bool act_is_commutative = Act::is_commutative;\n\
    \    static constexpr auto apply = mapping;\n};\n\ntemplate <typename T>\nconcept\
    \ ActedMonoid = requires {\n    typename T::data_monoid;\n    typename T::act_monoid;\n\
    \    typename T::data_type;\n    typename T::act_type;\n    {\n        T::data_op\n\
    \    } -> std::convertible_to<std::function<typename T::data_type(typename T::data_type,\
    \ typename T::data_type)>>;\n    { T::data_id } -> std::convertible_to<std::function<typename\
    \ T::data_type()>>;\n    { T::data_is_commutative } -> std::convertible_to<bool>;\n\
    \    {\n        T::act_op\n    } -> std::convertible_to<std::function<typename\
    \ T::act_type(typename T::act_type, typename T::act_type)>>;\n    { T::act_id\
    \ } -> std::convertible_to<std::function<typename T::act_type()>>;\n    { T::act_is_commutative\
    \ } -> std::convertible_to<bool>;\n    {\n        T::apply\n    } -> std::convertible_to<std::function<typename\
    \ T::data_type(typename T::act_type, typename T::data_type)>>;\n};\n\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n}  // namespace m1une\n\
    \n\n#line 11 \"data_structure/segtree/lazy_segtree.hpp\"\n\nnamespace m1une {\n\
    \ntemplate <ActedMonoid AM>\nstruct lazy_segment_tree {\n    using S = typename\
    \ AM::data_type;\n    using F = typename AM::act_type;\n\n   private:\n    int\
    \ _n;\n    int _size;\n    int _log;\n    std::vector<S> _data;\n    std::vector<F>\
    \ _lazy;\n\n    void update(int k) {\n        _data[k] = AM::data_op(_data[2 *\
    \ k], _data[2 * k + 1]);\n    }\n\n    void all_apply(int k, F f) {\n        _data[k]\
    \ = AM::apply(f, _data[k]);\n        if (k < _size) {\n            _lazy[k] =\
    \ AM::act_op(_lazy[k], f);\n        }\n    }\n\n    void push(int k) {\n     \
    \   all_apply(2 * k, _lazy[k]);\n        all_apply(2 * k + 1, _lazy[k]);\n   \
    \     _lazy[k] = AM::act_id();\n    }\n\n   public:\n    lazy_segment_tree() :\
    \ lazy_segment_tree(0) {}\n    explicit lazy_segment_tree(int n) : lazy_segment_tree(std::vector<S>(n,\
    \ AM::data_id())) {}\n    explicit lazy_segment_tree(const std::vector<S>& v)\
    \ : _n(v.size()) {\n        _size = bit_ceil((unsigned int)_n);\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)_size) _log++;\n        _data.assign(2\
    \ * _size, AM::data_id());\n        _lazy.assign(_size, AM::act_id());\n     \
    \   for (int i = 0; i < _n; i++) {\n            _data[_size + i] = v[i];\n   \
    \     }\n        for (int i = _size - 1; i >= 1; i--) {\n            update(i);\n\
    \        }\n    }\n\n    void set(int p, S x) {\n        p += _size;\n       \
    \ for (int i = _log; i >= 1; i--) push(p >> i);\n        _data[p] = x;\n     \
    \   for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    S get(int p)\
    \ {\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _data[p];\n    }\n\n    S prod(int l, int r) {\n        if (l\
    \ == r) return AM::data_id();\n\n        l += _size;\n        r += _size;\n\n\
    \        for (int i = _log; i >= 1; i--) {\n            if (((l >> i) << i) !=\
    \ l) push(l >> i);\n            if (((r >> i) << i) != r) push((r - 1) >> i);\n\
    \        }\n\n        S sml = AM::data_id(), smr = AM::data_id();\n        while\
    \ (l < r) {\n            if (l & 1) sml = AM::data_op(sml, _data[l++]);\n    \
    \        if (r & 1) smr = AM::data_op(_data[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n\n        return AM::data_op(sml, smr);\n  \
    \  }\n\n    S all_prod() {\n        return _data[1];\n    }\n\n    void apply(int\
    \ p, F f) {\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        _data[p] = AM::apply(f, _data[p]);\n        for (int i = 1;\
    \ i <= _log; i++) update(p >> i);\n    }\n\n    void apply(int l, int r, F f)\
    \ {\n        if (l == r) return;\n\n        l += _size;\n        r += _size;\n\
    \n        for (int i = _log; i >= 1; i--) {\n            if (((l >> i) << i) !=\
    \ l) push(l >> i);\n            if (((r >> i) << i) != r) push((r - 1) >> i);\n\
    \        }\n\n        {\n            int l2 = l, r2 = r;\n            while (l\
    \ < r) {\n                if (l & 1) all_apply(l++, f);\n                if (r\
    \ & 1) all_apply(--r, f);\n                l >>= 1;\n                r >>= 1;\n\
    \            }\n            l = l2;\n            r = r2;\n        }\n\n      \
    \  for (int i = 1; i <= _log; i++) {\n            if (((l >> i) << i) != l) update(l\
    \ >> i);\n            if (((r >> i) << i) != r) update((r - 1) >> i);\n      \
    \  }\n    }\n\n    int max_right(int l, auto g) {\n        if (l == _n) return\
    \ _n;\n        l += _size;\n        for (int i = _log; i >= 1; i--) push(l >>\
    \ i);\n        S sm = AM::data_id();\n        do {\n            while (l % 2 ==\
    \ 0) l >>= 1;\n            if (!g(AM::data_op(sm, _data[l]))) {\n            \
    \    while (l < _size) {\n                    push(l);\n                    l\
    \ = (2 * l);\n                    if (g(AM::data_op(sm, _data[l]))) {\n      \
    \                  sm = AM::data_op(sm, _data[l]);\n                        l++;\n\
    \                    }\n                }\n                return l - _size;\n\
    \            }\n            sm = AM::data_op(sm, _data[l]);\n            l++;\n\
    \        } while ((l & -l) != l);\n        return _n;\n    }\n\n    int min_left(int\
    \ r, auto g) {\n        if (r == 0) return 0;\n        r += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push((r - 1) >> i);\n        S sm = AM::data_id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!g(AM::data_op(_data[r], sm))) {\n                while (r <\
    \ _size) {\n                    push(r);\n                    r = (2 * r + 1);\n\
    \                    if (g(AM::data_op(_data[r], sm))) {\n                   \
    \     sm = AM::data_op(_data[r], sm);\n                        r--;\n        \
    \            }\n                }\n                return r + 1 - _size;\n   \
    \         }\n            sm = AM::data_op(_data[r], sm);\n        } while ((r\
    \ & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_LAZY_SEGTREE_HPP\n#define M1UNE_LAZY_SEGTREE_HPP 1\n\n#include\
    \ <algorithm>\n#include <functional>\n#include <type_traits>\n#include <vector>\n\
    \n#include \"monoid/acted_monoid.hpp\"\n#include \"utilities/bit_ceil.hpp\"\n\n\
    namespace m1une {\n\ntemplate <ActedMonoid AM>\nstruct lazy_segment_tree {\n \
    \   using S = typename AM::data_type;\n    using F = typename AM::act_type;\n\n\
    \   private:\n    int _n;\n    int _size;\n    int _log;\n    std::vector<S> _data;\n\
    \    std::vector<F> _lazy;\n\n    void update(int k) {\n        _data[k] = AM::data_op(_data[2\
    \ * k], _data[2 * k + 1]);\n    }\n\n    void all_apply(int k, F f) {\n      \
    \  _data[k] = AM::apply(f, _data[k]);\n        if (k < _size) {\n            _lazy[k]\
    \ = AM::act_op(_lazy[k], f);\n        }\n    }\n\n    void push(int k) {\n   \
    \     all_apply(2 * k, _lazy[k]);\n        all_apply(2 * k + 1, _lazy[k]);\n \
    \       _lazy[k] = AM::act_id();\n    }\n\n   public:\n    lazy_segment_tree()\
    \ : lazy_segment_tree(0) {}\n    explicit lazy_segment_tree(int n) : lazy_segment_tree(std::vector<S>(n,\
    \ AM::data_id())) {}\n    explicit lazy_segment_tree(const std::vector<S>& v)\
    \ : _n(v.size()) {\n        _size = bit_ceil((unsigned int)_n);\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)_size) _log++;\n        _data.assign(2\
    \ * _size, AM::data_id());\n        _lazy.assign(_size, AM::act_id());\n     \
    \   for (int i = 0; i < _n; i++) {\n            _data[_size + i] = v[i];\n   \
    \     }\n        for (int i = _size - 1; i >= 1; i--) {\n            update(i);\n\
    \        }\n    }\n\n    void set(int p, S x) {\n        p += _size;\n       \
    \ for (int i = _log; i >= 1; i--) push(p >> i);\n        _data[p] = x;\n     \
    \   for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    S get(int p)\
    \ {\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _data[p];\n    }\n\n    S prod(int l, int r) {\n        if (l\
    \ == r) return AM::data_id();\n\n        l += _size;\n        r += _size;\n\n\
    \        for (int i = _log; i >= 1; i--) {\n            if (((l >> i) << i) !=\
    \ l) push(l >> i);\n            if (((r >> i) << i) != r) push((r - 1) >> i);\n\
    \        }\n\n        S sml = AM::data_id(), smr = AM::data_id();\n        while\
    \ (l < r) {\n            if (l & 1) sml = AM::data_op(sml, _data[l++]);\n    \
    \        if (r & 1) smr = AM::data_op(_data[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n\n        return AM::data_op(sml, smr);\n  \
    \  }\n\n    S all_prod() {\n        return _data[1];\n    }\n\n    void apply(int\
    \ p, F f) {\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        _data[p] = AM::apply(f, _data[p]);\n        for (int i = 1;\
    \ i <= _log; i++) update(p >> i);\n    }\n\n    void apply(int l, int r, F f)\
    \ {\n        if (l == r) return;\n\n        l += _size;\n        r += _size;\n\
    \n        for (int i = _log; i >= 1; i--) {\n            if (((l >> i) << i) !=\
    \ l) push(l >> i);\n            if (((r >> i) << i) != r) push((r - 1) >> i);\n\
    \        }\n\n        {\n            int l2 = l, r2 = r;\n            while (l\
    \ < r) {\n                if (l & 1) all_apply(l++, f);\n                if (r\
    \ & 1) all_apply(--r, f);\n                l >>= 1;\n                r >>= 1;\n\
    \            }\n            l = l2;\n            r = r2;\n        }\n\n      \
    \  for (int i = 1; i <= _log; i++) {\n            if (((l >> i) << i) != l) update(l\
    \ >> i);\n            if (((r >> i) << i) != r) update((r - 1) >> i);\n      \
    \  }\n    }\n\n    int max_right(int l, auto g) {\n        if (l == _n) return\
    \ _n;\n        l += _size;\n        for (int i = _log; i >= 1; i--) push(l >>\
    \ i);\n        S sm = AM::data_id();\n        do {\n            while (l % 2 ==\
    \ 0) l >>= 1;\n            if (!g(AM::data_op(sm, _data[l]))) {\n            \
    \    while (l < _size) {\n                    push(l);\n                    l\
    \ = (2 * l);\n                    if (g(AM::data_op(sm, _data[l]))) {\n      \
    \                  sm = AM::data_op(sm, _data[l]);\n                        l++;\n\
    \                    }\n                }\n                return l - _size;\n\
    \            }\n            sm = AM::data_op(sm, _data[l]);\n            l++;\n\
    \        } while ((l & -l) != l);\n        return _n;\n    }\n\n    int min_left(int\
    \ r, auto g) {\n        if (r == 0) return 0;\n        r += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push((r - 1) >> i);\n        S sm = AM::data_id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!g(AM::data_op(_data[r], sm))) {\n                while (r <\
    \ _size) {\n                    push(r);\n                    r = (2 * r + 1);\n\
    \                    if (g(AM::data_op(_data[r], sm))) {\n                   \
    \     sm = AM::data_op(_data[r], sm);\n                        r--;\n        \
    \            }\n                }\n                return r + 1 - _size;\n   \
    \         }\n            sm = AM::data_op(_data[r], sm);\n        } while ((r\
    \ & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_LAZY_SEGTREE_HPP\n"
  dependsOn:
  - monoid/acted_monoid.hpp
  - monoid/monoid.hpp
  - utilities/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/segtree/lazy_segtree.hpp
  requiredBy: []
  timestamp: '2025-09-29 19:02:02+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/unit_test/lazy_segtree.test.cpp
documentation_of: data_structure/segtree/lazy_segtree.hpp
layout: document
title: Lazy Segment Tree
---

## Overview

A lazy segment tree is an advanced data structure that extends the functionality of a regular segment tree. It supports both range queries and range updates in logarithmic time. This is achieved by "lazily" propagating updates down the tree, applying them only when necessary.

This implementation is generic and designed to be used with the [acted_monoid](../../monoid/acted_monoid.hpp) structures available in the library, which define the data, the actions, and the mapping between them.

## Methods

* `lazy_segment_tree()`

    Constructs an empty lazy segment tree.

    Time complexity: $O(1)$.

* `explicit lazy_segment_tree(int n)`

    Constructs a lazy segment tree of size `n`, initialized with the identity element of the data monoid.

    Time complexity: $O(N)$.

* `explicit lazy_segment_tree(const std::vector<S>& v)`

    Constructs a lazy segment tree from an initial vector `v`.

    Time complexity: $O(N)$.

* `void set(int p, S x)`

    Sets the value at position `p` (0-indexed) to `x`.

    Time complexity: $O(\log N)$.

* `S get(int p)`

    Returns the value at position `p` (0-indexed).

    Time complexity: $O(\log N)$.

* `S prod(int l, int r)`

    Calculates the result of the data monoid operation on the range `[l, r)` (0-indexed, half-open interval).

    Time complexity: $O(\log N)$.

* `S all_prod()`

    Calculates the result of the data monoid operation on the entire range `[0, n)`.

    Time complexity: $O(1)$.

* `void apply(int p, F f)`

    Applies the action `f` to the element at position `p` (0-indexed).

    Time complexity: $O(\log N)$.

* `void apply(int l, int r, F f)`

    Applies the action `f` to all elements in the range `[l, r)` (0-indexed, half-open interval).

    Time complexity: $O(\log N)$.

* `int max_right(int l, auto g)`

    Finds the largest `r` such that `l <= r <= n` and the predicate `g(prod(l, r))` is true. `g` must be a function that takes a data monoid value and returns a boolean.

    Time complexity: $O(\log N)$.

* `int min_left(int r, auto g)`

    Finds the smallest `l` such that `0 <= l <= r` and the predicate `g(prod(l, r))` is true. `g` must be a function that takes a data monoid value and returns a boolean.

    Time complexity: $O(\log N)$.
