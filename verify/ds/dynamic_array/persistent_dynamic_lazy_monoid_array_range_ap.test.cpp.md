---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_ap_add_range_sum.hpp
    title: Range AP Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
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
  bundledCode: "#line 1 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
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
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 14 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct PersistentDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        F lazy;\n\
    \        int priority;\n        int count;\n        int l, r;\n        bool rev;\n\
    \        bool has_lazy;\n\n        Node(T value, T product, T reverse_product,\
    \ F lazy_value, int node_priority, int node_count, int left,\n             int\
    \ right, bool reversed, bool lazy_flag)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              lazy(std::move(lazy_value)),\n              priority(node_priority),\n\
    \              count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed),\n              has_lazy(lazy_flag) {}\n    };\n\n\
    \    struct BuildNode {\n        T val;\n        int priority;\n        int l,\
    \ r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    std::shared_ptr<std::vector<Node>> pool;\n\n    int subtree_size(int\
    \ t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int\
    \ t) const {\n        return t == -1 ? ActedMonoid::id() : (*pool)[t].prod;\n\
    \    }\n\n    T node_rprod(int t) const {\n        return t == -1 ? ActedMonoid::id()\
    \ : (*pool)[t].rprod;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    template <typename U>\n    static T\
    \ make_value(const U& value) {\n        if constexpr (requires(U x) { ActedMonoid::make(x);\
    \ }) {\n            return ActedMonoid::make(value);\n        } else {\n     \
    \       return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    static F reverse_operator(const\
    \ F& f, long long size) {\n        if constexpr (requires(F g, long long n) {\
    \ ActedMonoid::op_reverse(g, n); }) {\n            return ActedMonoid::op_reverse(f,\
    \ size);\n        } else {\n            return f;\n        }\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, long long ord) const {\n        F shifted = shift_operator(inherited,\
    \ ord);\n        const Node& node = (*pool)[t];\n        if (!node.has_lazy) return\
    \ shifted;\n        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy,\
    \ ord));\n    }\n\n    int make_raw_node(T val, T prod, T rprod, F lazy, int priority,\
    \ int count, bool rev, bool has_lazy, int l,\n                      int r) const\
    \ {\n        pool->emplace_back(std::move(val), std::move(prod), std::move(rprod),\
    \ std::move(lazy), priority, count, l,\n                           r, rev, has_lazy);\n\
    \        return int(pool->size()) - 1;\n    }\n\n    int make_node(T val, int\
    \ priority, bool rev, int l, int r) const {\n        T prod = ActedMonoid::op(ActedMonoid::op(node_prod(l),\
    \ val), node_prod(r));\n        T rprod = ActedMonoid::op(ActedMonoid::op(node_rprod(r),\
    \ val), node_rprod(l));\n        if (rev) std::swap(prod, rprod);\n        int\
    \ count = 1 + subtree_size(l) + subtree_size(r);\n        return make_raw_node(std::move(val),\
    \ std::move(prod), std::move(rprod), ActedMonoid::op_id(), priority,\n       \
    \                      count, rev, false, l, r);\n    }\n\n    int reversed_node(int\
    \ t) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        F lazy = node.has_lazy ? reverse_operator(node.lazy, node.count) : node.lazy;\n\
    \        return make_raw_node(std::move(node.val), std::move(node.rprod), std::move(node.prod),\
    \ std::move(lazy),\n                             node.priority, node.count, !node.rev,\
    \ node.has_lazy, node.l, node.r);\n    }\n\n    int all_apply(int t, const F&\
    \ f) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        int left_count = node.rev ? subtree_size(node.r) : subtree_size(node.l);\n\
    \        return make_raw_node(mapping_at(f, node.val, left_count), mapping_at(f,\
    \ node.prod, 0),\n                             mapping_at(reverse_operator(f,\
    \ node.count), node.rprod, 0),\n                             ActedMonoid::op_comp(f,\
    \ node.lazy), node.priority, node.count, node.rev, true, node.l,\n           \
    \                  node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1) return -1;\n        const Node& stored = (*pool)[t];\n        if (!stored.rev\
    \ && !stored.has_lazy) return t;\n        Node node = stored;\n        int l =\
    \ node.l;\n        int r = node.r;\n        if (node.rev) {\n            std::swap(l,\
    \ r);\n            l = reversed_node(l);\n            r = reversed_node(r);\n\
    \        }\n        if (node.has_lazy) {\n            l = all_apply(l, node.lazy);\n\
    \            r = all_apply(r, shift_operator(node.lazy, subtree_size(l) + 1));\n\
    \        }\n        return make_node(std::move(node.val), node.priority, false,\
    \ l, r);\n    }\n\n    int merge(int l, int r) const {\n        if (l == -1 ||\
    \ r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
    \ {\n            Node node = (*pool)[push(l)];\n            int right = merge(node.r,\
    \ r);\n            return make_node(std::move(node.val), node.priority, false,\
    \ node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n        int\
    \ left = merge(l, node.l);\n        return make_node(std::move(node.val), node.priority,\
    \ false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int t, int\
    \ pos) const {\n        if (t == -1) return {-1, -1};\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos <= left_count)\
    \ {\n            auto [a, b] = split_node(node.l, pos);\n            return {a,\
    \ make_node(std::move(node.val), node.priority, false, b, node.r)};\n        }\n\
    \        auto [a, b] = split_node(node.r, pos - left_count - 1);\n        return\
    \ {make_node(std::move(node.val), node.priority, false, node.l, a), b};\n    }\n\
    \n    int set_node(int t, int pos, T val) const {\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos < left_count)\
    \ {\n            int l = set_node(node.l, pos, std::move(val));\n            return\
    \ make_node(std::move(node.val), node.priority, false, l, node.r);\n        }\n\
    \        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ node.priority, false, node.l, node.r);\n        }\n        int r = set_node(node.r,\
    \ pos - left_count - 1, std::move(val));\n        return make_node(std::move(node.val),\
    \ node.priority, false, node.l, r);\n    }\n\n    T get_value(int t, int pos,\
    \ F inherited, bool reversed = false) const {\n        while (t != -1) {\n   \
    \         const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                inherited = compose_for_child(inherited,\
    \ t, 0);\n                t = l;\n                reversed = cur_reversed;\n \
    \           } else if (pos == left_count) {\n                return mapping_at(inherited,\
    \ node.val, left_count);\n            } else {\n                pos -= left_count\
    \ + 1;\n                inherited = compose_for_child(inherited, t, left_count\
    \ + 1);\n                t = r;\n                reversed = cur_reversed;\n  \
    \          }\n        }\n        return ActedMonoid::id();\n    }\n\n    T prod_dfs(int\
    \ t, int ql, int qr, int offset, const F& inherited, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return\
    \ ActedMonoid::id();\n        const Node& node = (*pool)[t];\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        if (ql <= offset && offset + node.count <= qr)\
    \ {\n            return mapping_at(inherited, reversed ? node.rprod : node.prod,\
    \ 0);\n        }\n        int l = cur_reversed ? node.r : node.l;\n        int\
    \ r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, compose_for_child(inherited, t, 0), cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res = ActedMonoid::op(res, mapping_at(inherited,\
    \ node.val, left_count));\n        return ActedMonoid::op(\n            res, prod_dfs(r,\
    \ ql, qr, node_pos + 1, compose_for_child(inherited, t, left_count + 1),\n   \
    \                       cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, const F& inherited, bool reversed = false) const {\n        if (t == -1)\
    \ return;\n        const Node& node = (*pool)[t];\n        bool cur_reversed =\
    \ reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n    \
    \    int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        dump_dfs(l, res, compose_for_child(inherited, t, 0), cur_reversed);\n\
    \        res.push_back(mapping_at(inherited, node.val, left_count));\n       \
    \ dump_dfs(r, res, compose_for_child(inherited, t, left_count + 1), cur_reversed);\n\
    \    }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, const F& inherited,\n                        bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, compose_for_child(inherited, t, 0), cur_reversed);\n        if\
    \ (ql <= node_pos && node_pos < qr) res.push_back(mapping_at(inherited, node.val,\
    \ left_count));\n        dump_range_dfs(r, ql, qr, node_pos + 1, res, compose_for_child(inherited,\
    \ t, left_count + 1),\n                       cur_reversed);\n    }\n\n    int\
    \ build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n        if (t\
    \ == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n  \
    \      int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
    \ nodes[t].priority, false, l, r);\n    }\n\n    int build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return -1;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    int build_from_vector(const std::vector<T>& v,\
    \ std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n     \
    \   nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n \
    \       std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n    \
    \    for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const\
    \ {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicLazyMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_raw_node(node.val, node.prod, node.rprod, node.lazy, node.priority,\
    \ node.count, node.rev,\n                             node.has_lazy, l, r);\n\
    \    }\n\n    explicit PersistentDynamicLazyMonoidArray(int node, std::uint32_t\
    \ state,\n                                              std::shared_ptr<std::vector<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {}\n\n   public:\n    PersistentDynamicLazyMonoidArray()\n        : root(-1),\n\
    \          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::vector<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(int\
    \ n)\n        : PersistentDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n\
    \    PersistentDynamicLazyMonoidArray(int n, const T& value) : PersistentDynamicLazyMonoidArray()\
    \ {\n        assert(0 <= n);\n        pool->reserve(n);\n        std::vector<T>\
    \ v(n, value);\n        root = build_from_vector(std::move(v), rng_state);\n \
    \   }\n\n    explicit PersistentDynamicLazyMonoidArray(const std::vector<T>& v)\n\
    \        : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(std::vector<T>&&\
    \ v) : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_vector(std::move(v), rng_state);\n    }\n\n    template\
    \ <typename U>\n        requires(!std::same_as<U, T>) &&\n                (requires(U\
    \ x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n    explicit PersistentDynamicLazyMonoidArray(const\
    \ std::vector<U>& v)\n        : PersistentDynamicLazyMonoidArray() {\n       \
    \ pool->reserve(v.size());\n        root = build_from_values(v, rng_state);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray(std::initializer_list<T> init)\n\
    \        : PersistentDynamicLazyMonoidArray(std::vector<T>(init)) {}\n\n    int\
    \ size() const {\n        return subtree_size(root);\n    }\n\n    bool empty()\
    \ const {\n        return size() == 0;\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ clear() const {\n        return PersistentDynamicLazyMonoidArray(-1, rng_state,\
    \ pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, T value)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        std::uint32_t next\
    \ = next_state(rng_state);\n        int node = make_node(std::move(value), int(next),\
    \ false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n        return\
    \ PersistentDynamicLazyMonoidArray(merge(merge(l, node), r), next, pool);\n  \
    \  }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, const std::vector<T>&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int\
    \ pos, std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n\
    \        if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int\
    \ pos, std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, const PersistentDynamicLazyMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicLazyMonoidArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const std::vector<T>& v) const {\n        return insert(size(), v);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray append(std::vector<T>&& v) const\
    \ {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const PersistentDynamicLazyMonoidArray& other) const {\n        return\
    \ insert(size(), other);\n    }\n\n    PersistentDynamicLazyMonoidArray erase(int\
    \ pos) const {\n        assert(0 <= pos && pos < size());\n        auto [a, b]\
    \ = split_node(root, pos);\n        auto [mid, c] = split_node(b, 1);\n      \
    \  (void)mid;\n        return PersistentDynamicLazyMonoidArray(merge(a, c), rng_state,\
    \ pool);\n    }\n\n    PersistentDynamicLazyMonoidArray erase(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split_node(root, l);\n        auto [mid, c] =\
    \ split_node(b, r - l);\n        (void)mid;\n        return PersistentDynamicLazyMonoidArray(merge(a,\
    \ c), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray pop_back()\
    \ const {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\
    \n    PersistentDynamicLazyMonoidArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0\
    \ <= pos && pos < size());\n        return get_value(root, pos, ActedMonoid::op_id());\n\
    \    }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\
    \n    T front() const {\n        assert(!empty());\n        return get(0);\n \
    \   }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray set(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return PersistentDynamicLazyMonoidArray(set_node(root,\
    \ pos, std::move(value)), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ reverse() const {\n        return PersistentDynamicLazyMonoidArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray rotate(int\
    \ l, int m, int r) const {\n        assert(0 <= l && l <= m && m <= r && r <=\
    \ size());\n        if (l == m || m == r) return *this;\n        auto [a, b] =\
    \ split_node(root, l);\n        auto [c, d] = split_node(b, m - l);\n        auto\
    \ [e, f] = split_node(d, r - m);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ e), merge(c, f)), rng_state, pool);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ apply(int pos, const F& f) const {\n        assert(0 <= pos && pos < size());\n\
    \        return apply(pos, pos + 1, f);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ apply(int l, int r, const F& f) const {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicLazyMonoidArray(merge(merge(a,\
    \ all_apply(mid, f)), c), rng_state, pool);\n    }\n\n    T prod(int l, int r)\
    \ const {\n        assert(0 <= l && l <= r && r <= size());\n        if (l ==\
    \ r) return ActedMonoid::id();\n        return prod_dfs(root, l, r, 0, ActedMonoid::op_id());\n\
    \    }\n\n    T all_prod() const {\n        return root == -1 ? ActedMonoid::id()\
    \ : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicLazyMonoidArray,\
    \ PersistentDynamicLazyMonoidArray> split(int pos) const {\n        assert(0 <=\
    \ pos && pos <= size());\n        auto [l, r] = split_node(root, pos);\n     \
    \   return {PersistentDynamicLazyMonoidArray(l, rng_state, pool),\n          \
    \      PersistentDynamicLazyMonoidArray(r, rng_state, pool)};\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ split_off(int pos) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     return PersistentDynamicLazyMonoidArray(split_node(root, pos).second, rng_state,\
    \ pool);\n    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T>\
    \ res;\n        res.reserve(size());\n        dump_dfs(root, res, ActedMonoid::op_id());\n\
    \        return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res,\
    \ ActedMonoid::op_id());\n        return res;\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n#include <iostream>\n#include <numeric>\n#include <random>\n#line 12 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n\n#line 1 \"acted_monoid/range_ap_add_range_sum.hpp\"\n\n\n\n#line 5 \"acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct\
    \ RangeApAddRangeSumNode {\n    T sum;\n    long long size;\n    T ord_sum;\n\
    };\n\ntemplate <typename T>\nstruct RangeApAddRangeSum {\n    using value_type\
    \ = RangeApAddRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for adding a * i + b\n\n    // Value Monoid (Sum)\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0, T(0)};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size, a.ord_sum + b.ord_sum + T(a.size) * T(b.size)};\n\
    \    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return {T(0), T(0)};\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return {f.first + g.first,\
    \ f.second + g.second};\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return mapping(f, x, 0);\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x, long long ord) {\n        return {x.sum + f.first * (x.ord_sum\
    \ + T(ord) * T(x.size)) + f.second * T(x.size), x.size, x.ord_sum};\n    }\n\n\
    \    static constexpr operator_type op_shift(const operator_type& f, long long\
    \ ord) {\n        return {f.first, f.second + f.first * T(ord)};\n    }\n\n  \
    \  static constexpr operator_type op_reverse(const operator_type& f, long long\
    \ size) {\n        return {-f.first, f.second + f.first * T(size - 1)};\n    }\n\
    \n    static constexpr value_type make(const T& val) {\n        return {val, 1,\
    \ T(0)};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    \n#line 14 \"verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp\"\
    \n\nusing AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;\nusing Node\
    \ = AM::value_type;\nusing Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;\n\
    \nstd::vector<long long> sums(const std::vector<Node>& a) {\n    std::vector<long\
    \ long> res;\n    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n\
    \    return res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int\
    \ l, int r) {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n\
    }\n\nvoid assert_all_ranges(const Array& a, const std::vector<long long>& expected)\
    \ {\n    assert(sums(a.to_vector()) == expected);\n    assert(a.all_prod().sum\
    \ == sum_range(expected, 0, int(expected.size())));\n    for (int l = 0; l <=\
    \ int(expected.size()); l++) {\n        for (int r = l; r <= int(expected.size());\
    \ r++) {\n            assert(a.prod(l, r).sum == sum_range(expected, l, r));\n\
    \        }\n    }\n}\n\nint main() {\n    {\n        Array a(std::vector<long\
    \ long>{0, 0, 0, 0});\n        Array b = a.apply(1, 4, {2, 3});\n        Array\
    \ c = b.insert(2, AM::make(100));\n        assert_all_ranges(a, {0, 0, 0, 0});\n\
    \        assert_all_ranges(b, {0, 3, 5, 7});\n        assert_all_ranges(c, {0,\
    \ 3, 100, 5, 7});\n\n        Array d = c.apply(1, 5, {10, 0});\n        assert_all_ranges(c,\
    \ {0, 3, 100, 5, 7});\n        assert_all_ranges(d, {0, 3, 110, 25, 37});\n  \
    \  }\n    {\n        Array a(std::vector<long long>{0, 0, 0, 0, 0});\n       \
    \ Array b = a.apply(0, 5, {1, 0});\n        Array c = b.insert(2, AM::make(100));\n\
    \        assert_all_ranges(b, {0, 1, 2, 3, 4});\n        assert_all_ranges(c,\
    \ {0, 1, 100, 2, 3, 4});\n    }\n    {\n        Array a(std::vector<long long>{0,\
    \ 0, 0, 0});\n        Array b = a.apply(0, 4, {1, 0}).reverse();\n        Array\
    \ c = b.insert(1, AM::make(9));\n        Array d = c.apply(1, 4, {2, 1});\n  \
    \      assert_all_ranges(b, {3, 2, 1, 0});\n        assert_all_ranges(c, {3, 9,\
    \ 2, 1, 0});\n        assert_all_ranges(d, {3, 10, 5, 6, 0});\n    }\n\n    std::mt19937\
    \ rng(4);\n    std::vector<std::pair<Array, std::vector<long long>>> versions;\n\
    \    versions.push_back({Array(), {}});\n    for (int step = 0; step < 300; step++)\
    \ {\n        int id = int(rng() % versions.size());\n        Array cur = versions[id].first;\n\
    \        std::vector<long long> expected = versions[id].second;\n        assert_all_ranges(cur,\
    \ expected);\n\n        Array next = cur;\n        std::vector<long long> next_expected\
    \ = expected;\n        int op = int(rng() % 7);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    long long value = int(rng() % 101) - 50;\n            next = cur.insert(pos,\
    \ AM::make(value));\n            next_expected.insert(next_expected.begin() +\
    \ pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            long long coef = int(rng() %\
    \ 11) - 5;\n            long long add = int(rng() % 21) - 10;\n            next\
    \ = cur.apply(l, r, {coef, add});\n            for (int i = l; i < r; i++) next_expected[i]\
    \ += coef * (i - l) + add;\n        } else if (op == 3) {\n            int l =\
    \ int(rng() % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > r) std::swap(l, r);\n            next = cur.reverse(l,\
    \ r);\n            std::reverse(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 4) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int m = int(rng() % (next_expected.size() + 1));\n     \
    \       int r = int(rng() % (next_expected.size() + 1));\n            if (l >\
    \ m) std::swap(l, m);\n            if (m > r) std::swap(m, r);\n            if\
    \ (l > m) std::swap(l, m);\n            next = cur.rotate(l, m, r);\n        \
    \    std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin()\
    \ + r);\n        } else if (op == 5) {\n            int pos = int(rng() % next_expected.size());\n\
    \            long long value = int(rng() % 101) - 50;\n            next = cur.set(pos,\
    \ AM::make(value));\n            next_expected[pos] = value;\n        } else {\n\
    \            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert_all_ranges(cur, expected);\n\
    \        assert_all_ranges(next, next_expected);\n        if (next_expected.size()\
    \ <= 80) versions.push_back({next, next_expected});\n    }\n\n    long long x,\
    \ y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <numeric>\n#include\
    \ <random>\n#include <utility>\n#include <vector>\n\n#include \"../../../acted_monoid/range_ap_add_range_sum.hpp\"\
    \n\nusing AM = m1une::acted_monoid::RangeApAddRangeSum<long long>;\nusing Node\
    \ = AM::value_type;\nusing Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;\n\
    \nstd::vector<long long> sums(const std::vector<Node>& a) {\n    std::vector<long\
    \ long> res;\n    res.reserve(a.size());\n    for (Node x : a) res.push_back(x.sum);\n\
    \    return res;\n}\n\nlong long sum_range(const std::vector<long long>& a, int\
    \ l, int r) {\n    return std::accumulate(a.begin() + l, a.begin() + r, 0LL);\n\
    }\n\nvoid assert_all_ranges(const Array& a, const std::vector<long long>& expected)\
    \ {\n    assert(sums(a.to_vector()) == expected);\n    assert(a.all_prod().sum\
    \ == sum_range(expected, 0, int(expected.size())));\n    for (int l = 0; l <=\
    \ int(expected.size()); l++) {\n        for (int r = l; r <= int(expected.size());\
    \ r++) {\n            assert(a.prod(l, r).sum == sum_range(expected, l, r));\n\
    \        }\n    }\n}\n\nint main() {\n    {\n        Array a(std::vector<long\
    \ long>{0, 0, 0, 0});\n        Array b = a.apply(1, 4, {2, 3});\n        Array\
    \ c = b.insert(2, AM::make(100));\n        assert_all_ranges(a, {0, 0, 0, 0});\n\
    \        assert_all_ranges(b, {0, 3, 5, 7});\n        assert_all_ranges(c, {0,\
    \ 3, 100, 5, 7});\n\n        Array d = c.apply(1, 5, {10, 0});\n        assert_all_ranges(c,\
    \ {0, 3, 100, 5, 7});\n        assert_all_ranges(d, {0, 3, 110, 25, 37});\n  \
    \  }\n    {\n        Array a(std::vector<long long>{0, 0, 0, 0, 0});\n       \
    \ Array b = a.apply(0, 5, {1, 0});\n        Array c = b.insert(2, AM::make(100));\n\
    \        assert_all_ranges(b, {0, 1, 2, 3, 4});\n        assert_all_ranges(c,\
    \ {0, 1, 100, 2, 3, 4});\n    }\n    {\n        Array a(std::vector<long long>{0,\
    \ 0, 0, 0});\n        Array b = a.apply(0, 4, {1, 0}).reverse();\n        Array\
    \ c = b.insert(1, AM::make(9));\n        Array d = c.apply(1, 4, {2, 1});\n  \
    \      assert_all_ranges(b, {3, 2, 1, 0});\n        assert_all_ranges(c, {3, 9,\
    \ 2, 1, 0});\n        assert_all_ranges(d, {3, 10, 5, 6, 0});\n    }\n\n    std::mt19937\
    \ rng(4);\n    std::vector<std::pair<Array, std::vector<long long>>> versions;\n\
    \    versions.push_back({Array(), {}});\n    for (int step = 0; step < 300; step++)\
    \ {\n        int id = int(rng() % versions.size());\n        Array cur = versions[id].first;\n\
    \        std::vector<long long> expected = versions[id].second;\n        assert_all_ranges(cur,\
    \ expected);\n\n        Array next = cur;\n        std::vector<long long> next_expected\
    \ = expected;\n        int op = int(rng() % 7);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    long long value = int(rng() % 101) - 50;\n            next = cur.insert(pos,\
    \ AM::make(value));\n            next_expected.insert(next_expected.begin() +\
    \ pos, value);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            long long coef = int(rng() %\
    \ 11) - 5;\n            long long add = int(rng() % 21) - 10;\n            next\
    \ = cur.apply(l, r, {coef, add});\n            for (int i = l; i < r; i++) next_expected[i]\
    \ += coef * (i - l) + add;\n        } else if (op == 3) {\n            int l =\
    \ int(rng() % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > r) std::swap(l, r);\n            next = cur.reverse(l,\
    \ r);\n            std::reverse(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 4) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int m = int(rng() % (next_expected.size() + 1));\n     \
    \       int r = int(rng() % (next_expected.size() + 1));\n            if (l >\
    \ m) std::swap(l, m);\n            if (m > r) std::swap(m, r);\n            if\
    \ (l > m) std::swap(l, m);\n            next = cur.rotate(l, m, r);\n        \
    \    std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin()\
    \ + r);\n        } else if (op == 5) {\n            int pos = int(rng() % next_expected.size());\n\
    \            long long value = int(rng() % 101) - 50;\n            next = cur.set(pos,\
    \ AM::make(value));\n            next_expected[pos] = value;\n        } else {\n\
    \            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert_all_ranges(cur, expected);\n\
    \        assert_all_ranges(next, next_expected);\n        if (next_expected.size()\
    \ <= 80) versions.push_back({next, next_expected});\n    }\n\n    long long x,\
    \ y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - acted_monoid/range_ap_add_range_sum.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
- /verify/verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp.html
title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array_range_ap.test.cpp
---
