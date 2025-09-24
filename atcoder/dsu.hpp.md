---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"atcoder/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\nnamespace atcoder {\n\n// Implement (union by\
    \ size) + (path compression)\n// Reference:\n// Zvi Galil and Giuseppe F. Italiano,\n\
    // Data structures and algorithms for disjoint set union problems\nstruct dsu\
    \ {\n  public:\n    dsu() : _n(0) {}\n    explicit dsu(int n) : _n(n), parent_or_size(n,\
    \ -1) {}\n\n    int merge(int a, int b) {\n        assert(0 <= a && a < _n);\n\
    \        assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return x;\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    bool same(int a, int b) {\n        assert(0\
    \ <= a && a < _n);\n        assert(0 <= b && b < _n);\n        return leader(a)\
    \ == leader(b);\n    }\n\n    int leader(int a) {\n        assert(0 <= a && a\
    \ < _n);\n        if (parent_or_size[a] < 0) return a;\n        return parent_or_size[a]\
    \ = leader(parent_or_size[a]);\n    }\n\n    int size(int a) {\n        assert(0\
    \ <= a && a < _n);\n        return -parent_or_size[leader(a)];\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(\n            std::remove_if(result.begin(),\
    \ result.end(),\n                           [&](const std::vector<int>& v) { return\
    \ v.empty(); }),\n            result.end());\n        return result;\n    }\n\n\
    \  private:\n    int _n;\n    // root node: -1 * component size\n    // otherwise:\
    \ parent\n    std::vector<int> parent_or_size;\n};\n\n}  // namespace atcoder\n\
    \n\n"
  code: "#ifndef ATCODER_DSU_HPP\n#define ATCODER_DSU_HPP 1\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace atcoder {\n\n// Implement (union\
    \ by size) + (path compression)\n// Reference:\n// Zvi Galil and Giuseppe F. Italiano,\n\
    // Data structures and algorithms for disjoint set union problems\nstruct dsu\
    \ {\n  public:\n    dsu() : _n(0) {}\n    explicit dsu(int n) : _n(n), parent_or_size(n,\
    \ -1) {}\n\n    int merge(int a, int b) {\n        assert(0 <= a && a < _n);\n\
    \        assert(0 <= b && b < _n);\n        int x = leader(a), y = leader(b);\n\
    \        if (x == y) return x;\n        if (-parent_or_size[x] < -parent_or_size[y])\
    \ std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    bool same(int a, int b) {\n        assert(0\
    \ <= a && a < _n);\n        assert(0 <= b && b < _n);\n        return leader(a)\
    \ == leader(b);\n    }\n\n    int leader(int a) {\n        assert(0 <= a && a\
    \ < _n);\n        if (parent_or_size[a] < 0) return a;\n        return parent_or_size[a]\
    \ = leader(parent_or_size[a]);\n    }\n\n    int size(int a) {\n        assert(0\
    \ <= a && a < _n);\n        return -parent_or_size[leader(a)];\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(\n            std::remove_if(result.begin(),\
    \ result.end(),\n                           [&](const std::vector<int>& v) { return\
    \ v.empty(); }),\n            result.end());\n        return result;\n    }\n\n\
    \  private:\n    int _n;\n    // root node: -1 * component size\n    // otherwise:\
    \ parent\n    std::vector<int> parent_or_size;\n};\n\n}  // namespace atcoder\n\
    \n#endif  // ATCODER_DSU_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: atcoder/dsu.hpp
  requiredBy: []
  timestamp: '2025-07-18 03:34:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: atcoder/dsu.hpp
layout: document
title: Disjoint Set Union
---

# DSU

無向グラフに対して、

- 辺の追加
- $2$ 頂点が連結かの判定

をならし $O(\alpha(n))$ 時間で処理することが出来ます。

また、内部的に各連結成分ごとに代表となる頂点を $1$ つ持っています。辺の追加により連結成分がマージされる時、新たな代表元は元の連結成分の代表元のうちどちらかになります。

## コンストラクタ

```cpp
dsu d(int n)
```

- $n$ 頂点 $0$ 辺の無向グラフを作ります。

**@{keyword.constraints}**

- $0 \leq n \leq 10^8$

**@{keyword.complexity}**

- $O(n)$

## merge

```cpp
int d.merge(int a, int b)
```

辺 $(a, b)$ を足します。

$a, b$ が連結だった場合はその代表元、非連結だった場合は新たな代表元を返します。

**@{keyword.constraints}**

- $0 \leq a < n$
- $0 \leq b < n$

**@{keyword.complexity}**

- ならし $O(\alpha(n))$

## same

```cpp
bool d.same(int a, int b)
```

頂点 $a, b$ が連結かどうかを返します。

**@{keyword.constraints}**

- $0 \leq a < n$
- $0 \leq b < n$

**@{keyword.complexity}**

- ならし $O(\alpha(n))$

## leader

```cpp
int d.leader(int a)
```

頂点 $a$ の属する連結成分の代表元を返します。

**@{keyword.constraints}**

- $0 \leq a < n$

**@{keyword.complexity}**

- ならし $O(\alpha(n))$

## size

```cpp
int d.size(int a)
```

頂点 $a$ の属する連結成分のサイズを返します。

**@{keyword.constraints}**

- $0 \leq a < n$

**@{keyword.complexity}**

- ならし $O(\alpha(n))$

## groups

```cpp
vector<vector<int>> d.groups()
```

グラフを連結成分に分け、その情報を返します。

返り値は「「一つの連結成分の頂点番号のリスト」のリスト」です。
(内側外側限らず)vector内でどの順番で頂点が格納されているかは未定義です。

**@{keyword.complexity}**

- $O(n)$

## @{keyword.examples}

@{example.dsu_practice}
