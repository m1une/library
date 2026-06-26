---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
    title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <memory>\n#include\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\n    requires std::equality_comparable<typename Group::value_type>\n\
    struct PersistentPotentializedDsu {\n    using T = typename Group::value_type;\n\
    \n    struct Value {\n        int parent_or_size;\n        T diff_to_parent;\n\
    \n        Value() : parent_or_size(0), diff_to_parent(Group::id()) {}\n      \
    \  Value(int parent_or_size_, const T& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(diff_to_parent_) {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n\
    \            : parent_or_size(parent_or_size_), diff_to_parent(std::move(diff_to_parent_))\
    \ {}\n    };\n\n   private:\n    struct Node {\n        Value val;\n        int\
    \ l, r;\n\n        Node() : val(), l(0), r(0) {}\n        explicit Node(const\
    \ Value& value) : val(value), l(0), r(0) {}\n        explicit Node(Value&& value)\
    \ : val(std::move(value)), l(0), r(0) {}\n        Node(const Value& value, int\
    \ left, int right) : val(value), l(left), r(right) {}\n        Node(Value&& value,\
    \ int left, int right) : val(std::move(value)), l(left), r(right) {}\n    };\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>> _pool;\n\
    \n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int build(int l, int r)\
    \ const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(Value(-1,\
    \ Group::id())));\n        int m = (l + r) >> 1;\n        int left = build(l,\
    \ m);\n        int right = build(m, r);\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    int set_node(int t, int l, int r, int p, Value\
    \ value) const {\n        if (r - l == 1) return new_node(Node(std::move(value)));\n\
    \        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int\
    \ right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, std::move(value));\n        } else {\n            right = set_node(right,\
    \ m, r, p, std::move(value));\n        }\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    Value get_value(int t, int l, int r, int p) const\
    \ {\n        while (r - l > 1) {\n            int m = (l + r) >> 1;\n        \
    \    if (p < m) {\n                t = (*_pool)[t].l;\n                r = m;\n\
    \            } else {\n                t = (*_pool)[t].r;\n                l =\
    \ m;\n            }\n        }\n        return (*_pool)[t].val;\n    }\n\n   \
    \ std::pair<int, T> leader_and_potential(int a) const {\n        T res = Group::id();\n\
    \        while (true) {\n            Value cur = get(a);\n            if (cur.parent_or_size\
    \ < 0) return {a, res};\n            res = Group::op(cur.diff_to_parent, res);\n\
    \            a = cur.parent_or_size;\n        }\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n     \
    \   assert(0 <= n);\n        _pool->reserve(n * 4 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       return leader_and_potential(a).first;\n    }\n\n    bool same(int a, int\
    \ b) const {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b <\
    \ _n);\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) const {\n        assert(0 <= a && a < _n);\n        return -get(leader(a)).parent_or_size;\n\
    \    }\n\n    int size(int a) const {\n        return group_size(a);\n    }\n\n\
    \    T potential(int a) const {\n        assert(0 <= a && a < _n);\n        return\
    \ leader_and_potential(a).second;\n    }\n\n    T diff(int a, int b) const {\n\
    \        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    Value get(int p) const {\n        assert(0 <= p\
    \ && p < _n);\n        return get_value(_root, 0, _n, p);\n    }\n\n    int parent_or_size(int\
    \ p) const {\n        return get(p).parent_or_size;\n    }\n\n    std::pair<PersistentPotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        assert(0 <= a && a <\
    \ _n);\n        assert(0 <= b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n\
    \        auto [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this,\
    \ Group::op(Group::inv(pa), pb) == w};\n\n        int sx = -get(x).parent_or_size;\n\
    \        int sy = -get(y).parent_or_size;\n        T y_from_x = Group::op(Group::op(pa,\
    \ w), Group::inv(pb));\n        if (sx < sy) {\n            std::swap(x, y);\n\
    \            std::swap(sx, sy);\n            y_from_x = Group::inv(y_from_x);\n\
    \        }\n        int root = set_node(_root, 0, _n, x, Value(-(sx + sy), Group::id()));\n\
    \        root = set_node(root, 0, _n, y, Value(x, std::move(y_from_x)));\n   \
    \     return {PersistentPotentializedDsu(_n, root, _pool), true};\n    }\n\n \
    \   std::vector<std::vector<int>> groups() const {\n        std::vector<int> leader_buf(_n),\
    \ group_size(_n);\n        for (int i = 0; i < _n; i++) {\n            leader_buf[i]\
    \ = leader(i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP\n#define M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <memory>\n#include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\n    requires std::equality_comparable<typename Group::value_type>\n\
    struct PersistentPotentializedDsu {\n    using T = typename Group::value_type;\n\
    \n    struct Value {\n        int parent_or_size;\n        T diff_to_parent;\n\
    \n        Value() : parent_or_size(0), diff_to_parent(Group::id()) {}\n      \
    \  Value(int parent_or_size_, const T& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(diff_to_parent_) {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n\
    \            : parent_or_size(parent_or_size_), diff_to_parent(std::move(diff_to_parent_))\
    \ {}\n    };\n\n   private:\n    struct Node {\n        Value val;\n        int\
    \ l, r;\n\n        Node() : val(), l(0), r(0) {}\n        explicit Node(const\
    \ Value& value) : val(value), l(0), r(0) {}\n        explicit Node(Value&& value)\
    \ : val(std::move(value)), l(0), r(0) {}\n        Node(const Value& value, int\
    \ left, int right) : val(value), l(left), r(right) {}\n        Node(Value&& value,\
    \ int left, int right) : val(std::move(value)), l(left), r(right) {}\n    };\n\
    \n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>> _pool;\n\
    \n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int build(int l, int r)\
    \ const {\n        if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(Value(-1,\
    \ Group::id())));\n        int m = (l + r) >> 1;\n        int left = build(l,\
    \ m);\n        int right = build(m, r);\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    int set_node(int t, int l, int r, int p, Value\
    \ value) const {\n        if (r - l == 1) return new_node(Node(std::move(value)));\n\
    \        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int\
    \ right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, std::move(value));\n        } else {\n            right = set_node(right,\
    \ m, r, p, std::move(value));\n        }\n        return new_node(Node(Value(),\
    \ left, right));\n    }\n\n    Value get_value(int t, int l, int r, int p) const\
    \ {\n        while (r - l > 1) {\n            int m = (l + r) >> 1;\n        \
    \    if (p < m) {\n                t = (*_pool)[t].l;\n                r = m;\n\
    \            } else {\n                t = (*_pool)[t].r;\n                l =\
    \ m;\n            }\n        }\n        return (*_pool)[t].val;\n    }\n\n   \
    \ std::pair<int, T> leader_and_potential(int a) const {\n        T res = Group::id();\n\
    \        while (true) {\n            Value cur = get(a);\n            if (cur.parent_or_size\
    \ < 0) return {a, res};\n            res = Group::op(cur.diff_to_parent, res);\n\
    \            a = cur.parent_or_size;\n        }\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n     \
    \   assert(0 <= n);\n        _pool->reserve(n * 4 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       return leader_and_potential(a).first;\n    }\n\n    bool same(int a, int\
    \ b) const {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b <\
    \ _n);\n        return leader(a) == leader(b);\n    }\n\n    int group_size(int\
    \ a) const {\n        assert(0 <= a && a < _n);\n        return -get(leader(a)).parent_or_size;\n\
    \    }\n\n    int size(int a) const {\n        return group_size(a);\n    }\n\n\
    \    T potential(int a) const {\n        assert(0 <= a && a < _n);\n        return\
    \ leader_and_potential(a).second;\n    }\n\n    T diff(int a, int b) const {\n\
    \        assert(same(a, b));\n        return Group::op(Group::inv(potential(a)),\
    \ potential(b));\n    }\n\n    Value get(int p) const {\n        assert(0 <= p\
    \ && p < _n);\n        return get_value(_root, 0, _n, p);\n    }\n\n    int parent_or_size(int\
    \ p) const {\n        return get(p).parent_or_size;\n    }\n\n    std::pair<PersistentPotentializedDsu,\
    \ bool> merge(int a, int b, const T& w) const {\n        assert(0 <= a && a <\
    \ _n);\n        assert(0 <= b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n\
    \        auto [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this,\
    \ Group::op(Group::inv(pa), pb) == w};\n\n        int sx = -get(x).parent_or_size;\n\
    \        int sy = -get(y).parent_or_size;\n        T y_from_x = Group::op(Group::op(pa,\
    \ w), Group::inv(pb));\n        if (sx < sy) {\n            std::swap(x, y);\n\
    \            std::swap(sx, sy);\n            y_from_x = Group::inv(y_from_x);\n\
    \        }\n        int root = set_node(_root, 0, _n, x, Value(-(sx + sy), Group::id()));\n\
    \        root = set_node(root, 0, _n, y, Value(x, std::move(y_from_x)));\n   \
    \     return {PersistentPotentializedDsu(_n, root, _pool), true};\n    }\n\n \
    \   std::vector<std::vector<int>> groups() const {\n        std::vector<int> leader_buf(_n),\
    \ group_size(_n);\n        for (int i = 0; i < _n; i++) {\n            leader_buf[i]\
    \ = leader(i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/dsu/persistent_potentialized_dsu.hpp
  requiredBy: []
  timestamp: '2026-06-27 02:45:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/persistent_potentialized_dsu.test.cpp
documentation_of: ds/dsu/persistent_potentialized_dsu.hpp
layout: document
title: Persistent Potentialized DSU
---

## Overview

`PersistentPotentializedDsu` is a persistent weighted Union-Find over a
commutative group. Merge operations return a new version and leave the old
version available, while preserving potential differences inside each component.

The template parameter is a type satisfying
`m1une::monoid::IsCommutativeGroup`. The stored constraint for
`merge(a, b, w)` is `diff(a, b) == w`, where `diff(a, b)` is
`Group::op(Group::inv(potential(a)), potential(b))`.

For `m1une::monoid::Add<long long>`, this means:

```cpp
potential(b) - potential(a) == w
```

Absolute values returned by `potential(v)` are root-relative. Use `diff(a, b)`
for stable values.

## Complexity Notation

* `N` is the number of elements.

## Template Parameters

* `Group`: A type satisfying `m1une::monoid::IsCommutativeGroup`.

The group value type must be equality comparable so repeated constraints can be
checked for consistency.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentPotentializedDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PersistentPotentializedDsu(int n)` | Creates `n` singleton sets with identity potentials. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `std::pair<PersistentPotentializedDsu, bool> merge(int a, int b, const T& w) const` | Returns a new version with the constraint `diff(a, b) == w`, and whether the constraint is consistent. If the constraint contradicts an existing component, the returned version is unchanged. | $O(\log^2 N)$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set. | $O(\log^2 N)$ |
| `int leader(int a) const` | Returns the representative of the set containing `a`. | $O(\log^2 N)$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the size of the set containing `a`. | $O(\log^2 N)$ |
| `T potential(int a) const` | Returns the root-relative potential of `a`. | $O(\log^2 N)$ |
| `T diff(int a, int b) const` | Returns the potential difference from `a` to `b`. Requires `same(a, b)`. | $O(\log^2 N)$ |
| `Value get(int p) const` | Returns the internal value at index `p`. It has `parent_or_size` and `diff_to_parent` members. | $O(\log N)$ |
| `int parent_or_size(int p) const` | Returns the internal parent-or-size value at index `p`. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups() const` | Returns all sets as vectors of element indices. | $O(N \log^2 N)$ |

## Example

```cpp
#include "ds/dsu/persistent_potentialized_dsu.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Dsu = m1une::ds::PersistentPotentializedDsu<Add>;

    Dsu dsu(3);

    auto [a, ok1] = dsu.merge(0, 1, 3);
    auto [b, ok2] = a.merge(1, 2, 4);
    auto [bad, ok3] = b.merge(0, 2, 8);

    std::cout << ok1 << "\n";          // 1
    std::cout << ok2 << "\n";          // 1
    std::cout << ok3 << "\n";          // 0
    std::cout << dsu.same(0, 2) << "\n"; // 0
    std::cout << b.diff(0, 2) << "\n"; // 7
}
```
