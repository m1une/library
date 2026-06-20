---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/dsu_monoid.test.cpp
    title: verify/ds/dsu/dsu_monoid.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dsu/dsu_monoid.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <initializer_list>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/dsu/dsu_monoid.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct DsuMonoid {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n;\n    std::vector<int> parent_or_size;\n    std::vector<T> _prod;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n    template <typename U>\n    static T make_value(const U& value,\
    \ int index) {\n        if constexpr (requires(U x) { Monoid::make(x); }) {\n\
    \            return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n   public:\n    DsuMonoid() : DsuMonoid(0) {}\n\n    explicit\
    \ DsuMonoid(int n) : DsuMonoid(n, Monoid::id()) {}\n\n    DsuMonoid(int n, const\
    \ T& value) : _n(check_size(n)), parent_or_size(_n, -1), _prod(_n, value) {}\n\
    \n    explicit DsuMonoid(const std::vector<T>& v) : _n(int(v.size())), parent_or_size(_n,\
    \ -1), _prod(v) {}\n\n    explicit DsuMonoid(std::vector<T>&& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(std::move(v)) {}\n\n    template <typename U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { Monoid::make(x);\
    \ } ||\n        requires(U x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DsuMonoid(const std::vector<U>& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(_n, Monoid::id()) {\n        for (int i = 0; i\
    \ < _n; i++) _prod[i] = make_value(v[i], i);\n    }\n\n    DsuMonoid(std::initializer_list<T>\
    \ init) : DsuMonoid(std::vector<T>(init)) {}\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int merge(int a, int b) {\n        assert(0 <= a && a < _n);\n  \
    \      assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return x;\n        T merged = Monoid::op(_prod[x], _prod[y]);\n\
    \        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\n     \
    \   parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y] = x;\n\
    \        _prod[x] = std::move(merged);\n        return x;\n    }\n\n    bool same(int\
    \ a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    bool same(int\
    \ a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n    int\
    \ leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return\
    \ a;\n    }\n\n    int group_size(int a) {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int size(int a) {\n        return group_size(a);\n    }\n\n    int\
    \ size(int a) const {\n        return group_size(a);\n    }\n\n    T prod(int\
    \ a) {\n        return _prod[leader(a)];\n    }\n\n    T prod(int a) const {\n\
    \        return _prod[leader(a)];\n    }\n\n    T get(int a) {\n        return\
    \ prod(a);\n    }\n\n    T get(int a) const {\n        return prod(a);\n    }\n\
    \n    void set(int a, T value) {\n        _prod[leader(a)] = std::move(value);\n\
    \    }\n\n    std::vector<std::vector<int>> groups() {\n        std::vector<int>\
    \ leader_buf(_n), group_size(_n);\n        for (int i = 0; i < _n; i++) {\n  \
    \          leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
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
  code: "#ifndef M1UNE_DSU_MONOID_HPP\n#define M1UNE_DSU_MONOID_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <concepts>\n#include <initializer_list>\n\
    #include <utility>\n#include <vector>\n\n#include \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ DsuMonoid {\n    using T = typename Monoid::value_type;\n\n   private:\n   \
    \ int _n;\n    std::vector<int> parent_or_size;\n    std::vector<T> _prod;\n\n\
    \    static int check_size(int n) {\n        assert(0 <= n);\n        return n;\n\
    \    }\n\n    template <typename U>\n    static T make_value(const U& value, int\
    \ index) {\n        if constexpr (requires(U x) { Monoid::make(x); }) {\n    \
    \        return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n   public:\n    DsuMonoid() : DsuMonoid(0) {}\n\n    explicit\
    \ DsuMonoid(int n) : DsuMonoid(n, Monoid::id()) {}\n\n    DsuMonoid(int n, const\
    \ T& value) : _n(check_size(n)), parent_or_size(_n, -1), _prod(_n, value) {}\n\
    \n    explicit DsuMonoid(const std::vector<T>& v) : _n(int(v.size())), parent_or_size(_n,\
    \ -1), _prod(v) {}\n\n    explicit DsuMonoid(std::vector<T>&& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(std::move(v)) {}\n\n    template <typename U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { Monoid::make(x);\
    \ } ||\n        requires(U x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DsuMonoid(const std::vector<U>& v) : _n(int(v.size())),\
    \ parent_or_size(_n, -1), _prod(_n, Monoid::id()) {\n        for (int i = 0; i\
    \ < _n; i++) _prod[i] = make_value(v[i], i);\n    }\n\n    DsuMonoid(std::initializer_list<T>\
    \ init) : DsuMonoid(std::vector<T>(init)) {}\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int merge(int a, int b) {\n        assert(0 <= a && a < _n);\n  \
    \      assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return x;\n        T merged = Monoid::op(_prod[x], _prod[y]);\n\
    \        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\n     \
    \   parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y] = x;\n\
    \        _prod[x] = std::move(merged);\n        return x;\n    }\n\n    bool same(int\
    \ a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    bool same(int\
    \ a, int b) const {\n        return leader(a) == leader(b);\n    }\n\n    int\
    \ leader(int a) {\n        assert(0 <= a && a < _n);\n        if (parent_or_size[a]\
    \ < 0) return a;\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       while (parent_or_size[a] >= 0) a = parent_or_size[a];\n        return\
    \ a;\n    }\n\n    int group_size(int a) {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int group_size(int a) const {\n        return -parent_or_size[leader(a)];\n\
    \    }\n\n    int size(int a) {\n        return group_size(a);\n    }\n\n    int\
    \ size(int a) const {\n        return group_size(a);\n    }\n\n    T prod(int\
    \ a) {\n        return _prod[leader(a)];\n    }\n\n    T prod(int a) const {\n\
    \        return _prod[leader(a)];\n    }\n\n    T get(int a) {\n        return\
    \ prod(a);\n    }\n\n    T get(int a) const {\n        return prod(a);\n    }\n\
    \n    void set(int a, T value) {\n        _prod[leader(a)] = std::move(value);\n\
    \    }\n\n    std::vector<std::vector<int>> groups() {\n        std::vector<int>\
    \ leader_buf(_n), group_size(_n);\n        for (int i = 0; i < _n; i++) {\n  \
    \          leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
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
    \  // namespace m1une\n\n#endif  // M1UNE_DSU_MONOID_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/dsu/dsu_monoid.hpp
  requiredBy: []
  timestamp: '2026-06-20 20:27:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/dsu_monoid.test.cpp
documentation_of: ds/dsu/dsu_monoid.hpp
layout: document
title: DSU with Monoid
---

## Overview

`DsuMonoid` is a Disjoint Set Union that stores one monoid aggregate for each
connected component. Each singleton starts with its own value, and `merge(a, b)`
combines the aggregate of `a`'s component with the aggregate of `b`'s component.

The structure uses path compression and union by size, so DSU operations are
near constant time. The aggregate order is independent of the root chosen by
union by size: for noncommutative monoids, `merge(a, b)` stores
`Monoid::op(prod(a), prod(b))`.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static constexpr T id()`
* `static constexpr T op(const T& a, const T& b)`

## Construction

* `DsuMonoid()`: creates an empty DSU.
* `DsuMonoid(int n)`: creates `n` singleton sets initialized with
  `Monoid::id()`.
* `DsuMonoid(int n, const T& value)`: creates `n` singleton sets initialized
  with `value`.
* `DsuMonoid(const std::vector<T>& v)`: creates singleton sets from monoid
  values.
* `DsuMonoid(std::vector<T>&& v)`: creates singleton sets from moved monoid
  values.
* `DsuMonoid(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
  is available.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the DSU has no elements. | $O(1)$ |
| `int merge(int a, int b)` | Merges the sets containing `a` and `b`; returns the leader of the merged set. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set. | Amortized $O(\alpha(N))$ |
| `int leader(int a)` | Returns the representative of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `int group_size(int a)`, `int size(int a)` | Returns the size of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `T prod(int a)`, `T get(int a)` | Returns the aggregate of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `void set(int a, T value)` | Replaces the aggregate of the set containing `a`. | Amortized $O(\alpha(N))$ |
| `std::vector<std::vector<int>> groups()` | Returns all sets as vectors of element indices. | $O(N \alpha(N))$ |

## Example

```cpp
#include "ds/dsu/dsu_monoid.hpp"
#include "monoid/add.hpp"

#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::DsuMonoid<Sum> dsu(std::vector<long long>{1, 2, 3, 4, 5});

    dsu.merge(0, 1);
    dsu.merge(2, 3);
    dsu.merge(1, 2);

    std::cout << dsu.prod(0) << "\n";  // 10
    std::cout << dsu.size(0) << "\n";  // 4
    std::cout << dsu.prod(4) << "\n";  // 5
}
```
