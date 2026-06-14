---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_dynamic_array.test.cpp
    title: verify/data_structure/persistent_dynamic_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/persistent_dynamic_array.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <chrono>\n#include <cstdint>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node;\n    using NodePtr = std::shared_ptr<const\
    \ Node>;\n\n    struct Node {\n        T val;\n        int priority;\n       \
    \ int count;\n        bool rev;\n        NodePtr l, r;\n\n        Node(T value,\
    \ int node_priority, bool reversed, NodePtr left, NodePtr right)\n           \
    \ : val(std::move(value)),\n              priority(node_priority),\n         \
    \     count(1 + subtree_size(left) + subtree_size(right)),\n              rev(reversed),\n\
    \              l(std::move(left)),\n              r(std::move(right)) {}\n   \
    \ };\n\n    struct BuildNode {\n        T val;\n        int priority;\n      \
    \  int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    NodePtr root;\n    std::uint32_t\
    \ rng_state;\n\n    static int subtree_size(const NodePtr& t) {\n        return\
    \ t ? t->count : 0;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    NodePtr make_node(T val, int priority,\
    \ bool rev, NodePtr l, NodePtr r) const {\n        return std::make_shared<Node>(std::move(val),\
    \ priority, rev, std::move(l), std::move(r));\n    }\n\n    NodePtr reversed_node(const\
    \ NodePtr& t) const {\n        if (!t) return nullptr;\n        return make_node(t->val,\
    \ t->priority, !t->rev, t->l, t->r);\n    }\n\n    NodePtr push(const NodePtr&\
    \ t) const {\n        if (!t || !t->rev) return t;\n        return make_node(t->val,\
    \ t->priority, false, reversed_node(t->r), reversed_node(t->l));\n    }\n\n  \
    \  NodePtr merge(const NodePtr& l, const NodePtr& r) const {\n        if (!l ||\
    \ !r) return l ? l : r;\n        if (l->priority > r->priority) {\n          \
    \  NodePtr t = push(l);\n            return make_node(t->val, t->priority, false,\
    \ t->l, merge(t->r, r));\n        }\n        NodePtr t = push(r);\n        return\
    \ make_node(t->val, t->priority, false, merge(l, t->l), t->r);\n    }\n\n    std::pair<NodePtr,\
    \ NodePtr> split(const NodePtr& t, int pos) const {\n        if (!t) return {nullptr,\
    \ nullptr};\n        NodePtr u = push(t);\n        int left_count = subtree_size(u->l);\n\
    \        if (pos <= left_count) {\n            auto [a, b] = split(u->l, pos);\n\
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
    \ ^ t->rev;\n            NodePtr left = cur_reversed ? t->r : t->l;\n        \
    \    NodePtr right = cur_reversed ? t->l : t->r;\n            int left_count =\
    \ subtree_size(left);\n            if (pos < left_count) {\n                t\
    \ = std::move(left);\n                reversed = cur_reversed;\n            }\
    \ else if (pos == left_count) {\n                return t.get();\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = std::move(right);\n\
    \                reversed = cur_reversed;\n            }\n        }\n        return\
    \ nullptr;\n    }\n\n    void dump_dfs(const NodePtr& t, std::vector<T>& res,\
    \ bool reversed = false) const {\n        if (!t) return;\n        bool cur_reversed\
    \ = reversed ^ t->rev;\n        const NodePtr& left = cur_reversed ? t->r : t->l;\n\
    \        const NodePtr& right = cur_reversed ? t->l : t->r;\n        dump_dfs(left,\
    \ res, cur_reversed);\n        res.push_back(t->val);\n        dump_dfs(right,\
    \ res, cur_reversed);\n    }\n\n    void dump_range_dfs(const NodePtr& t, int\
    \ ql, int qr, int offset, std::vector<T>& res,\n                        bool reversed\
    \ = false) const {\n        if (!t || qr <= offset || offset + t->count <= ql)\
    \ return;\n        bool cur_reversed = reversed ^ t->rev;\n        const NodePtr&\
    \ left = cur_reversed ? t->r : t->l;\n        const NodePtr& right = cur_reversed\
    \ ? t->l : t->r;\n        int left_count = subtree_size(left);\n        int node_pos\
    \ = offset + left_count;\n        dump_range_dfs(left, ql, qr, offset, res, cur_reversed);\n\
    \        if (ql <= node_pos && node_pos < qr) {\n            res.push_back(t->val);\n\
    \        }\n        dump_range_dfs(right, ql, qr, node_pos + 1, res, cur_reversed);\n\
    \    }\n\n    NodePtr build_from_nodes(std::vector<BuildNode>& nodes, int t) const\
    \ {\n        if (t == -1) return nullptr;\n        NodePtr l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        NodePtr r = build_from_nodes(nodes, nodes[t].r);\n   \
    \     return make_node(std::move(nodes[t].val), nodes[t].priority, false, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return nullptr;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) {\n           \
    \     nodes[stack.back()].r = i;\n            }\n            stack.push_back(i);\n\
    \        }\n        return build_from_nodes(nodes, stack.front());\n    }\n\n\
    \    NodePtr build_from_vector(const std::vector<T>& v, std::uint32_t& state)\
    \ const {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const T& x : v) {\n            nodes.emplace_back(x, next_priority(state));\n\
    \        }\n        return build_cartesian(nodes);\n    }\n\n    NodePtr build_from_vector(std::vector<T>&&\
    \ v, std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n  \
    \      nodes.reserve(v.size());\n        for (T& x : v) {\n            nodes.emplace_back(std::move(x),\
    \ next_priority(state));\n        }\n        return build_cartesian(nodes);\n\
    \    }\n\n    explicit PersistentDynamicArray(NodePtr node, std::uint32_t state)\
    \ : root(std::move(node)), rng_state(state) {}\n\n   public:\n    PersistentDynamicArray()\n\
    \        : root(nullptr), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        if (rng_state == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicArray(int\
    \ n) : PersistentDynamicArray(n, T()) {}\n\n    PersistentDynamicArray(int n,\
    \ const T& value) : PersistentDynamicArray() {\n        assert(0 <= n);\n    \
    \    std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    explicit PersistentDynamicArray(const std::vector<T>&\
    \ v) : PersistentDynamicArray() {\n        root = build_from_vector(v, rng_state);\n\
    \    }\n\n    explicit PersistentDynamicArray(std::vector<T>&& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n    }\n\n   \
    \ PersistentDynamicArray(std::initializer_list<T> init) : PersistentDynamicArray(std::vector<T>(init))\
    \ {}\n\n    int size() const {\n        return subtree_size(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    PersistentDynamicArray\
    \ clear() const {\n        return PersistentDynamicArray(nullptr, rng_state);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, T val) const {\n        assert(0\
    \ <= pos && pos <= size());\n        std::uint32_t next = next_state(rng_state);\n\
    \        NodePtr node = make_node(std::move(val), int(next), false, nullptr, nullptr);\n\
    \        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ node), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, const\
    \ std::vector<T>& v) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        NodePtr mid = build_from_vector(v, next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicArray(merge(merge(l, mid), r), next);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, std::vector<T>&& v) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (v.empty()) return\
    \ *this;\n        std::uint32_t next = rng_state;\n        NodePtr mid = build_from_vector(std::move(v),\
    \ next);\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ other.root), r), rng_state);\n    }\n\n    PersistentDynamicArray push_back(T\
    \ val) const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split(root, pos);\n\
    \        auto [mid, c] = split(b, 1);\n        (void)mid;\n        return PersistentDynamicArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicArray erase(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split(root, l);\n        auto [mid, c] = split(b,\
    \ r - l);\n        (void)mid;\n        return PersistentDynamicArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicArray pop_back() const {\n  \
    \      assert(!empty());\n        return erase(size() - 1);\n    }\n\n    PersistentDynamicArray\
    \ pop_front() const {\n        assert(!empty());\n        return erase(0);\n \
    \   }\n\n    const T& at(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        return find_node(root, pos)->val;\n    }\n\n    const T& operator[](int\
    \ pos) const {\n        return at(pos);\n    }\n\n    const T& front() const {\n\
    \        assert(!empty());\n        return at(0);\n    }\n\n    const T& back()\
    \ const {\n        assert(!empty());\n        return at(size() - 1);\n    }\n\n\
    \    T get(int pos) const {\n        return at(pos);\n    }\n\n    PersistentDynamicArray\
    \ set(int pos, T val) const {\n        assert(0 <= pos && pos < size());\n   \
    \     return PersistentDynamicArray(set_node(root, pos, std::move(val)), rng_state);\n\
    \    }\n\n    PersistentDynamicArray reverse(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split(root, l);\n        auto [mid, c] = split(b, r - l);\n  \
    \      return PersistentDynamicArray(merge(merge(a, reversed_node(mid)), c), rng_state);\n\
    \    }\n\n    PersistentDynamicArray reverse() const {\n        return PersistentDynamicArray(reversed_node(root),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray rotate(int l, int m, int r)\
    \ const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n      \
    \  if (l == m || m == r) return *this;\n        auto [a, b] = split(root, l);\n\
    \        auto [c, d] = split(b, m - l);\n        auto [e, f] = split(d, r - m);\n\
    \        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)), rng_state);\n\
    \    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        auto [l, r]\
    \ = split(root, pos);\n        return {PersistentDynamicArray(l, rng_state), PersistentDynamicArray(r,\
    \ rng_state)};\n    }\n\n    PersistentDynamicArray split_off(int pos) const {\n\
    \        assert(0 <= pos && pos <= size());\n        return PersistentDynamicArray(split(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node;\n    using NodePtr = std::shared_ptr<const\
    \ Node>;\n\n    struct Node {\n        T val;\n        int priority;\n       \
    \ int count;\n        bool rev;\n        NodePtr l, r;\n\n        Node(T value,\
    \ int node_priority, bool reversed, NodePtr left, NodePtr right)\n           \
    \ : val(std::move(value)),\n              priority(node_priority),\n         \
    \     count(1 + subtree_size(left) + subtree_size(right)),\n              rev(reversed),\n\
    \              l(std::move(left)),\n              r(std::move(right)) {}\n   \
    \ };\n\n    struct BuildNode {\n        T val;\n        int priority;\n      \
    \  int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    NodePtr root;\n    std::uint32_t\
    \ rng_state;\n\n    static int subtree_size(const NodePtr& t) {\n        return\
    \ t ? t->count : 0;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    NodePtr make_node(T val, int priority,\
    \ bool rev, NodePtr l, NodePtr r) const {\n        return std::make_shared<Node>(std::move(val),\
    \ priority, rev, std::move(l), std::move(r));\n    }\n\n    NodePtr reversed_node(const\
    \ NodePtr& t) const {\n        if (!t) return nullptr;\n        return make_node(t->val,\
    \ t->priority, !t->rev, t->l, t->r);\n    }\n\n    NodePtr push(const NodePtr&\
    \ t) const {\n        if (!t || !t->rev) return t;\n        return make_node(t->val,\
    \ t->priority, false, reversed_node(t->r), reversed_node(t->l));\n    }\n\n  \
    \  NodePtr merge(const NodePtr& l, const NodePtr& r) const {\n        if (!l ||\
    \ !r) return l ? l : r;\n        if (l->priority > r->priority) {\n          \
    \  NodePtr t = push(l);\n            return make_node(t->val, t->priority, false,\
    \ t->l, merge(t->r, r));\n        }\n        NodePtr t = push(r);\n        return\
    \ make_node(t->val, t->priority, false, merge(l, t->l), t->r);\n    }\n\n    std::pair<NodePtr,\
    \ NodePtr> split(const NodePtr& t, int pos) const {\n        if (!t) return {nullptr,\
    \ nullptr};\n        NodePtr u = push(t);\n        int left_count = subtree_size(u->l);\n\
    \        if (pos <= left_count) {\n            auto [a, b] = split(u->l, pos);\n\
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
    \ ^ t->rev;\n            NodePtr left = cur_reversed ? t->r : t->l;\n        \
    \    NodePtr right = cur_reversed ? t->l : t->r;\n            int left_count =\
    \ subtree_size(left);\n            if (pos < left_count) {\n                t\
    \ = std::move(left);\n                reversed = cur_reversed;\n            }\
    \ else if (pos == left_count) {\n                return t.get();\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = std::move(right);\n\
    \                reversed = cur_reversed;\n            }\n        }\n        return\
    \ nullptr;\n    }\n\n    void dump_dfs(const NodePtr& t, std::vector<T>& res,\
    \ bool reversed = false) const {\n        if (!t) return;\n        bool cur_reversed\
    \ = reversed ^ t->rev;\n        const NodePtr& left = cur_reversed ? t->r : t->l;\n\
    \        const NodePtr& right = cur_reversed ? t->l : t->r;\n        dump_dfs(left,\
    \ res, cur_reversed);\n        res.push_back(t->val);\n        dump_dfs(right,\
    \ res, cur_reversed);\n    }\n\n    void dump_range_dfs(const NodePtr& t, int\
    \ ql, int qr, int offset, std::vector<T>& res,\n                        bool reversed\
    \ = false) const {\n        if (!t || qr <= offset || offset + t->count <= ql)\
    \ return;\n        bool cur_reversed = reversed ^ t->rev;\n        const NodePtr&\
    \ left = cur_reversed ? t->r : t->l;\n        const NodePtr& right = cur_reversed\
    \ ? t->l : t->r;\n        int left_count = subtree_size(left);\n        int node_pos\
    \ = offset + left_count;\n        dump_range_dfs(left, ql, qr, offset, res, cur_reversed);\n\
    \        if (ql <= node_pos && node_pos < qr) {\n            res.push_back(t->val);\n\
    \        }\n        dump_range_dfs(right, ql, qr, node_pos + 1, res, cur_reversed);\n\
    \    }\n\n    NodePtr build_from_nodes(std::vector<BuildNode>& nodes, int t) const\
    \ {\n        if (t == -1) return nullptr;\n        NodePtr l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        NodePtr r = build_from_nodes(nodes, nodes[t].r);\n   \
    \     return make_node(std::move(nodes[t].val), nodes[t].priority, false, std::move(l),\
    \ std::move(r));\n    }\n\n    NodePtr build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return nullptr;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) {\n           \
    \     nodes[stack.back()].r = i;\n            }\n            stack.push_back(i);\n\
    \        }\n        return build_from_nodes(nodes, stack.front());\n    }\n\n\
    \    NodePtr build_from_vector(const std::vector<T>& v, std::uint32_t& state)\
    \ const {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const T& x : v) {\n            nodes.emplace_back(x, next_priority(state));\n\
    \        }\n        return build_cartesian(nodes);\n    }\n\n    NodePtr build_from_vector(std::vector<T>&&\
    \ v, std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n  \
    \      nodes.reserve(v.size());\n        for (T& x : v) {\n            nodes.emplace_back(std::move(x),\
    \ next_priority(state));\n        }\n        return build_cartesian(nodes);\n\
    \    }\n\n    explicit PersistentDynamicArray(NodePtr node, std::uint32_t state)\
    \ : root(std::move(node)), rng_state(state) {}\n\n   public:\n    PersistentDynamicArray()\n\
    \        : root(nullptr), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        if (rng_state == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicArray(int\
    \ n) : PersistentDynamicArray(n, T()) {}\n\n    PersistentDynamicArray(int n,\
    \ const T& value) : PersistentDynamicArray() {\n        assert(0 <= n);\n    \
    \    std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    explicit PersistentDynamicArray(const std::vector<T>&\
    \ v) : PersistentDynamicArray() {\n        root = build_from_vector(v, rng_state);\n\
    \    }\n\n    explicit PersistentDynamicArray(std::vector<T>&& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n    }\n\n   \
    \ PersistentDynamicArray(std::initializer_list<T> init) : PersistentDynamicArray(std::vector<T>(init))\
    \ {}\n\n    int size() const {\n        return subtree_size(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    PersistentDynamicArray\
    \ clear() const {\n        return PersistentDynamicArray(nullptr, rng_state);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, T val) const {\n        assert(0\
    \ <= pos && pos <= size());\n        std::uint32_t next = next_state(rng_state);\n\
    \        NodePtr node = make_node(std::move(val), int(next), false, nullptr, nullptr);\n\
    \        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ node), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, const\
    \ std::vector<T>& v) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        NodePtr mid = build_from_vector(v, next);\n        auto [l, r] = split(root,\
    \ pos);\n        return PersistentDynamicArray(merge(merge(l, mid), r), next);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, std::vector<T>&& v) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (v.empty()) return\
    \ *this;\n        std::uint32_t next = rng_state;\n        NodePtr mid = build_from_vector(std::move(v),\
    \ next);\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        auto [l, r] = split(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ other.root), r), rng_state);\n    }\n\n    PersistentDynamicArray push_back(T\
    \ val) const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split(root, pos);\n\
    \        auto [mid, c] = split(b, 1);\n        (void)mid;\n        return PersistentDynamicArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicArray erase(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split(root, l);\n        auto [mid, c] = split(b,\
    \ r - l);\n        (void)mid;\n        return PersistentDynamicArray(merge(a,\
    \ c), rng_state);\n    }\n\n    PersistentDynamicArray pop_back() const {\n  \
    \      assert(!empty());\n        return erase(size() - 1);\n    }\n\n    PersistentDynamicArray\
    \ pop_front() const {\n        assert(!empty());\n        return erase(0);\n \
    \   }\n\n    const T& at(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        return find_node(root, pos)->val;\n    }\n\n    const T& operator[](int\
    \ pos) const {\n        return at(pos);\n    }\n\n    const T& front() const {\n\
    \        assert(!empty());\n        return at(0);\n    }\n\n    const T& back()\
    \ const {\n        assert(!empty());\n        return at(size() - 1);\n    }\n\n\
    \    T get(int pos) const {\n        return at(pos);\n    }\n\n    PersistentDynamicArray\
    \ set(int pos, T val) const {\n        assert(0 <= pos && pos < size());\n   \
    \     return PersistentDynamicArray(set_node(root, pos, std::move(val)), rng_state);\n\
    \    }\n\n    PersistentDynamicArray reverse(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split(root, l);\n        auto [mid, c] = split(b, r - l);\n  \
    \      return PersistentDynamicArray(merge(merge(a, reversed_node(mid)), c), rng_state);\n\
    \    }\n\n    PersistentDynamicArray reverse() const {\n        return PersistentDynamicArray(reversed_node(root),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray rotate(int l, int m, int r)\
    \ const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n      \
    \  if (l == m || m == r) return *this;\n        auto [a, b] = split(root, l);\n\
    \        auto [c, d] = split(b, m - l);\n        auto [e, f] = split(d, r - m);\n\
    \        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)), rng_state);\n\
    \    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        auto [l, r]\
    \ = split(root, pos);\n        return {PersistentDynamicArray(l, rng_state), PersistentDynamicArray(r,\
    \ rng_state)};\n    }\n\n    PersistentDynamicArray split_off(int pos) const {\n\
    \        assert(0 <= pos && pos <= size());\n        return PersistentDynamicArray(split(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/persistent_dynamic_array.hpp
  requiredBy: []
  timestamp: '2026-06-15 01:54:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/persistent_dynamic_array.test.cpp
documentation_of: data_structure/persistent_dynamic_array.hpp
layout: document
title: Persistent Dynamic Array
---

## Overview

`PersistentDynamicArray` is a path-copying implicit treap. It acts like a persistent version of `DynamicArray`: update operations return a new array and leave the old version available.

The structure supports index-based insertion, deletion, point assignment, reversal, rotation, splitting, and concatenation. Untouched subtrees are shared between versions.

## Complexity Notation

* `N` is the current number of elements in the array.
* `M` is the number of inserted or appended elements.
* `K` is the number of elements returned by `to_vector`.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors

* `PersistentDynamicArray()`
  Constructs an empty array. ($O(1)$)

* `PersistentDynamicArray(int n)`
  Constructs an array with `n` value-initialized elements. ($O(N)$)

* `PersistentDynamicArray(int n, const T& value)`
  Constructs an array with `n` copies of `value`. ($O(N)$)

* `PersistentDynamicArray(const std::vector<T>& v)`
  Constructs an array initialized with elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::vector<T>&& v)`
  Constructs an array by moving elements from `v`. ($O(N)$)

* `PersistentDynamicArray(std::initializer_list<T> init)`
  Constructs an array initialized with an initializer list. ($O(N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `PersistentDynamicArray clear() const` | Returns an empty version. | $O(1)$ |
| `PersistentDynamicArray insert(int pos, T val) const` | Returns a version with `val` inserted before index `pos`. | $O(\log N)$ expected |
| `PersistentDynamicArray insert(int pos, const std::vector<T>& v) const` | Returns a version with all elements of `v` inserted before index `pos`. | $O(M + \log N)$ expected |
| `PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const` | Returns a version with `other` inserted before index `pos`. | $O(\log N)$ expected |
| `PersistentDynamicArray push_back(T val) const`, `push_front(T val) const` | Returns a version with one element added. | $O(\log N)$ expected |
| `PersistentDynamicArray append(...) const` | Appends a vector or another persistent dynamic array. | $O(M + \log N)$ expected for a vector; $O(\log N)$ expected for another array |
| `PersistentDynamicArray erase(int pos) const` | Returns a version with the element at `pos` removed. | $O(\log N)$ expected |
| `PersistentDynamicArray erase(int l, int r) const` | Returns a version with `[l, r)` removed. | $O(\log N)$ expected |
| `PersistentDynamicArray pop_back() const`, `pop_front() const` | Returns a version with one element removed. | $O(\log N)$ expected |
| `const T& at(int pos) const`, `operator[]` | Returns the element at `pos`. | $O(\log N)$ expected |
| `T get(int pos) const` | Returns a copy of the element at `pos`. | $O(\log N)$ expected |
| `const T& front() const`, `back() const` | Returns the first or last element. | $O(\log N)$ expected |
| `PersistentDynamicArray set(int pos, T val) const` | Returns a version where index `pos` is overwritten by `val`. | $O(\log N)$ expected |
| `PersistentDynamicArray reverse(int l, int r) const` | Returns a version with `[l, r)` reversed. | $O(\log N)$ expected |
| `PersistentDynamicArray reverse() const` | Returns a version with the whole array reversed. | $O(1)$ |
| `PersistentDynamicArray rotate(int l, int m, int r) const` | Returns a version where `[m, r)` is moved before `[l, m)`, like `std::rotate`. | $O(\log N)$ expected |
| `std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const` | Returns `{prefix, suffix}` split at `pos`. | $O(\log N)$ expected |
| `PersistentDynamicArray split_off(int pos) const` | Returns the suffix `[pos, N)` while leaving the current version unchanged. | $O(\log N)$ expected |
| `std::vector<T> to_vector() const` | Dumps the entire array. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Dumps `[l, r)`, where `K = r - l`. | $O(K + \log N)$ |

## Example

```cpp
#include "data_structure/persistent_dynamic_array.hpp"

#include <iostream>

using namespace m1une::data_structure;

int main() {
    PersistentDynamicArray<int> a = {1, 2, 3, 4, 5};
    auto b = a.insert(2, 10);      // {1, 2, 10, 3, 4, 5}
    auto c = b.reverse(1, 5);      // {1, 4, 3, 10, 2, 5}
    auto d = c.erase(2).set(0, 7); // {7, 4, 10, 2, 5}

    for (int x : a.to_vector()) std::cout << x << " ";
    std::cout << "\n";
    for (int x : d.to_vector()) std::cout << x << " ";
    std::cout << "\n";
}
```
