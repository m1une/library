---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dual_segtree.test.cpp
    title: verify/data_structure/persistent_dual_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/persistent_dual_segtree.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <memory>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
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
    \ M::value_type a) {\n    { M::inverse(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"data_structure/persistent_dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct PersistentDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        T val;\n        int l, r;\n        bool\
    \ has_lazy;\n\n        Node() : val(Monoid::id()), l(0), r(0), has_lazy(false)\
    \ {}\n        explicit Node(T value) : val(std::move(value)), l(0), r(0), has_lazy(false)\
    \ {}\n        Node(int left, int right) : val(Monoid::id()), l(left), r(right),\
    \ has_lazy(false) {}\n    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentDualSegtree(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int clone_node(int t) const\
    \ {\n        return new_node((*_pool)[t]);\n    }\n\n    template <typename U>\n\
    \    static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    T compose_for_child(const T&\
    \ inherited, const Node& node) const {\n        if (!node.has_lazy) return inherited;\n\
    \        return Monoid::op(inherited, node.val);\n    }\n\n    int build(int l,\
    \ int r, const std::vector<T>& v) const {\n        if (l == r) return 0;\n   \
    \     if (r - l == 1) return new_node(Node(v[l]));\n        int m = (l + r) >>\
    \ 1;\n        return new_node(Node(build(l, m, v), build(m, r, v)));\n    }\n\n\
    \    int build(int l, int r, std::vector<T>& v) const {\n        if (l == r) return\
    \ 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n      \
    \  int m = (l + r) >> 1;\n        return new_node(Node(build(l, m, v), build(m,\
    \ r, v)));\n    }\n\n    template <typename U>\n    int build_from_values(int\
    \ l, int r, const std::vector<U>& v) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(make_value(v[l], l)));\n       \
    \ int m = (l + r) >> 1;\n        return new_node(Node(build_from_values(l, m,\
    \ v), build_from_values(m, r, v)));\n    }\n\n    void all_apply_to_node(int t,\
    \ const T& x, int l, int r) const {\n        Node& node = (*_pool)[t];\n     \
    \   if (r - l == 1) {\n            node.val = Monoid::op(x, node.val);\n     \
    \   } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val) :\
    \ x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, const T& x, int l, int r) const {\n        int res = clone_node(t);\n   \
    \     all_apply_to_node(res, x, l, r);\n        return res;\n    }\n\n    void\
    \ push(int t, int l, int r) const {\n        Node node = (*_pool)[t];\n      \
    \  if (!node.has_lazy || r - l == 1) return;\n        int m = (l + r) >> 1;\n\
    \        int left = all_apply_clone(node.l, node.val, l, m);\n        int right\
    \ = all_apply_clone(node.r, node.val, m, r);\n        Node& target = (*_pool)[t];\n\
    \        target.l = left;\n        target.r = right;\n        target.val = Monoid::id();\n\
    \        target.has_lazy = false;\n    }\n\n    int set_node(int t, int l, int\
    \ r, int p, T value) const {\n        t = clone_node(t);\n        if (r - l ==\
    \ 1) {\n            Node& node = (*_pool)[t];\n            node.val = std::move(value);\n\
    \            node.has_lazy = false;\n            return t;\n        }\n      \
    \  push(t, l, r);\n        int m = (l + r) >> 1;\n        if (p < m) {\n     \
    \       (*_pool)[t].l = set_node((*_pool)[t].l, l, m, p, std::move(value));\n\
    \        } else {\n            (*_pool)[t].r = set_node((*_pool)[t].r, m, r, p,\
    \ std::move(value));\n        }\n        return t;\n    }\n\n    int apply_node(int\
    \ t, int l, int r, int ql, int qr, const T& x) const {\n        if (qr <= l ||\
    \ r <= ql) return t;\n        t = clone_node(t);\n        if (ql <= l && r <=\
    \ qr) {\n            all_apply_to_node(t, x, l, r);\n            return t;\n \
    \       }\n        push(t, l, r);\n        int m = (l + r) >> 1;\n        (*_pool)[t].l\
    \ = apply_node((*_pool)[t].l, l, m, ql, qr, x);\n        (*_pool)[t].r = apply_node((*_pool)[t].r,\
    \ m, r, ql, qr, x);\n        return t;\n    }\n\n    T get_node(int t, int l,\
    \ int r, int p, const T& inherited) const {\n        const Node& node = (*_pool)[t];\n\
    \        if (r - l == 1) return Monoid::op(inherited, node.val);\n        int\
    \ m = (l + r) >> 1;\n        if (p < m) return get_node(node.l, l, m, p, compose_for_child(inherited,\
    \ node));\n        return get_node(node.r, m, r, p, compose_for_child(inherited,\
    \ node));\n    }\n\n    void collect_node(int t, int l, int r, int ql, int qr,\
    \ const T& inherited, std::vector<T>& res) const {\n        if (!t || qr <= l\
    \ || r <= ql) return;\n        const Node& node = (*_pool)[t];\n        if (r\
    \ - l == 1) {\n            res.push_back(Monoid::op(inherited, node.val));\n \
    \           return;\n        }\n        int m = (l + r) >> 1;\n        T next\
    \ = compose_for_child(inherited, node);\n        collect_node(node.l, l, m, ql,\
    \ qr, next, res);\n        collect_node(node.r, m, r, ql, qr, next, res);\n  \
    \  }\n\n   public:\n    PersistentDualSegtree() : PersistentDualSegtree(0) {}\n\
    \n    explicit PersistentDualSegtree(int n)\n        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        assert(0 <= n);\n        _pool->push_back(Node());\n        if (_n\
    \ > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));\n    }\n\n    explicit\
    \ PersistentDualSegtree(const std::vector<T>& v)\n        : _n(int(v.size())),\
    \ _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n        _pool->reserve(v.size()\
    \ * 2 + 1);\n        _pool->push_back(Node());\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n    }\n\n    explicit PersistentDualSegtree(std::vector<T>&& v)\n \
    \       : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n, v);\n    }\n\n    template <typename\
    \ U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U x)\
    \ { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||\n  \
    \               std::convertible_to<U, T>)\n    explicit PersistentDualSegtree(const\
    \ std::vector<U>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build_from_values(0, _n, v);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    PersistentDualSegtree set(int p, T x) const {\n     \
    \   assert(0 <= p && p < _n);\n        return PersistentDualSegtree(_n, set_node(_root,\
    \ 0, _n, p, std::move(x)), _pool);\n    }\n\n    T get(int p) const {\n      \
    \  assert(0 <= p && p < _n);\n        return get_node(_root, 0, _n, p, Monoid::id());\n\
    \    }\n\n    T operator[](int p) const {\n        return get(p);\n    }\n\n \
    \   PersistentDualSegtree apply(int p, const T& x) const {\n        assert(0 <=\
    \ p && p < _n);\n        return apply(p, p + 1, x);\n    }\n\n    PersistentDualSegtree\
    \ apply(int l, int r, const T& x) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        if (l == r) return *this;\n        return PersistentDualSegtree(_n,\
    \ apply_node(_root, 0, _n, l, r, x), _pool);\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        collect_node(_root, 0, _n, l, r,\
    \ Monoid::id(), res);\n        return res;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DUAL_SEGTREE_HPP\n#define M1UNE_PERSISTENT_DUAL_SEGTREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\n#include \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ data_structure {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct PersistentDualSegtree\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node\
    \ {\n        T val;\n        int l, r;\n        bool has_lazy;\n\n        Node()\
    \ : val(Monoid::id()), l(0), r(0), has_lazy(false) {}\n        explicit Node(T\
    \ value) : val(std::move(value)), l(0), r(0), has_lazy(false) {}\n        Node(int\
    \ left, int right) : val(Monoid::id()), l(left), r(right), has_lazy(false) {}\n\
    \    };\n\n    int _n;\n    int _root;\n    std::shared_ptr<std::vector<Node>>\
    \ _pool;\n\n    explicit PersistentDualSegtree(int n, int root, std::shared_ptr<std::vector<Node>>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {}\n\n    int new_node(const\
    \ Node& node) const {\n        _pool->push_back(node);\n        return int(_pool->size())\
    \ - 1;\n    }\n\n    int new_node(Node&& node) const {\n        _pool->push_back(std::move(node));\n\
    \        return int(_pool->size()) - 1;\n    }\n\n    int clone_node(int t) const\
    \ {\n        return new_node((*_pool)[t]);\n    }\n\n    template <typename U>\n\
    \    static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    T compose_for_child(const T&\
    \ inherited, const Node& node) const {\n        if (!node.has_lazy) return inherited;\n\
    \        return Monoid::op(inherited, node.val);\n    }\n\n    int build(int l,\
    \ int r, const std::vector<T>& v) const {\n        if (l == r) return 0;\n   \
    \     if (r - l == 1) return new_node(Node(v[l]));\n        int m = (l + r) >>\
    \ 1;\n        return new_node(Node(build(l, m, v), build(m, r, v)));\n    }\n\n\
    \    int build(int l, int r, std::vector<T>& v) const {\n        if (l == r) return\
    \ 0;\n        if (r - l == 1) return new_node(Node(std::move(v[l])));\n      \
    \  int m = (l + r) >> 1;\n        return new_node(Node(build(l, m, v), build(m,\
    \ r, v)));\n    }\n\n    template <typename U>\n    int build_from_values(int\
    \ l, int r, const std::vector<U>& v) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(make_value(v[l], l)));\n       \
    \ int m = (l + r) >> 1;\n        return new_node(Node(build_from_values(l, m,\
    \ v), build_from_values(m, r, v)));\n    }\n\n    void all_apply_to_node(int t,\
    \ const T& x, int l, int r) const {\n        Node& node = (*_pool)[t];\n     \
    \   if (r - l == 1) {\n            node.val = Monoid::op(x, node.val);\n     \
    \   } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val) :\
    \ x;\n            node.has_lazy = true;\n        }\n    }\n\n    int all_apply_clone(int\
    \ t, const T& x, int l, int r) const {\n        int res = clone_node(t);\n   \
    \     all_apply_to_node(res, x, l, r);\n        return res;\n    }\n\n    void\
    \ push(int t, int l, int r) const {\n        Node node = (*_pool)[t];\n      \
    \  if (!node.has_lazy || r - l == 1) return;\n        int m = (l + r) >> 1;\n\
    \        int left = all_apply_clone(node.l, node.val, l, m);\n        int right\
    \ = all_apply_clone(node.r, node.val, m, r);\n        Node& target = (*_pool)[t];\n\
    \        target.l = left;\n        target.r = right;\n        target.val = Monoid::id();\n\
    \        target.has_lazy = false;\n    }\n\n    int set_node(int t, int l, int\
    \ r, int p, T value) const {\n        t = clone_node(t);\n        if (r - l ==\
    \ 1) {\n            Node& node = (*_pool)[t];\n            node.val = std::move(value);\n\
    \            node.has_lazy = false;\n            return t;\n        }\n      \
    \  push(t, l, r);\n        int m = (l + r) >> 1;\n        if (p < m) {\n     \
    \       (*_pool)[t].l = set_node((*_pool)[t].l, l, m, p, std::move(value));\n\
    \        } else {\n            (*_pool)[t].r = set_node((*_pool)[t].r, m, r, p,\
    \ std::move(value));\n        }\n        return t;\n    }\n\n    int apply_node(int\
    \ t, int l, int r, int ql, int qr, const T& x) const {\n        if (qr <= l ||\
    \ r <= ql) return t;\n        t = clone_node(t);\n        if (ql <= l && r <=\
    \ qr) {\n            all_apply_to_node(t, x, l, r);\n            return t;\n \
    \       }\n        push(t, l, r);\n        int m = (l + r) >> 1;\n        (*_pool)[t].l\
    \ = apply_node((*_pool)[t].l, l, m, ql, qr, x);\n        (*_pool)[t].r = apply_node((*_pool)[t].r,\
    \ m, r, ql, qr, x);\n        return t;\n    }\n\n    T get_node(int t, int l,\
    \ int r, int p, const T& inherited) const {\n        const Node& node = (*_pool)[t];\n\
    \        if (r - l == 1) return Monoid::op(inherited, node.val);\n        int\
    \ m = (l + r) >> 1;\n        if (p < m) return get_node(node.l, l, m, p, compose_for_child(inherited,\
    \ node));\n        return get_node(node.r, m, r, p, compose_for_child(inherited,\
    \ node));\n    }\n\n    void collect_node(int t, int l, int r, int ql, int qr,\
    \ const T& inherited, std::vector<T>& res) const {\n        if (!t || qr <= l\
    \ || r <= ql) return;\n        const Node& node = (*_pool)[t];\n        if (r\
    \ - l == 1) {\n            res.push_back(Monoid::op(inherited, node.val));\n \
    \           return;\n        }\n        int m = (l + r) >> 1;\n        T next\
    \ = compose_for_child(inherited, node);\n        collect_node(node.l, l, m, ql,\
    \ qr, next, res);\n        collect_node(node.r, m, r, ql, qr, next, res);\n  \
    \  }\n\n   public:\n    PersistentDualSegtree() : PersistentDualSegtree(0) {}\n\
    \n    explicit PersistentDualSegtree(int n)\n        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        assert(0 <= n);\n        _pool->push_back(Node());\n        if (_n\
    \ > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));\n    }\n\n    explicit\
    \ PersistentDualSegtree(const std::vector<T>& v)\n        : _n(int(v.size())),\
    \ _root(0), _pool(std::make_shared<std::vector<Node>>()) {\n        _pool->reserve(v.size()\
    \ * 2 + 1);\n        _pool->push_back(Node());\n        if (_n > 0) _root = build(0,\
    \ _n, v);\n    }\n\n    explicit PersistentDualSegtree(std::vector<T>&& v)\n \
    \       : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build(0, _n, v);\n    }\n\n    template <typename\
    \ U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U x)\
    \ { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||\n  \
    \               std::convertible_to<U, T>)\n    explicit PersistentDualSegtree(const\
    \ std::vector<U>& v)\n        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>())\
    \ {\n        _pool->reserve(v.size() * 2 + 1);\n        _pool->push_back(Node());\n\
    \        if (_n > 0) _root = build_from_values(0, _n, v);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    PersistentDualSegtree set(int p, T x) const {\n     \
    \   assert(0 <= p && p < _n);\n        return PersistentDualSegtree(_n, set_node(_root,\
    \ 0, _n, p, std::move(x)), _pool);\n    }\n\n    T get(int p) const {\n      \
    \  assert(0 <= p && p < _n);\n        return get_node(_root, 0, _n, p, Monoid::id());\n\
    \    }\n\n    T operator[](int p) const {\n        return get(p);\n    }\n\n \
    \   PersistentDualSegtree apply(int p, const T& x) const {\n        assert(0 <=\
    \ p && p < _n);\n        return apply(p, p + 1, x);\n    }\n\n    PersistentDualSegtree\
    \ apply(int l, int r, const T& x) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        if (l == r) return *this;\n        return PersistentDualSegtree(_n,\
    \ apply_node(_root, 0, _n, l, r, x), _pool);\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T> to_vector(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        collect_node(_root, 0, _n, l, r,\
    \ Monoid::id(), res);\n        return res;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_DUAL_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/persistent_dual_segtree.hpp
  requiredBy: []
  timestamp: '2026-06-17 20:59:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/persistent_dual_segtree.test.cpp
documentation_of: data_structure/persistent_dual_segtree.hpp
layout: document
title: Persistent Dual Segment Tree
---

## Overview

A persistent dual segment tree for any monoid satisfying
`m1une::monoid::IsMonoid`. Range updates and point assignments return new
versions while older versions remain available.

Use it when you need versioned range updates and point queries. If you also need
range products on each version, use `PersistentLazySegtree`.

`apply(l, r, x)` updates each point value `v` in `[l, r)` to
`Monoid::op(x, v)`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDualSegtree(int n)` | Initializes `n` elements with the monoid identity. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<T>& v)` | Builds the tree from monoid values. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<U>& v)` | Builds from another value type when `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)` is available. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `PersistentDualSegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int p, T x)` | Returns a new version where `x` is applied to index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int l, int r, T x)` | Returns a new version where `x` is applied to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r-l)$ |

## Example

```cpp
#include "data_structure/persistent_dual_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::data_structure::PersistentDualSegtree<Add>;

    Seg seg(std::vector<long long>{1, 2, 3, 4});
    Seg next = seg.apply(1, 3, 10);

    std::cout << seg.get(2) << "\n";   // 3
    std::cout << next.get(2) << "\n";  // 13
}
```
