---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/potentialized_dsu.test.cpp
    title: verify/ds/dsu/potentialized_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/potentialized_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
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
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/dsu/potentialized_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\nrequires std::equality_comparable<typename Group::value_type>\nstruct\
    \ PotentializedDsu {\n    using T = typename Group::value_type;\n\n   private:\n\
    \    int _n;\n    std::vector<int> parent_or_size;\n    std::vector<T> diff_to_parent;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n   public:\n    PotentializedDsu() : PotentializedDsu(0) {}\n\n\
    \    explicit PotentializedDsu(int n) : _n(check_size(n)), parent_or_size(_n,\
    \ -1), diff_to_parent(_n, Group::id()) {}\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        int p = parent_or_size[a];\n        int r = leader(p);\n\
    \        diff_to_parent[a] = Group::op(diff_to_parent[p], diff_to_parent[a]);\n\
    \        return parent_or_size[a] = r;\n    }\n\n    int leader(int a) const {\n\
    \        assert(0 <= a && a < _n);\n        while (parent_or_size[a] >= 0) a =\
    \ parent_or_size[a];\n        return a;\n    }\n\n    bool same(int a, int b)\
    \ {\n        return leader(a) == leader(b);\n    }\n\n    bool same(int a, int\
    \ b) const {\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent_or_size[leader(a)];\n    }\n\n    int size(int\
    \ a) {\n        return group_size(a);\n    }\n\n    int size(int a) const {\n\
    \        return group_size(a);\n    }\n\n    T potential(int a) {\n        leader(a);\n\
    \        return diff_to_parent[a];\n    }\n\n    T potential(int a) const {\n\
    \        assert(0 <= a && a < _n);\n        T res = Group::id();\n        while\
    \ (parent_or_size[a] >= 0) {\n            res = Group::op(diff_to_parent[a], res);\n\
    \            a = parent_or_size[a];\n        }\n        return res;\n    }\n\n\
    \    T diff(int a, int b) {\n        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    T diff(int a, int b) const {\n        assert(same(a,\
    \ b));\n        return Group::op(Group::inv(potential(a)), potential(b));\n  \
    \  }\n\n    bool merge(int a, int b, const T& w) {\n        assert(0 <= a && a\
    \ < _n);\n        assert(0 <= b && b < _n);\n        int x = leader(a);\n    \
    \    int y = leader(b);\n        T pa = diff_to_parent[a], pb = diff_to_parent[b];\n\
    \        if (x == y) return Group::op(Group::inv(pa), pb) == w;\n\n        T y_from_x\
    \ = Group::op(Group::op(pa, w), Group::inv(pb));\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) {\n            std::swap(x, y);\n            y_from_x\
    \ = Group::inv(y_from_x);\n        }\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        diff_to_parent[y] = std::move(y_from_x);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() {\n\
    \        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int i\
    \ = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n\
    \            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_POTENTIALIZED_DSU_HPP\n#define M1UNE_POTENTIALIZED_DSU_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\n\
    requires std::equality_comparable<typename Group::value_type>\nstruct PotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    int _n;\n \
    \   std::vector<int> parent_or_size;\n    std::vector<T> diff_to_parent;\n\n \
    \   static int check_size(int n) {\n        assert(0 <= n);\n        return n;\n\
    \    }\n\n   public:\n    PotentializedDsu() : PotentializedDsu(0) {}\n\n    explicit\
    \ PotentializedDsu(int n) : _n(check_size(n)), parent_or_size(_n, -1), diff_to_parent(_n,\
    \ Group::id()) {}\n\n    int size() const {\n        return _n;\n    }\n\n   \
    \ bool empty() const {\n        return _n == 0;\n    }\n\n    int leader(int a)\
    \ {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a] < 0) return\
    \ a;\n        int p = parent_or_size[a];\n        int r = leader(p);\n       \
    \ diff_to_parent[a] = Group::op(diff_to_parent[p], diff_to_parent[a]);\n     \
    \   return parent_or_size[a] = r;\n    }\n\n    int leader(int a) const {\n  \
    \      assert(0 <= a && a < _n);\n        while (parent_or_size[a] >= 0) a = parent_or_size[a];\n\
    \        return a;\n    }\n\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    bool same(int a, int b) const {\n        return\
    \ leader(a) == leader(b);\n    }\n\n    int group_size(int a) {\n        return\
    \ -parent_or_size[leader(a)];\n    }\n\n    int group_size(int a) const {\n  \
    \      return -parent_or_size[leader(a)];\n    }\n\n    int size(int a) {\n  \
    \      return group_size(a);\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    T potential(int a) {\n        leader(a);\n    \
    \    return diff_to_parent[a];\n    }\n\n    T potential(int a) const {\n    \
    \    assert(0 <= a && a < _n);\n        T res = Group::id();\n        while (parent_or_size[a]\
    \ >= 0) {\n            res = Group::op(diff_to_parent[a], res);\n            a\
    \ = parent_or_size[a];\n        }\n        return res;\n    }\n\n    T diff(int\
    \ a, int b) {\n        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    T diff(int a, int b) const {\n        assert(same(a,\
    \ b));\n        return Group::op(Group::inv(potential(a)), potential(b));\n  \
    \  }\n\n    bool merge(int a, int b, const T& w) {\n        assert(0 <= a && a\
    \ < _n);\n        assert(0 <= b && b < _n);\n        int x = leader(a);\n    \
    \    int y = leader(b);\n        T pa = diff_to_parent[a], pb = diff_to_parent[b];\n\
    \        if (x == y) return Group::op(Group::inv(pa), pb) == w;\n\n        T y_from_x\
    \ = Group::op(Group::op(pa, w), Group::inv(pb));\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) {\n            std::swap(x, y);\n            y_from_x\
    \ = Group::inv(y_from_x);\n        }\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        diff_to_parent[y] = std::move(y_from_x);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups() {\n\
    \        std::vector<int> leader_buf(_n), group_size(_n);\n        for (int i\
    \ = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n\
    \            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_POTENTIALIZED_DSU_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/dsu/potentialized_dsu.hpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/potentialized_dsu.test.cpp
documentation_of: ds/dsu/potentialized_dsu.hpp
layout: document
title: Potentialized DSU
---

## Overview

`PotentializedDsu` is a weighted Union-Find over a commutative group. It stores
relative potentials inside each connected component and can answer potential
differences between two vertices.

The template parameter is a type satisfying
`m1une::monoid::IsCommutativeGroup`, so the same data structure works with
addition, xor, and other invertible commutative operations.

The main operation is `merge(a, b, w)`, which adds the constraint
`diff(a, b) == w`. Here `diff(a, b)` is defined as
`Group::op(Group::inv(potential(a)), potential(b))`.

For `m1une::monoid::Add<long long>`, this means:

```cpp
potential(b) - potential(a) == w
```

Equivalently, `diff(a, b)` is `b - a` for addition.

For `m1une::monoid::Xor<int>`, this means:

```cpp
potential(a) ^ potential(b) == w
```

Absolute values returned by `potential(v)` are root-relative and may shift when
components are merged. Use `diff(a, b)` for stable values.

## Template Parameters

* `Group`: A type satisfying `m1une::monoid::IsCommutativeGroup`.

The group must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`
* `static constexpr T inv(const T& x)`

`T` must be equality comparable so repeated constraints can be checked for
consistency.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PotentializedDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PotentializedDsu(int n)` | Creates `n` singleton sets with identity potentials. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `bool merge(int a, int b, const T& w)` | Adds the constraint `diff(a, b) == w`. Returns `false` only when `a` and `b` were already connected and the constraint contradicts the stored potentials. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)`, `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)`, `int leader(int a) const` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int group_size(int a)`, `int group_size(int a) const`, `int size(int a)`, `int size(int a) const` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `T potential(int a)`, `T potential(int a) const` | Returns the root-relative potential of `a`. | Amortized $O(\alpha(N))$ |
| `T diff(int a, int b)`, `T diff(int a, int b) const` | Returns the potential difference from `a` to `b`. Requires `same(a, b)`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()`, `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Example

```cpp
#include "ds/dsu/potentialized_dsu.hpp"
#include "monoid/add.hpp"
#include "monoid/xor.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    m1une::ds::PotentializedDsu<Add> add_dsu(3);

    add_dsu.merge(0, 1, 3);
    add_dsu.merge(1, 2, 4);

    std::cout << add_dsu.diff(0, 2) << "\n";  // 7
    std::cout << add_dsu.merge(0, 2, 8) << "\n";  // 0, contradiction

    using Xor = m1une::monoid::Xor<int>;
    m1une::ds::PotentializedDsu<Xor> xor_dsu(3);

    xor_dsu.merge(0, 1, 5);
    xor_dsu.merge(1, 2, 6);

    std::cout << xor_dsu.diff(0, 2) << "\n";  // 3
}
```
