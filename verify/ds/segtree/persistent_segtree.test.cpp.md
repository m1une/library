---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree.hpp
    title: Persistent Segment Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':question:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/segtree/persistent_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/segtree/persistent_segtree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <memory>\n#include <utility>\n\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/segtree/persistent_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct PersistentSegtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    struct Node {\n        T val;\n        int l, r;\n\n        Node() : val(Monoid::id()),\
    \ l(0), r(0) {}\n        explicit Node(T value) : val(std::move(value)), l(0),\
    \ r(0) {}\n        Node(T value, int left, int right) : val(std::move(value)),\
    \ l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentSegtree(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    template <typename U>\n\
    \    static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    int build(int l, int r, const\
    \ std::vector<T>& v) const {\n        if (l == r) return 0;\n        if (r - l\
    \ == 1) return new_node(Node(v[l]));\n        int m = (l + r) >> 1;\n        int\
    \ left = build(l, m, v);\n        int right = build(m, r, v);\n        return\
    \ new_node(Node(Monoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));\n\
    \    }\n\n    int build(int l, int r, std::vector<T>& v) const {\n        if (l\
    \ == r) return 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n\
    \        int m = (l + r) >> 1;\n        int left = build(l, m, v);\n        int\
    \ right = build(m, r, v);\n        return new_node(Node(Monoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    template <typename U>\n \
    \   int build_from_values(int l, int r, const std::vector<U>& v) const {\n   \
    \     if (l == r) return 0;\n        if (r - l == 1) return new_node(Node(make_value(v[l],\
    \ l)));\n        int m = (l + r) >> 1;\n        int left = build_from_values(l,\
    \ m, v);\n        int right = build_from_values(m, r, v);\n        return new_node(Node(Monoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    int set_node(int t, int l,\
    \ int r, int p, T value) const {\n        if (r - l == 1) return new_node(Node(std::move(value)));\n\
    \        int m = (l + r) >> 1;\n        int left = (*_pool)[t].l;\n        int\
    \ right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, std::move(value));\n        } else {\n            right = set_node(right,\
    \ m, r, p, std::move(value));\n        }\n        return new_node(Node(Monoid::op((*_pool)[left].val,\
    \ (*_pool)[right].val), left, right));\n    }\n\n    T prod_node(int t, int l,\
    \ int r, int ql, int qr) const {\n        if (!t || qr <= l || r <= ql) return\
    \ Monoid::id();\n        if (ql <= l && r <= qr) return (*_pool)[t].val;\n   \
    \     int m = (l + r) >> 1;\n        return Monoid::op(prod_node((*_pool)[t].l,\
    \ l, m, ql, qr), prod_node((*_pool)[t].r, m, r, ql, qr));\n    }\n\n    void collect_node(int\
    \ t, int l, int r, int ql, int qr, std::vector<T>& res) const {\n        if (!t\
    \ || qr <= l || r <= ql) return;\n        if (r - l == 1) {\n            res.push_back((*_pool)[t].val);\n\
    \            return;\n        }\n        int m = (l + r) >> 1;\n        collect_node((*_pool)[t].l,\
    \ l, m, ql, qr, res);\n        collect_node((*_pool)[t].r, m, r, ql, qr, res);\n\
    \    }\n\n    template <class F>\n    int max_right_node(int t, int l, int r,\
    \ int ql, T& sm, F& f) const {\n        if (r <= ql) return r;\n        if (ql\
    \ <= l) {\n            T nxt = Monoid::op(sm, (*_pool)[t].val);\n            if\
    \ (f(nxt)) {\n                sm = std::move(nxt);\n                return r;\n\
    \            }\n            if (r - l == 1) return l;\n        }\n        int\
    \ m = (l + r) >> 1;\n        int res = max_right_node((*_pool)[t].l, l, m, ql,\
    \ sm, f);\n        if (res < m) return res;\n        return max_right_node((*_pool)[t].r,\
    \ m, r, ql, sm, f);\n    }\n\n    template <class F>\n    int min_left_node(int\
    \ t, int l, int r, int qr, T& sm, F& f) const {\n        if (qr <= l) return l;\n\
    \        if (r <= qr) {\n            T nxt = Monoid::op((*_pool)[t].val, sm);\n\
    \            if (f(nxt)) {\n                sm = std::move(nxt);\n           \
    \     return l;\n            }\n            if (r - l == 1) return r;\n      \
    \  }\n        int m = (l + r) >> 1;\n        int res = min_left_node((*_pool)[t].r,\
    \ m, r, qr, sm, f);\n        if (m < res) return res;\n        return min_left_node((*_pool)[t].l,\
    \ l, m, qr, sm, f);\n    }\n\n   public:\n    PersistentSegtree() : PersistentSegtree(0)\
    \ {}\n\n    explicit PersistentSegtree(int n)\n        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        assert(0 <= n);\n        _pool->push_back(Node());\n        if (_n\
    \ > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));\n    }\n\n    explicit\
    \ PersistentSegtree(const std::vector<T>& v)\n        : _n(int(v.size())), _root(0),\
    \ _pool(std::make_shared<std::vector<Node>>()) {\n        _pool->reserve(v.size()\
    \ * 2 + 1);\n        _pool->push_back(Node());\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n    }\n\n    explicit PersistentSegtree(std::vector<T>&& v)\n     \
    \   : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n, v);\n    }\n\n    template <typename\
    \ U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U x)\
    \ { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||\n  \
    \               std::convertible_to<U, T>)\n    explicit PersistentSegtree(const\
    \ std::vector<U>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build_from_values(0, _n, v);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    PersistentSegtree set(int p, T x) const {\n        assert(0\
    \ <= p && p < _n);\n        return PersistentSegtree(_n, set_node(_root, 0, _n,\
    \ p, std::move(x)), _pool);\n    }\n\n    T get(int p) const {\n        assert(0\
    \ <= p && p < _n);\n        int t = _root;\n        int l = 0, r = _n;\n     \
    \   while (r - l > 1) {\n            int m = (l + r) >> 1;\n            if (p\
    \ < m) {\n                t = (*_pool)[t].l;\n                r = m;\n       \
    \     } else {\n                t = (*_pool)[t].r;\n                l = m;\n \
    \           }\n        }\n        return (*_pool)[t].val;\n    }\n\n    T operator[](int\
    \ p) const {\n        return get(p);\n    }\n\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return\
    \ Monoid::id();\n        return prod_node(_root, 0, _n, l, r);\n    }\n\n    T\
    \ all_prod() const {\n        return _root ? (*_pool)[_root].val : Monoid::id();\n\
    \    }\n\n    std::vector<T> to_vector() const {\n        return to_vector(0,\
    \ _n);\n    }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        collect_node(_root, 0, _n, l, r, res);\n        return res;\n\
    \    }\n\n    template <class F>\n    int max_right(int l, F f) const {\n    \
    \    assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n        if\
    \ (l == _n) return _n;\n        T sm = Monoid::id();\n        return max_right_node(_root,\
    \ 0, _n, l, sm, f);\n    }\n\n    template <class F>\n    int min_left(int r,\
    \ F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        T sm = Monoid::id();\n        return min_left_node(_root,\
    \ 0, _n, r, sm, f);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n#line 4 \"verify/ds/segtree/persistent_segtree.test.cpp\"\n\n#line 6 \"verify/ds/segtree/persistent_segtree.test.cpp\"\
    \n#include <iostream>\n#line 8 \"verify/ds/segtree/persistent_segtree.test.cpp\"\
    \n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n   \
    \ using value_type = T;\n\n    // Returns the identity element for addition, which\
    \ is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    //\
    \ Returns the sum of a and b.\n    static constexpr T op(const T& a, const T&\
    \ b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T& x)\
    \ {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 10 \"verify/ds/segtree/persistent_segtree.test.cpp\"\n\nint\
    \ main() {\n    using Seg = m1une::ds::PersistentSegtree<m1une::monoid::Add<long\
    \ long>>;\n\n    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});\n    Seg seg1\
    \ = seg.set(2, 10);\n    Seg seg2 = seg1.set(0, -1);\n\n    auto check = [](const\
    \ Seg& tree, const std::vector<long long>& a) {\n        assert(tree.size() ==\
    \ int(a.size()));\n        assert(tree.empty() == a.empty());\n        assert(tree.to_vector()\
    \ == a);\n        assert(tree.to_vector(1, 4) == std::vector<long long>(a.begin()\
    \ + 1, a.begin() + 4));\n        long long total = 0;\n        for (long long\
    \ x : a) total += x;\n        assert(tree.all_prod() == total);\n        for (int\
    \ l = 0; l <= int(a.size()); l++) {\n            long long sum = 0;\n        \
    \    for (int r = l; r <= int(a.size()); r++) {\n                assert(tree.prod(l,\
    \ r) == sum);\n                if (r < int(a.size())) sum += a[r];\n         \
    \   }\n        }\n        for (int i = 0; i < int(a.size()); i++) {\n        \
    \    assert(tree.get(i) == a[i]);\n            assert(tree[i] == a[i]);\n    \
    \    }\n    };\n\n    check(seg, {1, 2, 3, 4, 5});\n    check(seg1, {1, 2, 10,\
    \ 4, 5});\n    check(seg2, {-1, 2, 10, 4, 5});\n\n    assert(seg.prod(0, 5) ==\
    \ 15);\n    assert(seg1.prod(0, 5) == 22);\n    assert(seg2.prod(0, 5) == 20);\n\
    \    assert(seg.get(2) == 3);\n    assert(seg1.get(2) == 10);\n    assert(seg2.get(0)\
    \ == -1);\n    assert(seg1.max_right(0, [](long long x) { return x <= 13; }) ==\
    \ 3);\n    assert(seg1.min_left(5, [](long long x) { return x <= 9; }) == 3);\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/segtree/persistent_segtree.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n#include \"../../../monoid/add.hpp\"\n\nint main() {\n  \
    \  using Seg = m1une::ds::PersistentSegtree<m1une::monoid::Add<long long>>;\n\n\
    \    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});\n    Seg seg1 = seg.set(2,\
    \ 10);\n    Seg seg2 = seg1.set(0, -1);\n\n    auto check = [](const Seg& tree,\
    \ const std::vector<long long>& a) {\n        assert(tree.size() == int(a.size()));\n\
    \        assert(tree.empty() == a.empty());\n        assert(tree.to_vector() ==\
    \ a);\n        assert(tree.to_vector(1, 4) == std::vector<long long>(a.begin()\
    \ + 1, a.begin() + 4));\n        long long total = 0;\n        for (long long\
    \ x : a) total += x;\n        assert(tree.all_prod() == total);\n        for (int\
    \ l = 0; l <= int(a.size()); l++) {\n            long long sum = 0;\n        \
    \    for (int r = l; r <= int(a.size()); r++) {\n                assert(tree.prod(l,\
    \ r) == sum);\n                if (r < int(a.size())) sum += a[r];\n         \
    \   }\n        }\n        for (int i = 0; i < int(a.size()); i++) {\n        \
    \    assert(tree.get(i) == a[i]);\n            assert(tree[i] == a[i]);\n    \
    \    }\n    };\n\n    check(seg, {1, 2, 3, 4, 5});\n    check(seg1, {1, 2, 10,\
    \ 4, 5});\n    check(seg2, {-1, 2, 10, 4, 5});\n\n    assert(seg.prod(0, 5) ==\
    \ 15);\n    assert(seg1.prod(0, 5) == 22);\n    assert(seg2.prod(0, 5) == 20);\n\
    \    assert(seg.get(2) == 3);\n    assert(seg1.get(2) == 10);\n    assert(seg2.get(0)\
    \ == -1);\n    assert(seg1.max_right(0, [](long long x) { return x <= 13; }) ==\
    \ 3);\n    assert(seg1.min_left(5, [](long long x) { return x <= 9; }) == 3);\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - ds/segtree/persistent_segtree.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/segtree/persistent_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/persistent_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/persistent_segtree.test.cpp
- /verify/verify/ds/segtree/persistent_segtree.test.cpp.html
title: verify/ds/segtree/persistent_segtree.test.cpp
---
