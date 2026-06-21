---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
    title: Persistent Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
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
  bundledCode: "#line 1 \"verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 14 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct PersistentDynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        int priority;\n\
    \        int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ T product, T reverse_product, int node_priority, int node_count, int left, int\
    \ right,\n             bool reversed)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              priority(node_priority),\n              count(node_count),\n  \
    \            l(left),\n              r(right),\n              rev(reversed) {}\n\
    \    };\n\n    struct BuildNode {\n        T val;\n        int priority;\n   \
    \     int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    std::shared_ptr<std::vector<Node>> pool;\n\n    int subtree_size(int\
    \ t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int\
    \ t) const {\n        return t == -1 ? Monoid::id() : (*pool)[t].prod;\n    }\n\
    \n    T node_rprod(int t) const {\n        return t == -1 ? Monoid::id() : (*pool)[t].rprod;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    template <typename U>\n    static T make_value(const U& value) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else {\n            return static_cast<T>(value);\n\
    \        }\n    }\n\n    int make_node(T val, int priority, bool rev, int l, int\
    \ r) const {\n        T prod = Monoid::op(Monoid::op(node_prod(l), val), node_prod(r));\n\
    \        T rprod = Monoid::op(Monoid::op(node_rprod(r), val), node_rprod(l));\n\
    \        if (rev) std::swap(prod, rprod);\n        int count = 1 + subtree_size(l)\
    \ + subtree_size(r);\n        pool->emplace_back(std::move(val), std::move(prod),\
    \ std::move(rprod), priority, count, l, r, rev);\n        return int(pool->size())\
    \ - 1;\n    }\n\n    int reversed_node(int t) const {\n        if (t == -1) return\
    \ -1;\n        Node node = (*pool)[t];\n        return make_node(std::move(node.val),\
    \ node.priority, !node.rev, node.l, node.r);\n    }\n\n    int push(int t) const\
    \ {\n        if (t == -1 || !(*pool)[t].rev) return t;\n        Node node = (*pool)[t];\n\
    \        int l = reversed_node(node.r);\n        int r = reversed_node(node.l);\n\
    \        return make_node(std::move(node.val), node.priority, false, l, r);\n\
    \    }\n\n    int merge(int l, int r) const {\n        if (l == -1 || r == -1)\
    \ return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
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
    \ node.priority, false, node.l, r);\n    }\n\n    int find_node(int t, int pos)\
    \ const {\n        bool reversed = false;\n        while (t != -1) {\n       \
    \     const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                t = l;\n               \
    \ reversed = cur_reversed;\n            } else if (pos == left_count) {\n    \
    \            return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return -1;\n    }\n\n    T prod_dfs(int t, int\
    \ ql, int qr, int offset, bool reversed = false) const {\n        if (t == -1\
    \ || qr <= offset || offset + (*pool)[t].count <= ql) return Monoid::id();\n \
    \       const Node& node = (*pool)[t];\n        if (ql <= offset && offset + node.count\
    \ <= qr) return reversed ? node.rprod : node.prod;\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n  \
    \      int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res\
    \ = Monoid::op(res, node.val);\n        return Monoid::op(res, prod_dfs(r, ql,\
    \ qr, node_pos + 1, cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1) return;\n        const\
    \ Node& node = (*pool)[t];\n        bool cur_reversed = reversed ^ node.rev;\n\
    \        int l = cur_reversed ? node.r : node.l;\n        int r = cur_reversed\
    \ ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(node.val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(node.val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n    \
    \    if (t == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n\
    \        int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
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
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicMonoidArray(int node, std::uint32_t state,\n  \
    \                                        std::shared_ptr<std::vector<Node>> node_pool)\n\
    \        : root(node), rng_state(state), pool(std::move(node_pool)) {}\n\n   public:\n\
    \    PersistentDynamicMonoidArray()\n        : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::vector<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicMonoidArray(int\
    \ n) : PersistentDynamicMonoidArray(n, Monoid::id()) {}\n\n    PersistentDynamicMonoidArray(int\
    \ n, const T& value) : PersistentDynamicMonoidArray() {\n        assert(0 <= n);\n\
    \        pool->reserve(n);\n        std::vector<T> v(n, value);\n        root\
    \ = build_from_vector(std::move(v), rng_state);\n    }\n\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<T>& v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicMonoidArray(std::vector<T>&&\
    \ v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n  \
    \      root = build_from_vector(std::move(v), rng_state);\n    }\n\n    template\
    \ <typename U>\n        requires(!std::same_as<U, T>) && (requires(U x) { Monoid::make(x);\
    \ } || std::convertible_to<U, T>)\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<U>& v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_values(v, rng_state);\n    }\n\n    PersistentDynamicMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}\n\n \
    \   int size() const {\n        return subtree_size(root);\n    }\n\n    bool\
    \ empty() const {\n        return size() == 0;\n    }\n\n    PersistentDynamicMonoidArray\
    \ clear() const {\n        return PersistentDynamicMonoidArray(-1, rng_state,\
    \ pool);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        std::uint32_t next =\
    \ next_state(rng_state);\n        int node = make_node(std::move(value), int(next),\
    \ false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n        return\
    \ PersistentDynamicMonoidArray(merge(merge(l, node), r), next, pool);\n    }\n\
    \n    PersistentDynamicMonoidArray insert(int pos, const std::vector<T>& v) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (v.empty()) return\
    \ *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicMonoidArray insert(int\
    \ pos, std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n\
    \        if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicMonoidArray insert(int\
    \ pos, std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ std::vector<T>& v) const {\n        return insert(size(), v);\n    }\n\n   \
    \ PersistentDynamicMonoidArray append(std::vector<T>&& v) const {\n        return\
    \ insert(size(), std::move(v));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ PersistentDynamicMonoidArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicMonoidArray erase(int pos) const {\n\
    \        assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root,\
    \ pos);\n        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n     \
    \   return PersistentDynamicMonoidArray(merge(a, c), rng_state, pool);\n    }\n\
    \n    PersistentDynamicMonoidArray erase(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split_node(root, l);\n        auto [mid, c] = split_node(b, r\
    \ - l);\n        (void)mid;\n        return PersistentDynamicMonoidArray(merge(a,\
    \ c), rng_state, pool);\n    }\n\n    PersistentDynamicMonoidArray pop_back()\
    \ const {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\
    \n    PersistentDynamicMonoidArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0\
    \ <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\
    \n    T front() const {\n        assert(!empty());\n        return get(0);\n \
    \   }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    PersistentDynamicMonoidArray set(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return PersistentDynamicMonoidArray(set_node(root,\
    \ pos, std::move(value)), rng_state, pool);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicMonoidArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse() const {\n        return PersistentDynamicMonoidArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicMonoidArray rotate(int l, int\
    \ m, int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return PersistentDynamicMonoidArray(merge(merge(a, e), merge(c,\
    \ f)), rng_state, pool);\n    }\n\n    T prod(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return Monoid::id();\n\
    \        return prod_dfs(root, l, r, 0);\n    }\n\n    T all_prod() const {\n\
    \        return root == -1 ? Monoid::id() : (*pool)[root].prod;\n    }\n\n   \
    \ std::pair<PersistentDynamicMonoidArray, PersistentDynamicMonoidArray> split(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        auto [l, r]\
    \ = split_node(root, pos);\n        return {PersistentDynamicMonoidArray(l, rng_state,\
    \ pool),\n                PersistentDynamicMonoidArray(r, rng_state, pool)};\n\
    \    }\n\n    PersistentDynamicMonoidArray split_off(int pos) const {\n      \
    \  assert(0 <= pos && pos <= size());\n        return PersistentDynamicMonoidArray(split_node(root,\
    \ pos).second, rng_state, pool);\n    }\n\n    std::vector<T> to_vector() const\
    \ {\n        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp\"\
    \n#include <iostream>\n#include <numeric>\n#include <random>\n#include <string>\n\
    #line 13 \"verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp\"\n\
    \nstruct StringMonoid {\n    using value_type = std::string;\n\n    static std::string\
    \ id() {\n        return \"\";\n    }\n\n    static std::string op(const std::string&\
    \ a, const std::string& b) {\n        return a + b;\n    }\n};\n\nstd::string\
    \ join(const std::vector<std::string>& a, int l, int r) {\n    std::string res;\n\
    \    for (int i = l; i < r; i++) res += a[i];\n    return res;\n}\n\nint main()\
    \ {\n    using Array = m1une::ds::PersistentDynamicMonoidArray<StringMonoid>;\n\
    \n    Array a = {\"a\", \"b\", \"c\", \"d\", \"e\"};\n    Array b = a.insert(2,\
    \ \"X\");\n    Array c = b.reverse(1, 5);\n    Array d = c.rotate(1, 3, 6);\n\
    \    Array e = d.set(0, \"Z\");\n    Array f = e.erase(2);\n\n    assert(a.to_vector()\
    \ == (std::vector<std::string>{\"a\", \"b\", \"c\", \"d\", \"e\"}));\n    assert(b.to_vector()\
    \ == (std::vector<std::string>{\"a\", \"b\", \"X\", \"c\", \"d\", \"e\"}));\n\
    \    assert(c.to_vector() == (std::vector<std::string>{\"a\", \"d\", \"c\", \"\
    X\", \"b\", \"e\"}));\n    assert(d.to_vector() == (std::vector<std::string>{\"\
    a\", \"X\", \"b\", \"e\", \"d\", \"c\"}));\n    assert(e.to_vector() == (std::vector<std::string>{\"\
    Z\", \"X\", \"b\", \"e\", \"d\", \"c\"}));\n    assert(f.to_vector() == (std::vector<std::string>{\"\
    Z\", \"X\", \"e\", \"d\", \"c\"}));\n    assert(c.prod(0, c.size()) == \"adcXbe\"\
    );\n    assert(c.prod(1, 5) == \"dcXb\");\n    assert(f.all_prod() == \"ZXedc\"\
    );\n    assert(f.get(2) == \"e\");\n    assert(f.front() == \"Z\");\n    assert(f.back()\
    \ == \"c\");\n\n    auto [left, right] = f.split(2);\n    assert(left.to_vector()\
    \ == (std::vector<std::string>{\"Z\", \"X\"}));\n    assert(right.to_vector()\
    \ == (std::vector<std::string>{\"e\", \"d\", \"c\"}));\n    assert(left.append(right).to_vector()\
    \ == f.to_vector());\n    assert(f.split_off(3).to_vector() == (std::vector<std::string>{\"\
    d\", \"c\"}));\n    assert(f.clear().empty());\n\n    std::mt19937 rng(1);\n \
    \   std::vector<std::pair<Array, std::vector<std::string>>> versions;\n    versions.push_back({Array(),\
    \ {}});\n    for (int step = 0; step < 300; step++) {\n        int id = int(rng()\
    \ % versions.size());\n        Array cur = versions[id].first;\n        std::vector<std::string>\
    \ expected = versions[id].second;\n        assert(cur.to_vector() == expected);\n\
    \n        Array next = cur;\n        std::vector<std::string> next_expected =\
    \ expected;\n        int op = int(rng() % 8);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    std::string value(1, char('a' + int(rng() % 26)));\n            next = cur.insert(pos,\
    \ value);\n            next_expected.insert(next_expected.begin() + pos, value);\n\
    \        } else if (op == 1) {\n            int pos = int(rng() % next_expected.size());\n\
    \            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            std::string value(1, char('A' + int(rng() % 26)));\n            next\
    \ = cur.set(pos, value);\n            next_expected[pos] = value;\n        } else\
    \ if (op == 4) {\n            int l = int(rng() % (next_expected.size() + 1));\n\
    \            int r = int(rng() % (next_expected.size() + 1));\n            if\
    \ (l > r) std::swap(l, r);\n            next = cur.reverse(l, r);\n          \
    \  std::reverse(next_expected.begin() + l, next_expected.begin() + r);\n     \
    \   } else if (op == 5) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int m = int(rng() % (next_expected.size() + 1));\n     \
    \       int r = int(rng() % (next_expected.size() + 1));\n            if (l >\
    \ m) std::swap(l, m);\n            if (m > r) std::swap(m, r);\n            if\
    \ (l > m) std::swap(l, m);\n            next = cur.rotate(l, m, r);\n        \
    \    std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin()\
    \ + r);\n        } else if (op == 6 && next_expected.size() < 80) {\n        \
    \    int other_id = int(rng() % versions.size());\n            next = cur.append(versions[other_id].first);\n\
    \            next_expected.insert(next_expected.end(), versions[other_id].second.begin(),\
    \ versions[other_id].second.end());\n        } else {\n            next = cur.reverse();\n\
    \            std::reverse(next_expected.begin(), next_expected.end());\n     \
    \   }\n\n        assert(cur.to_vector() == expected);\n        assert(next.to_vector()\
    \ == next_expected);\n        assert(next.all_prod() == join(next_expected, 0,\
    \ int(next_expected.size())));\n        for (int l = 0; l <= int(next_expected.size());\
    \ l++) {\n            for (int r = l; r <= int(next_expected.size()); r++) {\n\
    \                assert(next.prod(l, r) == join(next_expected, l, r));\n     \
    \       }\n        }\n        if (!next_expected.empty()) {\n            int pos\
    \ = int(rng() % next_expected.size());\n            assert(next[pos] == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<std::string>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<std::string>(next_expected.begin()\
    \ + split_pos, next_expected.end()));\n\n        if (next_expected.size() <= 100)\
    \ versions.push_back({next, next_expected});\n    }\n\n    long long x, y;\n \
    \   std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <numeric>\n#include <random>\n\
    #include <string>\n#include <utility>\n#include <vector>\n\nstruct StringMonoid\
    \ {\n    using value_type = std::string;\n\n    static std::string id() {\n  \
    \      return \"\";\n    }\n\n    static std::string op(const std::string& a,\
    \ const std::string& b) {\n        return a + b;\n    }\n};\n\nstd::string join(const\
    \ std::vector<std::string>& a, int l, int r) {\n    std::string res;\n    for\
    \ (int i = l; i < r; i++) res += a[i];\n    return res;\n}\n\nint main() {\n \
    \   using Array = m1une::ds::PersistentDynamicMonoidArray<StringMonoid>;\n\n \
    \   Array a = {\"a\", \"b\", \"c\", \"d\", \"e\"};\n    Array b = a.insert(2,\
    \ \"X\");\n    Array c = b.reverse(1, 5);\n    Array d = c.rotate(1, 3, 6);\n\
    \    Array e = d.set(0, \"Z\");\n    Array f = e.erase(2);\n\n    assert(a.to_vector()\
    \ == (std::vector<std::string>{\"a\", \"b\", \"c\", \"d\", \"e\"}));\n    assert(b.to_vector()\
    \ == (std::vector<std::string>{\"a\", \"b\", \"X\", \"c\", \"d\", \"e\"}));\n\
    \    assert(c.to_vector() == (std::vector<std::string>{\"a\", \"d\", \"c\", \"\
    X\", \"b\", \"e\"}));\n    assert(d.to_vector() == (std::vector<std::string>{\"\
    a\", \"X\", \"b\", \"e\", \"d\", \"c\"}));\n    assert(e.to_vector() == (std::vector<std::string>{\"\
    Z\", \"X\", \"b\", \"e\", \"d\", \"c\"}));\n    assert(f.to_vector() == (std::vector<std::string>{\"\
    Z\", \"X\", \"e\", \"d\", \"c\"}));\n    assert(c.prod(0, c.size()) == \"adcXbe\"\
    );\n    assert(c.prod(1, 5) == \"dcXb\");\n    assert(f.all_prod() == \"ZXedc\"\
    );\n    assert(f.get(2) == \"e\");\n    assert(f.front() == \"Z\");\n    assert(f.back()\
    \ == \"c\");\n\n    auto [left, right] = f.split(2);\n    assert(left.to_vector()\
    \ == (std::vector<std::string>{\"Z\", \"X\"}));\n    assert(right.to_vector()\
    \ == (std::vector<std::string>{\"e\", \"d\", \"c\"}));\n    assert(left.append(right).to_vector()\
    \ == f.to_vector());\n    assert(f.split_off(3).to_vector() == (std::vector<std::string>{\"\
    d\", \"c\"}));\n    assert(f.clear().empty());\n\n    std::mt19937 rng(1);\n \
    \   std::vector<std::pair<Array, std::vector<std::string>>> versions;\n    versions.push_back({Array(),\
    \ {}});\n    for (int step = 0; step < 300; step++) {\n        int id = int(rng()\
    \ % versions.size());\n        Array cur = versions[id].first;\n        std::vector<std::string>\
    \ expected = versions[id].second;\n        assert(cur.to_vector() == expected);\n\
    \n        Array next = cur;\n        std::vector<std::string> next_expected =\
    \ expected;\n        int op = int(rng() % 8);\n        if (op == 0 || next_expected.empty())\
    \ {\n            int pos = int(rng() % (next_expected.size() + 1));\n        \
    \    std::string value(1, char('a' + int(rng() % 26)));\n            next = cur.insert(pos,\
    \ value);\n            next_expected.insert(next_expected.begin() + pos, value);\n\
    \        } else if (op == 1) {\n            int pos = int(rng() % next_expected.size());\n\
    \            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            std::string value(1, char('A' + int(rng() % 26)));\n            next\
    \ = cur.set(pos, value);\n            next_expected[pos] = value;\n        } else\
    \ if (op == 4) {\n            int l = int(rng() % (next_expected.size() + 1));\n\
    \            int r = int(rng() % (next_expected.size() + 1));\n            if\
    \ (l > r) std::swap(l, r);\n            next = cur.reverse(l, r);\n          \
    \  std::reverse(next_expected.begin() + l, next_expected.begin() + r);\n     \
    \   } else if (op == 5) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int m = int(rng() % (next_expected.size() + 1));\n     \
    \       int r = int(rng() % (next_expected.size() + 1));\n            if (l >\
    \ m) std::swap(l, m);\n            if (m > r) std::swap(m, r);\n            if\
    \ (l > m) std::swap(l, m);\n            next = cur.rotate(l, m, r);\n        \
    \    std::rotate(next_expected.begin() + l, next_expected.begin() + m, next_expected.begin()\
    \ + r);\n        } else if (op == 6 && next_expected.size() < 80) {\n        \
    \    int other_id = int(rng() % versions.size());\n            next = cur.append(versions[other_id].first);\n\
    \            next_expected.insert(next_expected.end(), versions[other_id].second.begin(),\
    \ versions[other_id].second.end());\n        } else {\n            next = cur.reverse();\n\
    \            std::reverse(next_expected.begin(), next_expected.end());\n     \
    \   }\n\n        assert(cur.to_vector() == expected);\n        assert(next.to_vector()\
    \ == next_expected);\n        assert(next.all_prod() == join(next_expected, 0,\
    \ int(next_expected.size())));\n        for (int l = 0; l <= int(next_expected.size());\
    \ l++) {\n            for (int r = l; r <= int(next_expected.size()); r++) {\n\
    \                assert(next.prod(l, r) == join(next_expected, l, r));\n     \
    \       }\n        }\n        if (!next_expected.empty()) {\n            int pos\
    \ = int(rng() % next_expected.size());\n            assert(next[pos] == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<std::string>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<std::string>(next_expected.begin()\
    \ + split_pos, next_expected.end()));\n\n        if (next_expected.size() <= 100)\
    \ versions.push_back({next, next_expected});\n    }\n\n    long long x, y;\n \
    \   std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_array/persistent_dynamic_monoid_array.hpp
  - monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
- /verify/verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp.html
title: verify/ds/dynamic_array/persistent_dynamic_monoid_array.test.cpp
---
