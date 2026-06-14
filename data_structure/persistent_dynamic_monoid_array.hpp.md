---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_monoid_array.test.cpp
    title: verify/data_structure/persistent_dynamic_monoid_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/persistent_dynamic_monoid_array.hpp\"\n\n\
    \n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
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
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 14 \"data_structure/persistent_dynamic_monoid_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct PersistentDynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node;\n    using NodePtr = std::shared_ptr<const Node>;\n\
    \n    struct Node {\n        T val, prod, rprod;\n        int priority;\n    \
    \    int count;\n        bool rev;\n        NodePtr l, r;\n\n        Node(T value,\
    \ int node_priority, bool reversed, NodePtr left, NodePtr right)\n           \
    \ : val(std::move(value)),\n              prod(Monoid::op(Monoid::op(node_prod(left),\
    \ val), node_prod(right))),\n              rprod(Monoid::op(Monoid::op(node_rprod(right),\
    \ val), node_rprod(left))),\n              priority(node_priority),\n        \
    \      count(1 + subtree_size(left) + subtree_size(right)),\n              rev(reversed),\n\
    \              l(std::move(left)),\n              r(std::move(right)) {\n    \
    \        if (rev) std::swap(prod, rprod);\n        }\n    };\n\n    struct BuildNode\
    \ {\n        T val;\n        int priority;\n        int l, r;\n\n        BuildNode(T\
    \ value, int node_priority) : val(std::move(value)), priority(node_priority),\
    \ l(-1), r(-1) {}\n    };\n\n    NodePtr root;\n    std::uint32_t rng_state;\n\
    \n    static int subtree_size(const NodePtr& t) {\n        return t ? t->count\
    \ : 0;\n    }\n\n    static T node_prod(const NodePtr& t) {\n        return t\
    \ ? t->prod : Monoid::id();\n    }\n\n    static T node_rprod(const NodePtr& t)\
    \ {\n        return t ? t->rprod : Monoid::id();\n    }\n\n    static std::uint32_t\
    \ next_state(std::uint32_t state) {\n        state ^= state << 13;\n        state\
    \ ^= state >> 17;\n        state ^= state << 5;\n        return state == 0 ? 1\
    \ : state;\n    }\n\n    static int next_priority(std::uint32_t& state) {\n  \
    \      state = next_state(state);\n        return int(state);\n    }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value) {\n        if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    NodePtr make_node(T val, int priority, bool rev, NodePtr l, NodePtr r) const\
    \ {\n        return std::make_shared<Node>(std::move(val), priority, rev, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr reversed_node(const NodePtr& t) const {\n\
    \        if (!t) return nullptr;\n        return make_node(t->val, t->priority,\
    \ !t->rev, t->l, t->r);\n    }\n\n    NodePtr push(const NodePtr& t) const {\n\
    \        if (!t || !t->rev) return t;\n        return make_node(t->val, t->priority,\
    \ false, reversed_node(t->r), reversed_node(t->l));\n    }\n\n    NodePtr merge(const\
    \ NodePtr& l, const NodePtr& r) const {\n        if (!l || !r) return l ? l :\
    \ r;\n        if (l->priority > r->priority) {\n            NodePtr t = push(l);\n\
    \            return make_node(t->val, t->priority, false, t->l, merge(t->r, r));\n\
    \        }\n        NodePtr t = push(r);\n        return make_node(t->val, t->priority,\
    \ false, merge(l, t->l), t->r);\n    }\n\n    std::pair<NodePtr, NodePtr> split(const\
    \ NodePtr& t, int pos) const {\n        if (!t) return {nullptr, nullptr};\n \
    \       NodePtr u = push(t);\n        int left_count = subtree_size(u->l);\n \
    \       if (pos <= left_count) {\n            auto [a, b] = split(u->l, pos);\n\
    \            return {a, make_node(u->val, u->priority, false, b, u->r)};\n   \
    \     }\n        auto [a, b] = split(u->r, pos - left_count - 1);\n        return\
    \ {make_node(u->val, u->priority, false, u->l, a), b};\n    }\n\n    NodePtr set_node(const\
    \ NodePtr& t, int pos, T val) const {\n        NodePtr u = push(t);\n        int\
    \ left_count = subtree_size(u->l);\n        if (pos < left_count) {\n        \
    \    return make_node(u->val, u->priority, false, set_node(u->l, pos, std::move(val)),\
    \ u->r);\n        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ u->priority, false, u->l, u->r);\n        }\n        return make_node(u->val,\
    \ u->priority, false, u->l, set_node(u->r, pos - left_count - 1, std::move(val)));\n\
    \    }\n\n    const Node* find_node(NodePtr t, int pos) const {\n        bool\
    \ reversed = false;\n        while (t) {\n            bool cur_reversed = reversed\
    \ ^ t->rev;\n            NodePtr l = cur_reversed ? t->r : t->l;\n           \
    \ NodePtr r = cur_reversed ? t->l : t->r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                t = std::move(l);\n    \
    \            reversed = cur_reversed;\n            } else if (pos == left_count)\
    \ {\n                return t.get();\n            } else {\n                pos\
    \ -= left_count + 1;\n                t = std::move(r);\n                reversed\
    \ = cur_reversed;\n            }\n        }\n        return nullptr;\n    }\n\n\
    \    T prod_dfs(const NodePtr& t, int ql, int qr, int offset, bool reversed =\
    \ false) const {\n        if (!t || qr <= offset || offset + t->count <= ql) return\
    \ Monoid::id();\n        if (ql <= offset && offset + t->count <= qr) {\n    \
    \        return reversed ? t->rprod : t->prod;\n        }\n        bool cur_reversed\
    \ = reversed ^ t->rev;\n        const NodePtr& l = cur_reversed ? t->r : t->l;\n\
    \        const NodePtr& r = cur_reversed ? t->l : t->r;\n        int left_count\
    \ = subtree_size(l);\n        int node_pos = offset + left_count;\n        T res\
    \ = prod_dfs(l, ql, qr, offset, cur_reversed);\n        if (ql <= node_pos &&\
    \ node_pos < qr) res = Monoid::op(res, t->val);\n        return Monoid::op(res,\
    \ prod_dfs(r, ql, qr, node_pos + 1, cur_reversed));\n    }\n\n    void dump_dfs(const\
    \ NodePtr& t, std::vector<T>& res, bool reversed = false) const {\n        if\
    \ (!t) return;\n        bool cur_reversed = reversed ^ t->rev;\n        const\
    \ NodePtr& l = cur_reversed ? t->r : t->l;\n        const NodePtr& r = cur_reversed\
    \ ? t->l : t->r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(t->val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(const\
    \ NodePtr& t, int ql, int qr, int offset, std::vector<T>& res,\n             \
    \           bool reversed = false) const {\n        if (!t || qr <= offset ||\
    \ offset + t->count <= ql) return;\n        bool cur_reversed = reversed ^ t->rev;\n\
    \        const NodePtr& l = cur_reversed ? t->r : t->l;\n        const NodePtr&\
    \ r = cur_reversed ? t->l : t->r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(t->val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    NodePtr build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n\
    \        if (t == -1) return nullptr;\n        NodePtr l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        NodePtr r = build_from_nodes(nodes, nodes[t].r);\n   \
    \     return make_node(std::move(nodes[t].val), nodes[t].priority, false, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return nullptr;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    NodePtr build_from_vector(const std::vector<T>&\
    \ v, std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n  \
    \      nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  NodePtr build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n\
    \        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n   \
    \     for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    NodePtr build_from_values(const std::vector<U>& v, std::uint32_t& state)\
    \ const {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    explicit PersistentDynamicMonoidArray(NodePtr\
    \ node, std::uint32_t state)\n        : root(std::move(node)), rng_state(state)\
    \ {}\n\n   public:\n    PersistentDynamicMonoidArray()\n        : root(nullptr),\
    \ rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        if (rng_state == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicMonoidArray(int\
    \ n) : PersistentDynamicMonoidArray(n, Monoid::id()) {}\n\n    PersistentDynamicMonoidArray(int\
    \ n, const T& value) : PersistentDynamicMonoidArray() {\n        assert(0 <= n);\n\
    \        std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    explicit PersistentDynamicMonoidArray(const std::vector<T>&\
    \ v) : PersistentDynamicMonoidArray() {\n        root = build_from_vector(v, rng_state);\n\
    \    }\n\n    explicit PersistentDynamicMonoidArray(std::vector<T>&& v) : PersistentDynamicMonoidArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n    }\n\n   \
    \ template <typename U>\n        requires(!std::same_as<U, T>) && (requires(U\
    \ x) { Monoid::make(x); } || std::convertible_to<U, T>)\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<U>& v) : PersistentDynamicMonoidArray() {\n        root = build_from_values(v,\
    \ rng_state);\n    }\n\n    PersistentDynamicMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}\n\n \
    \   int size() const {\n        return subtree_size(root);\n    }\n\n    bool\
    \ empty() const {\n        return size() == 0;\n    }\n\n    PersistentDynamicMonoidArray\
    \ clear() const {\n        return PersistentDynamicMonoidArray(nullptr, rng_state);\n\
    \    }\n\n    PersistentDynamicMonoidArray insert(int pos, T value) const {\n\
    \        assert(0 <= pos && pos <= size());\n        std::uint32_t next = next_state(rng_state);\n\
    \        NodePtr node = make_node(std::move(value), int(next), false, nullptr,\
    \ nullptr);\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ node), r), next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos,\
    \ const std::vector<T>& v) const {\n        assert(0 <= pos && pos <= size());\n\
    \        if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        NodePtr mid = build_from_vector(v, next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicMonoidArray(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::vector<T>&&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        NodePtr mid\
    \ = build_from_vector(std::move(v), next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicMonoidArray(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ other.root), r), rng_state);\n    }\n\n    PersistentDynamicMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ std::vector<T>& v) const {\n        return insert(size(), v);\n    }\n\n   \
    \ PersistentDynamicMonoidArray append(std::vector<T>&& v) const {\n        return\
    \ insert(size(), std::move(v));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ PersistentDynamicMonoidArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicMonoidArray erase(int pos) const {\n\
    \        assert(0 <= pos && pos < size());\n        auto [a, b] = split(root,\
    \ pos);\n        auto [mid, c] = split(b, 1);\n        (void)mid;\n        return\
    \ PersistentDynamicMonoidArray(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split(root, l);\n  \
    \      auto [mid, c] = split(b, r - l);\n        (void)mid;\n        return PersistentDynamicMonoidArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray pop_back() const\
    \ {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\n \
    \   PersistentDynamicMonoidArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0\
    \ <= pos && pos < size());\n        return find_node(root, pos)->val;\n    }\n\
    \n    T operator[](int pos) const {\n        return get(pos);\n    }\n\n    T\
    \ front() const {\n        assert(!empty());\n        return get(0);\n    }\n\n\
    \    T back() const {\n        assert(!empty());\n        return get(size() -\
    \ 1);\n    }\n\n    PersistentDynamicMonoidArray set(int pos, T value) const {\n\
    \        assert(0 <= pos && pos < size());\n        return PersistentDynamicMonoidArray(set_node(root,\
    \ pos, std::move(value)), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split(root, l);\n  \
    \      auto [mid, c] = split(b, r - l);\n        return PersistentDynamicMonoidArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse() const {\n        return PersistentDynamicMonoidArray(reversed_node(root),\
    \ rng_state);\n    }\n\n    PersistentDynamicMonoidArray rotate(int l, int m,\
    \ int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split(root,\
    \ l);\n        auto [c, d] = split(b, m - l);\n        auto [e, f] = split(d,\
    \ r - m);\n        return PersistentDynamicMonoidArray(merge(merge(a, e), merge(c,\
    \ f)), rng_state);\n    }\n\n    T prod(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return Monoid::id();\n\
    \        return prod_dfs(root, l, r, 0);\n    }\n\n    T all_prod() const {\n\
    \        return root ? root->prod : Monoid::id();\n    }\n\n    std::pair<PersistentDynamicMonoidArray,\
    \ PersistentDynamicMonoidArray> split(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        auto [l, r] = split(root, pos);\n        return\
    \ {PersistentDynamicMonoidArray(l, rng_state), PersistentDynamicMonoidArray(r,\
    \ rng_state)};\n    }\n\n    PersistentDynamicMonoidArray split_off(int pos) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        return PersistentDynamicMonoidArray(split(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \n#include \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct PersistentDynamicMonoidArray\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node;\n\
    \    using NodePtr = std::shared_ptr<const Node>;\n\n    struct Node {\n     \
    \   T val, prod, rprod;\n        int priority;\n        int count;\n        bool\
    \ rev;\n        NodePtr l, r;\n\n        Node(T value, int node_priority, bool\
    \ reversed, NodePtr left, NodePtr right)\n            : val(std::move(value)),\n\
    \              prod(Monoid::op(Monoid::op(node_prod(left), val), node_prod(right))),\n\
    \              rprod(Monoid::op(Monoid::op(node_rprod(right), val), node_rprod(left))),\n\
    \              priority(node_priority),\n              count(1 + subtree_size(left)\
    \ + subtree_size(right)),\n              rev(reversed),\n              l(std::move(left)),\n\
    \              r(std::move(right)) {\n            if (rev) std::swap(prod, rprod);\n\
    \        }\n    };\n\n    struct BuildNode {\n        T val;\n        int priority;\n\
    \        int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    NodePtr root;\n    std::uint32_t\
    \ rng_state;\n\n    static int subtree_size(const NodePtr& t) {\n        return\
    \ t ? t->count : 0;\n    }\n\n    static T node_prod(const NodePtr& t) {\n   \
    \     return t ? t->prod : Monoid::id();\n    }\n\n    static T node_rprod(const\
    \ NodePtr& t) {\n        return t ? t->rprod : Monoid::id();\n    }\n\n    static\
    \ std::uint32_t next_state(std::uint32_t state) {\n        state ^= state << 13;\n\
    \        state ^= state >> 17;\n        state ^= state << 5;\n        return state\
    \ == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t& state)\
    \ {\n        state = next_state(state);\n        return int(state);\n    }\n\n\
    \    template <typename U>\n    static T make_value(const U& value) {\n      \
    \  if constexpr (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    NodePtr make_node(T val, int priority, bool rev, NodePtr l, NodePtr r) const\
    \ {\n        return std::make_shared<Node>(std::move(val), priority, rev, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr reversed_node(const NodePtr& t) const {\n\
    \        if (!t) return nullptr;\n        return make_node(t->val, t->priority,\
    \ !t->rev, t->l, t->r);\n    }\n\n    NodePtr push(const NodePtr& t) const {\n\
    \        if (!t || !t->rev) return t;\n        return make_node(t->val, t->priority,\
    \ false, reversed_node(t->r), reversed_node(t->l));\n    }\n\n    NodePtr merge(const\
    \ NodePtr& l, const NodePtr& r) const {\n        if (!l || !r) return l ? l :\
    \ r;\n        if (l->priority > r->priority) {\n            NodePtr t = push(l);\n\
    \            return make_node(t->val, t->priority, false, t->l, merge(t->r, r));\n\
    \        }\n        NodePtr t = push(r);\n        return make_node(t->val, t->priority,\
    \ false, merge(l, t->l), t->r);\n    }\n\n    std::pair<NodePtr, NodePtr> split(const\
    \ NodePtr& t, int pos) const {\n        if (!t) return {nullptr, nullptr};\n \
    \       NodePtr u = push(t);\n        int left_count = subtree_size(u->l);\n \
    \       if (pos <= left_count) {\n            auto [a, b] = split(u->l, pos);\n\
    \            return {a, make_node(u->val, u->priority, false, b, u->r)};\n   \
    \     }\n        auto [a, b] = split(u->r, pos - left_count - 1);\n        return\
    \ {make_node(u->val, u->priority, false, u->l, a), b};\n    }\n\n    NodePtr set_node(const\
    \ NodePtr& t, int pos, T val) const {\n        NodePtr u = push(t);\n        int\
    \ left_count = subtree_size(u->l);\n        if (pos < left_count) {\n        \
    \    return make_node(u->val, u->priority, false, set_node(u->l, pos, std::move(val)),\
    \ u->r);\n        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ u->priority, false, u->l, u->r);\n        }\n        return make_node(u->val,\
    \ u->priority, false, u->l, set_node(u->r, pos - left_count - 1, std::move(val)));\n\
    \    }\n\n    const Node* find_node(NodePtr t, int pos) const {\n        bool\
    \ reversed = false;\n        while (t) {\n            bool cur_reversed = reversed\
    \ ^ t->rev;\n            NodePtr l = cur_reversed ? t->r : t->l;\n           \
    \ NodePtr r = cur_reversed ? t->l : t->r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                t = std::move(l);\n    \
    \            reversed = cur_reversed;\n            } else if (pos == left_count)\
    \ {\n                return t.get();\n            } else {\n                pos\
    \ -= left_count + 1;\n                t = std::move(r);\n                reversed\
    \ = cur_reversed;\n            }\n        }\n        return nullptr;\n    }\n\n\
    \    T prod_dfs(const NodePtr& t, int ql, int qr, int offset, bool reversed =\
    \ false) const {\n        if (!t || qr <= offset || offset + t->count <= ql) return\
    \ Monoid::id();\n        if (ql <= offset && offset + t->count <= qr) {\n    \
    \        return reversed ? t->rprod : t->prod;\n        }\n        bool cur_reversed\
    \ = reversed ^ t->rev;\n        const NodePtr& l = cur_reversed ? t->r : t->l;\n\
    \        const NodePtr& r = cur_reversed ? t->l : t->r;\n        int left_count\
    \ = subtree_size(l);\n        int node_pos = offset + left_count;\n        T res\
    \ = prod_dfs(l, ql, qr, offset, cur_reversed);\n        if (ql <= node_pos &&\
    \ node_pos < qr) res = Monoid::op(res, t->val);\n        return Monoid::op(res,\
    \ prod_dfs(r, ql, qr, node_pos + 1, cur_reversed));\n    }\n\n    void dump_dfs(const\
    \ NodePtr& t, std::vector<T>& res, bool reversed = false) const {\n        if\
    \ (!t) return;\n        bool cur_reversed = reversed ^ t->rev;\n        const\
    \ NodePtr& l = cur_reversed ? t->r : t->l;\n        const NodePtr& r = cur_reversed\
    \ ? t->l : t->r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(t->val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(const\
    \ NodePtr& t, int ql, int qr, int offset, std::vector<T>& res,\n             \
    \           bool reversed = false) const {\n        if (!t || qr <= offset ||\
    \ offset + t->count <= ql) return;\n        bool cur_reversed = reversed ^ t->rev;\n\
    \        const NodePtr& l = cur_reversed ? t->r : t->l;\n        const NodePtr&\
    \ r = cur_reversed ? t->l : t->r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(t->val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    NodePtr build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n\
    \        if (t == -1) return nullptr;\n        NodePtr l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        NodePtr r = build_from_nodes(nodes, nodes[t].r);\n   \
    \     return make_node(std::move(nodes[t].val), nodes[t].priority, false, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return nullptr;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    NodePtr build_from_vector(const std::vector<T>&\
    \ v, std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n  \
    \      nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  NodePtr build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n\
    \        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n   \
    \     for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    NodePtr build_from_values(const std::vector<U>& v, std::uint32_t& state)\
    \ const {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    explicit PersistentDynamicMonoidArray(NodePtr\
    \ node, std::uint32_t state)\n        : root(std::move(node)), rng_state(state)\
    \ {}\n\n   public:\n    PersistentDynamicMonoidArray()\n        : root(nullptr),\
    \ rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        if (rng_state == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicMonoidArray(int\
    \ n) : PersistentDynamicMonoidArray(n, Monoid::id()) {}\n\n    PersistentDynamicMonoidArray(int\
    \ n, const T& value) : PersistentDynamicMonoidArray() {\n        assert(0 <= n);\n\
    \        std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    explicit PersistentDynamicMonoidArray(const std::vector<T>&\
    \ v) : PersistentDynamicMonoidArray() {\n        root = build_from_vector(v, rng_state);\n\
    \    }\n\n    explicit PersistentDynamicMonoidArray(std::vector<T>&& v) : PersistentDynamicMonoidArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n    }\n\n   \
    \ template <typename U>\n        requires(!std::same_as<U, T>) && (requires(U\
    \ x) { Monoid::make(x); } || std::convertible_to<U, T>)\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<U>& v) : PersistentDynamicMonoidArray() {\n        root = build_from_values(v,\
    \ rng_state);\n    }\n\n    PersistentDynamicMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}\n\n \
    \   int size() const {\n        return subtree_size(root);\n    }\n\n    bool\
    \ empty() const {\n        return size() == 0;\n    }\n\n    PersistentDynamicMonoidArray\
    \ clear() const {\n        return PersistentDynamicMonoidArray(nullptr, rng_state);\n\
    \    }\n\n    PersistentDynamicMonoidArray insert(int pos, T value) const {\n\
    \        assert(0 <= pos && pos <= size());\n        std::uint32_t next = next_state(rng_state);\n\
    \        NodePtr node = make_node(std::move(value), int(next), false, nullptr,\
    \ nullptr);\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ node), r), next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos,\
    \ const std::vector<T>& v) const {\n        assert(0 <= pos && pos <= size());\n\
    \        if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        NodePtr mid = build_from_vector(v, next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicMonoidArray(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::vector<T>&&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        NodePtr mid\
    \ = build_from_vector(std::move(v), next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicMonoidArray(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicMonoidArray(merge(merge(l,\
    \ other.root), r), rng_state);\n    }\n\n    PersistentDynamicMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ std::vector<T>& v) const {\n        return insert(size(), v);\n    }\n\n   \
    \ PersistentDynamicMonoidArray append(std::vector<T>&& v) const {\n        return\
    \ insert(size(), std::move(v));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ PersistentDynamicMonoidArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicMonoidArray erase(int pos) const {\n\
    \        assert(0 <= pos && pos < size());\n        auto [a, b] = split(root,\
    \ pos);\n        auto [mid, c] = split(b, 1);\n        (void)mid;\n        return\
    \ PersistentDynamicMonoidArray(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split(root, l);\n  \
    \      auto [mid, c] = split(b, r - l);\n        (void)mid;\n        return PersistentDynamicMonoidArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray pop_back() const\
    \ {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\n \
    \   PersistentDynamicMonoidArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0\
    \ <= pos && pos < size());\n        return find_node(root, pos)->val;\n    }\n\
    \n    T operator[](int pos) const {\n        return get(pos);\n    }\n\n    T\
    \ front() const {\n        assert(!empty());\n        return get(0);\n    }\n\n\
    \    T back() const {\n        assert(!empty());\n        return get(size() -\
    \ 1);\n    }\n\n    PersistentDynamicMonoidArray set(int pos, T value) const {\n\
    \        assert(0 <= pos && pos < size());\n        return PersistentDynamicMonoidArray(set_node(root,\
    \ pos, std::move(value)), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split(root, l);\n  \
    \      auto [mid, c] = split(b, r - l);\n        return PersistentDynamicMonoidArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse() const {\n        return PersistentDynamicMonoidArray(reversed_node(root),\
    \ rng_state);\n    }\n\n    PersistentDynamicMonoidArray rotate(int l, int m,\
    \ int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split(root,\
    \ l);\n        auto [c, d] = split(b, m - l);\n        auto [e, f] = split(d,\
    \ r - m);\n        return PersistentDynamicMonoidArray(merge(merge(a, e), merge(c,\
    \ f)), rng_state);\n    }\n\n    T prod(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return Monoid::id();\n\
    \        return prod_dfs(root, l, r, 0);\n    }\n\n    T all_prod() const {\n\
    \        return root ? root->prod : Monoid::id();\n    }\n\n    std::pair<PersistentDynamicMonoidArray,\
    \ PersistentDynamicMonoidArray> split(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        auto [l, r] = split(root, pos);\n        return\
    \ {PersistentDynamicMonoidArray(l, rng_state), PersistentDynamicMonoidArray(r,\
    \ rng_state)};\n    }\n\n    PersistentDynamicMonoidArray split_off(int pos) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        return PersistentDynamicMonoidArray(split(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/persistent_dynamic_monoid_array.hpp
  requiredBy: []
  timestamp: '2026-06-15 02:04:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/persistent_dynamic_monoid_array.test.cpp
documentation_of: data_structure/persistent_dynamic_monoid_array.hpp
layout: document
title: Persistent Dynamic Monoid Array
---

## Overview

`PersistentDynamicMonoidArray` is a path-copying implicit treap for dynamic sequences with range product queries. Updates return a new sequence and leave older versions available.

Each node stores both forward and reversed products, so range reversal works for non-commutative monoids.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`.

## Main Operations

| Operation | Description | Complexity |
| --- | --- | --- |
| `insert`, `push_back`, `push_front`, `append` | Return a version with values inserted. | Expected $O(\log N)$ for one value; expected $O(M + \log N)$ for a vector |
| `erase`, `pop_back`, `pop_front` | Return a version with values removed. | Expected $O(\log N)$ |
| `set` | Returns a version with one value replaced. | Expected $O(\log N)$ |
| `reverse`, `rotate` | Return versions with sequence order changed. | Expected $O(\log N)$; whole-sequence `reverse()` is $O(1)$ |
| `prod`, `all_prod` | Return monoid products over a range or the whole sequence. | Expected $O(\log N)$ for `prod`; $O(1)$ for `all_prod` |
| `split`, `split_off` | Return persistent split versions. | Expected $O(\log N)$ |
| `to_vector` | Dumps a range or the whole sequence. | $O(K + \log N)$ for a range; $O(N)$ for all values |

## Notes

Order-aware monoids should store relative order information such as `size` and `ord`, not immutable global indices. For example, `monoid::ArgMin` returns `ord` relative to the queried range, so it remains valid after insertions, deletions, and reversals.

## Example

```cpp
#include "data_structure/persistent_dynamic_monoid_array.hpp"
#include "monoid/add.hpp"

using Monoid = m1une::monoid::Add<long long>;
using Array = m1une::data_structure::PersistentDynamicMonoidArray<Monoid>;

int main() {
    Array a = {1, 2, 3, 4, 5};
    auto b = a.reverse(1, 5);
    auto c = b.set(2, 10);

    // a is still {1, 2, 3, 4, 5}
    // c is {1, 5, 10, 3, 2}
    long long sum = c.prod(0, 4);
}
```
