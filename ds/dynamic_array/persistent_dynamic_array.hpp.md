---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n\n\n\
    #include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <deque>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node {\n        T val;\n        int priority;\n \
    \       int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ int node_priority, int node_count, int left, int right, bool reversed)\n   \
    \         : val(std::move(value)),\n              priority(node_priority),\n \
    \             count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    std::shared_ptr<std::deque<Node>>\
    \ pool;\n\n    int subtree_size(int t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    int make_node(T val, int priority, bool rev, int l, int r) const\
    \ {\n        int count = 1 + subtree_size(l) + subtree_size(r);\n        pool->emplace_back(std::move(val),\
    \ priority, count, l, r, rev);\n        return int(pool->size()) - 1;\n    }\n\
    \n    int reversed_node(int t) const {\n        if (t == -1) return -1;\n    \
    \    const Node& node = (*pool)[t];\n        return make_node(node.val, node.priority,\
    \ !node.rev, node.l, node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1 || !(*pool)[t].rev) return t;\n        Node node = (*pool)[t];\n  \
    \      int l = reversed_node(node.r);\n        int r = reversed_node(node.l);\n\
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
    \         }\n        }\n        return -1;\n    }\n\n    void dump_dfs(int t,\
    \ std::vector<T>& res, bool reversed = false) const {\n        if (t == -1) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n\
    \        res.push_back(node.val);\n        dump_dfs(r, res, cur_reversed);\n \
    \   }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1 || qr <= offset ||\
    \ offset + (*pool)[t].count <= ql) return;\n        const Node& node = (*pool)[t];\n\
    \        bool cur_reversed = reversed ^ node.rev;\n        int l = cur_reversed\
    \ ? node.r : node.l;\n        int r = cur_reversed ? node.l : node.r;\n      \
    \  int left_count = subtree_size(l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(l, ql, qr, offset, res, cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res.push_back(node.val);\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int build_from_nodes(std::vector<BuildNode>&\
    \ nodes, int t) const {\n        if (t == -1) return -1;\n        int l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        int r = build_from_nodes(nodes, nodes[t].r);\n       \
    \ return make_node(std::move(nodes[t].val), nodes[t].priority, false, l, r);\n\
    \    }\n\n    int build_cartesian(std::vector<BuildNode>& nodes) const {\n   \
    \     if (nodes.empty()) return -1;\n        std::vector<int> stack;\n       \
    \ stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
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
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicArray(int node, std::uint32_t state, std::shared_ptr<std::deque<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {}\n\n   public:\n    PersistentDynamicArray()\n        : root(-1),\n      \
    \    rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::deque<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicArray(int n) :\
    \ PersistentDynamicArray(n, T()) {}\n\n    PersistentDynamicArray(int n, const\
    \ T& value) : PersistentDynamicArray() {\n        assert(0 <= n);\n        std::vector<T>\
    \ v(n, value);\n        root = build_from_vector(std::move(v), rng_state);\n \
    \   }\n\n    explicit PersistentDynamicArray(const std::vector<T>& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicArray(std::vector<T>&&\
    \ v) : PersistentDynamicArray() {\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray(std::initializer_list<T> init)\
    \ : PersistentDynamicArray(std::vector<T>(init)) {}\n\n    int size() const {\n\
    \        return subtree_size(root);\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    PersistentDynamicArray clear() const {\n\
    \        return PersistentDynamicArray(-1, rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, T val) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(val),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return PersistentDynamicArray(merge(merge(l, node), r), next, pool);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const std::vector<T>& v)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const PersistentDynamicArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicArray push_back(T\
    \ val) const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root, pos);\n\
    \        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ pop_back() const {\n        assert(!empty());\n        return erase(size() -\
    \ 1);\n    }\n\n    PersistentDynamicArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    const T& at(int pos) const {\n       \
    \ assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    const T& operator[](int pos) const {\n        return at(pos);\n\
    \    }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ at(0);\n    }\n\n    const T& back() const {\n        assert(!empty());\n  \
    \      return at(size() - 1);\n    }\n\n    T get(int pos) const {\n        return\
    \ at(pos);\n    }\n\n    PersistentDynamicArray set(int pos, T val) const {\n\
    \        assert(0 <= pos && pos < size());\n        return PersistentDynamicArray(set_node(root,\
    \ pos, std::move(val)), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse() const {\n        return PersistentDynamicArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicArray rotate(int l, int m,\
    \ int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)),\
    \ rng_state, pool);\n    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray>\
    \ split(int pos) const {\n        assert(0 <= pos && pos <= size());\n       \
    \ auto [l, r] = split_node(root, pos);\n        return {PersistentDynamicArray(l,\
    \ rng_state, pool), PersistentDynamicArray(r, rng_state, pool)};\n    }\n\n  \
    \  PersistentDynamicArray split_off(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        return PersistentDynamicArray(split_node(root, pos).second,\
    \ rng_state, pool);\n    }\n\n    std::vector<T> to_vector() const {\n       \
    \ std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root, res);\n\
    \        return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n#define M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <deque>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node {\n        T val;\n        int priority;\n \
    \       int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ int node_priority, int node_count, int left, int right, bool reversed)\n   \
    \         : val(std::move(value)),\n              priority(node_priority),\n \
    \             count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    std::shared_ptr<std::deque<Node>>\
    \ pool;\n\n    int subtree_size(int t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    int make_node(T val, int priority, bool rev, int l, int r) const\
    \ {\n        int count = 1 + subtree_size(l) + subtree_size(r);\n        pool->emplace_back(std::move(val),\
    \ priority, count, l, r, rev);\n        return int(pool->size()) - 1;\n    }\n\
    \n    int reversed_node(int t) const {\n        if (t == -1) return -1;\n    \
    \    const Node& node = (*pool)[t];\n        return make_node(node.val, node.priority,\
    \ !node.rev, node.l, node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1 || !(*pool)[t].rev) return t;\n        Node node = (*pool)[t];\n  \
    \      int l = reversed_node(node.r);\n        int r = reversed_node(node.l);\n\
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
    \         }\n        }\n        return -1;\n    }\n\n    void dump_dfs(int t,\
    \ std::vector<T>& res, bool reversed = false) const {\n        if (t == -1) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n\
    \        res.push_back(node.val);\n        dump_dfs(r, res, cur_reversed);\n \
    \   }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1 || qr <= offset ||\
    \ offset + (*pool)[t].count <= ql) return;\n        const Node& node = (*pool)[t];\n\
    \        bool cur_reversed = reversed ^ node.rev;\n        int l = cur_reversed\
    \ ? node.r : node.l;\n        int r = cur_reversed ? node.l : node.r;\n      \
    \  int left_count = subtree_size(l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(l, ql, qr, offset, res, cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res.push_back(node.val);\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int build_from_nodes(std::vector<BuildNode>&\
    \ nodes, int t) const {\n        if (t == -1) return -1;\n        int l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        int r = build_from_nodes(nodes, nodes[t].r);\n       \
    \ return make_node(std::move(nodes[t].val), nodes[t].priority, false, l, r);\n\
    \    }\n\n    int build_cartesian(std::vector<BuildNode>& nodes) const {\n   \
    \     if (nodes.empty()) return -1;\n        std::vector<int> stack;\n       \
    \ stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
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
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicArray(int node, std::uint32_t state, std::shared_ptr<std::deque<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {}\n\n   public:\n    PersistentDynamicArray()\n        : root(-1),\n      \
    \    rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::deque<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicArray(int n) :\
    \ PersistentDynamicArray(n, T()) {}\n\n    PersistentDynamicArray(int n, const\
    \ T& value) : PersistentDynamicArray() {\n        assert(0 <= n);\n        std::vector<T>\
    \ v(n, value);\n        root = build_from_vector(std::move(v), rng_state);\n \
    \   }\n\n    explicit PersistentDynamicArray(const std::vector<T>& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicArray(std::vector<T>&&\
    \ v) : PersistentDynamicArray() {\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray(std::initializer_list<T> init)\
    \ : PersistentDynamicArray(std::vector<T>(init)) {}\n\n    int size() const {\n\
    \        return subtree_size(root);\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    PersistentDynamicArray clear() const {\n\
    \        return PersistentDynamicArray(-1, rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, T val) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(val),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return PersistentDynamicArray(merge(merge(l, node), r), next, pool);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const std::vector<T>& v)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const PersistentDynamicArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicArray push_back(T\
    \ val) const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root, pos);\n\
    \        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ pop_back() const {\n        assert(!empty());\n        return erase(size() -\
    \ 1);\n    }\n\n    PersistentDynamicArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    const T& at(int pos) const {\n       \
    \ assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    const T& operator[](int pos) const {\n        return at(pos);\n\
    \    }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ at(0);\n    }\n\n    const T& back() const {\n        assert(!empty());\n  \
    \      return at(size() - 1);\n    }\n\n    T get(int pos) const {\n        return\
    \ at(pos);\n    }\n\n    PersistentDynamicArray set(int pos, T val) const {\n\
    \        assert(0 <= pos && pos < size());\n        return PersistentDynamicArray(set_node(root,\
    \ pos, std::move(val)), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse() const {\n        return PersistentDynamicArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicArray rotate(int l, int m,\
    \ int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)),\
    \ rng_state, pool);\n    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray>\
    \ split(int pos) const {\n        assert(0 <= pos && pos <= size());\n       \
    \ auto [l, r] = split_node(root, pos);\n        return {PersistentDynamicArray(l,\
    \ rng_state, pool), PersistentDynamicArray(r, rng_state, pool)};\n    }\n\n  \
    \  PersistentDynamicArray split_off(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        return PersistentDynamicArray(split_node(root, pos).second,\
    \ rng_state, pool);\n    }\n\n    std::vector<T> to_vector() const {\n       \
    \ std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root, res);\n\
    \        return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n#endif  // M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/dynamic_array/persistent_dynamic_array.hpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
documentation_of: ds/dynamic_array/persistent_dynamic_array.hpp
layout: document
title: Persistent Dynamic Array
---

## Overview

`PersistentDynamicArray` is a path-copying implicit treap. It acts like a persistent version of `DynamicArray`: update operations return a new array and leave the old version available.

Nodes are stored in a shared block-contiguous pool and refer to children by integer index. This avoids per-node allocation and reference-counted child pointers while preserving stable references returned by `at`, `front`, and `back`.
The pool is append-only and is released when the last related version is destroyed.

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
| `PersistentDynamicArray insert(int pos, T val) const` | Returns a version with `val` inserted before index `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray insert(int pos, const std::vector<T>& v) const` | Returns a version with all elements of `v` inserted before index `pos`. | Expected $O(M + \log N)$ |
| `PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const` | Returns a version with `other` inserted before index `pos`. Versions sharing a pool reuse its nodes; an independently constructed array is copied into this pool. | Expected $O(\log N)$ with a shared pool; $O(M + \log N)$ otherwise |
| `PersistentDynamicArray push_back(T val) const`, `push_front(T val) const` | Returns a version with one element added. | Expected $O(\log N)$ |
| `PersistentDynamicArray append(...) const` | Appends a vector or another persistent dynamic array. | Expected $O(M + \log N)$ for a vector or independent array; $O(\log N)$ for a version sharing the pool |
| `PersistentDynamicArray erase(int pos) const` | Returns a version with the element at `pos` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray erase(int l, int r) const` | Returns a version with `[l, r)` removed. | Expected $O(\log N)$ |
| `PersistentDynamicArray pop_back() const`, `pop_front() const` | Returns a version with one element removed. | Expected $O(\log N)$ |
| `const T& at(int pos) const`, `operator[]` | Returns the element at `pos`. | Expected $O(\log N)$ |
| `T get(int pos) const` | Returns a copy of the element at `pos`. | Expected $O(\log N)$ |
| `const T& front() const`, `back() const` | Returns the first or last element. | Expected $O(\log N)$ |
| `PersistentDynamicArray set(int pos, T val) const` | Returns a version where index `pos` is overwritten by `val`. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse(int l, int r) const` | Returns a version with `[l, r)` reversed. | Expected $O(\log N)$ |
| `PersistentDynamicArray reverse() const` | Returns a version with the whole array reversed. | $O(1)$ |
| `PersistentDynamicArray rotate(int l, int m, int r) const` | Returns a version where `[m, r)` is moved before `[l, m)`, like `std::rotate`. | Expected $O(\log N)$ |
| `std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const` | Returns `{prefix, suffix}` split at `pos`. | Expected $O(\log N)$ |
| `PersistentDynamicArray split_off(int pos) const` | Returns the suffix `[pos, N)` while leaving the current version unchanged. | Expected $O(\log N)$ |
| `std::vector<T> to_vector() const` | Dumps the entire array. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Dumps `[l, r)`, where `K = r - l`. | $O(K + \log N)$ |

## Example

```cpp
#include "ds/dynamic_array/persistent_dynamic_array.hpp"

#include <iostream>

using namespace m1une::ds;

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
