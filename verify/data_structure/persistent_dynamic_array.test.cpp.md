---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
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
  bundledCode: "#line 1 \"verify/data_structure/persistent_dynamic_array.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"data_structure/persistent_dynamic_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <deque>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace data_structure {\n\ntemplate <typename T>\nstruct\
    \ PersistentDynamicArray {\n   private:\n    struct Node {\n        T val;\n \
    \       int priority;\n        int count;\n        int l, r;\n        bool rev;\n\
    \n        Node(T value, int node_priority, int node_count, int left, int right,\
    \ bool reversed)\n            : val(std::move(value)),\n              priority(node_priority),\n\
    \              count(node_count),\n              l(left),\n              r(right),\n\
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
    \        return res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/data_structure/persistent_dynamic_array.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/data_structure/persistent_dynamic_array.test.cpp\"\
    \n#include <iostream>\n#include <random>\n#line 11 \"verify/data_structure/persistent_dynamic_array.test.cpp\"\
    \n\nint main() {\n    using Array = m1une::data_structure::PersistentDynamicArray<int>;\n\
    \n    Array a = {1, 2, 3, 4, 5};\n    Array b = a.insert(2, 10);\n    Array c\
    \ = b.erase(4);\n    Array d = c.reverse(1, 4);\n    Array e = d.rotate(1, 3,\
    \ 5);\n    Array f = e.set(0, -1);\n    Array g = f.push_front(-2).push_back(6);\n\
    \    Array h = g.erase(2, 5);\n    Array i = h.append(Array({7, 8}));\n\n    assert(a.to_vector()\
    \ == (std::vector<int>{1, 2, 3, 4, 5}));\n    assert(b.to_vector() == (std::vector<int>{1,\
    \ 2, 10, 3, 4, 5}));\n    assert(c.to_vector() == (std::vector<int>{1, 2, 10,\
    \ 3, 5}));\n    assert(d.to_vector() == (std::vector<int>{1, 3, 10, 2, 5}));\n\
    \    assert(e.to_vector() == (std::vector<int>{1, 2, 5, 3, 10}));\n    assert(f.to_vector()\
    \ == (std::vector<int>{-1, 2, 5, 3, 10}));\n    assert(g.to_vector() == (std::vector<int>{-2,\
    \ -1, 2, 5, 3, 10, 6}));\n    assert(h.to_vector() == (std::vector<int>{-2, -1,\
    \ 10, 6}));\n    assert(i.to_vector() == (std::vector<int>{-2, -1, 10, 6, 7, 8}));\n\
    \n    assert(a.to_vector(1, 4) == (std::vector<int>{2, 3, 4}));\n    assert(i.size()\
    \ == 6);\n    assert(!i.empty());\n    assert(i.front() == -2);\n    assert(i.back()\
    \ == 8);\n    assert(i[2] == 10);\n    assert(i.get(3) == 6);\n\n    auto [left,\
    \ right] = i.split(3);\n    assert(left.to_vector() == (std::vector<int>{-2, -1,\
    \ 10}));\n    assert(right.to_vector() == (std::vector<int>{6, 7, 8}));\n    assert(i.split_off(4).to_vector()\
    \ == (std::vector<int>{7, 8}));\n    assert(left.append(right).to_vector() ==\
    \ i.to_vector());\n    assert(i.clear().empty());\n\n    Array base = {1, 2, 3};\n\
    \    const int& stable_reference = base[1];\n    Array pointer_growth = base;\n\
    \    for (int x = 0; x < 1000; x++) pointer_growth = pointer_growth.push_back(x);\n\
    \    Array j = base.append(base);\n    assert(j.to_vector() == (std::vector<int>{1,\
    \ 2, 3, 1, 2, 3}));\n    assert(j.reverse().to_vector() == (std::vector<int>{3,\
    \ 2, 1, 3, 2, 1}));\n    assert(base.to_vector() == (std::vector<int>{1, 2, 3}));\n\
    \    assert(stable_reference == 2);\n    assert(pointer_growth.size() == 1003);\n\
    \n    std::mt19937 rng(0);\n    std::vector<std::pair<Array, std::vector<int>>>\
    \ versions;\n    versions.push_back({Array(), {}});\n    for (int step = 0; step\
    \ < 300; step++) {\n        int id = int(rng() % versions.size());\n        const\
    \ Array cur = versions[id].first;\n        std::vector<int> expected = versions[id].second;\n\
    \        assert(cur.to_vector() == expected);\n\n        Array next = cur;\n \
    \       std::vector<int> next_expected = expected;\n        int op = int(rng()\
    \ % 8);\n        if (op == 0 || next_expected.empty()) {\n            int pos\
    \ = int(rng() % (next_expected.size() + 1));\n            int val = int(rng()\
    \ % 1000) - 500;\n            next = cur.insert(pos, val);\n            next_expected.insert(next_expected.begin()\
    \ + pos, val);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            int val = int(rng() % 1000) - 500;\n            next = cur.set(pos,\
    \ val);\n            next_expected[pos] = val;\n        } else if (op == 4) {\n\
    \            int l = int(rng() % (next_expected.size() + 1));\n            int\
    \ r = int(rng() % (next_expected.size() + 1));\n            if (l > r) std::swap(l,\
    \ r);\n            next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 5) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 6 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(cur.to_vector() == expected);\n\
    \        assert(next.to_vector() == next_expected);\n        if (!next_expected.empty())\
    \ {\n            int pos = int(rng() % next_expected.size());\n            assert(next[pos]\
    \ == next_expected[pos]);\n            assert(next.get(pos) == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<int>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<int>(next_expected.begin() +\
    \ split_pos, next_expected.end()));\n        assert(prefix.append(suffix).to_vector()\
    \ == next_expected);\n\n        if (next_expected.size() <= 100) {\n         \
    \   versions.push_back({next, next_expected});\n        }\n    }\n\n    long long\
    \ x, y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    data_structure/persistent_dynamic_array.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n#include\
    \ <vector>\n\nint main() {\n    using Array = m1une::data_structure::PersistentDynamicArray<int>;\n\
    \n    Array a = {1, 2, 3, 4, 5};\n    Array b = a.insert(2, 10);\n    Array c\
    \ = b.erase(4);\n    Array d = c.reverse(1, 4);\n    Array e = d.rotate(1, 3,\
    \ 5);\n    Array f = e.set(0, -1);\n    Array g = f.push_front(-2).push_back(6);\n\
    \    Array h = g.erase(2, 5);\n    Array i = h.append(Array({7, 8}));\n\n    assert(a.to_vector()\
    \ == (std::vector<int>{1, 2, 3, 4, 5}));\n    assert(b.to_vector() == (std::vector<int>{1,\
    \ 2, 10, 3, 4, 5}));\n    assert(c.to_vector() == (std::vector<int>{1, 2, 10,\
    \ 3, 5}));\n    assert(d.to_vector() == (std::vector<int>{1, 3, 10, 2, 5}));\n\
    \    assert(e.to_vector() == (std::vector<int>{1, 2, 5, 3, 10}));\n    assert(f.to_vector()\
    \ == (std::vector<int>{-1, 2, 5, 3, 10}));\n    assert(g.to_vector() == (std::vector<int>{-2,\
    \ -1, 2, 5, 3, 10, 6}));\n    assert(h.to_vector() == (std::vector<int>{-2, -1,\
    \ 10, 6}));\n    assert(i.to_vector() == (std::vector<int>{-2, -1, 10, 6, 7, 8}));\n\
    \n    assert(a.to_vector(1, 4) == (std::vector<int>{2, 3, 4}));\n    assert(i.size()\
    \ == 6);\n    assert(!i.empty());\n    assert(i.front() == -2);\n    assert(i.back()\
    \ == 8);\n    assert(i[2] == 10);\n    assert(i.get(3) == 6);\n\n    auto [left,\
    \ right] = i.split(3);\n    assert(left.to_vector() == (std::vector<int>{-2, -1,\
    \ 10}));\n    assert(right.to_vector() == (std::vector<int>{6, 7, 8}));\n    assert(i.split_off(4).to_vector()\
    \ == (std::vector<int>{7, 8}));\n    assert(left.append(right).to_vector() ==\
    \ i.to_vector());\n    assert(i.clear().empty());\n\n    Array base = {1, 2, 3};\n\
    \    const int& stable_reference = base[1];\n    Array pointer_growth = base;\n\
    \    for (int x = 0; x < 1000; x++) pointer_growth = pointer_growth.push_back(x);\n\
    \    Array j = base.append(base);\n    assert(j.to_vector() == (std::vector<int>{1,\
    \ 2, 3, 1, 2, 3}));\n    assert(j.reverse().to_vector() == (std::vector<int>{3,\
    \ 2, 1, 3, 2, 1}));\n    assert(base.to_vector() == (std::vector<int>{1, 2, 3}));\n\
    \    assert(stable_reference == 2);\n    assert(pointer_growth.size() == 1003);\n\
    \n    std::mt19937 rng(0);\n    std::vector<std::pair<Array, std::vector<int>>>\
    \ versions;\n    versions.push_back({Array(), {}});\n    for (int step = 0; step\
    \ < 300; step++) {\n        int id = int(rng() % versions.size());\n        const\
    \ Array cur = versions[id].first;\n        std::vector<int> expected = versions[id].second;\n\
    \        assert(cur.to_vector() == expected);\n\n        Array next = cur;\n \
    \       std::vector<int> next_expected = expected;\n        int op = int(rng()\
    \ % 8);\n        if (op == 0 || next_expected.empty()) {\n            int pos\
    \ = int(rng() % (next_expected.size() + 1));\n            int val = int(rng()\
    \ % 1000) - 500;\n            next = cur.insert(pos, val);\n            next_expected.insert(next_expected.begin()\
    \ + pos, val);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            int val = int(rng() % 1000) - 500;\n            next = cur.set(pos,\
    \ val);\n            next_expected[pos] = val;\n        } else if (op == 4) {\n\
    \            int l = int(rng() % (next_expected.size() + 1));\n            int\
    \ r = int(rng() % (next_expected.size() + 1));\n            if (l > r) std::swap(l,\
    \ r);\n            next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 5) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 6 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(cur.to_vector() == expected);\n\
    \        assert(next.to_vector() == next_expected);\n        if (!next_expected.empty())\
    \ {\n            int pos = int(rng() % next_expected.size());\n            assert(next[pos]\
    \ == next_expected[pos]);\n            assert(next.get(pos) == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<int>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<int>(next_expected.begin() +\
    \ split_pos, next_expected.end()));\n        assert(prefix.append(suffix).to_vector()\
    \ == next_expected);\n\n        if (next_expected.size() <= 100) {\n         \
    \   versions.push_back({next, next_expected});\n        }\n    }\n\n    long long\
    \ x, y;\n    std::cin >> x >> y;\n    std::cout << x + y << '\\n';\n}\n"
  dependsOn:
  - data_structure/persistent_dynamic_array.hpp
  isVerificationFile: true
  path: verify/data_structure/persistent_dynamic_array.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/persistent_dynamic_array.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/persistent_dynamic_array.test.cpp
- /verify/verify/data_structure/persistent_dynamic_array.test.cpp.html
title: verify/data_structure/persistent_dynamic_array.test.cpp
---
