---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/data_structure/persistent_ordered_multiset.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line\
    \ 1 \"data_structure/persistent_ordered_multiset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <deque>\n#include <functional>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace data_structure {\n\ntemplate <typename T, typename\
    \ Compare = std::less<T>>\nstruct PersistentOrderedMultiset {\n   private:\n \
    \   struct Node {\n        T key;\n        int priority;\n        int count;\n\
    \        int size;\n        int distinct_size;\n        int l, r;\n\n        Node(T\
    \ value, int node_priority, int multiplicity, int subtree_count, int unique_count,\
    \ int left,\n             int right)\n            : key(std::move(value)),\n \
    \             priority(node_priority),\n              count(multiplicity),\n \
    \             size(subtree_count),\n              distinct_size(unique_count),\n\
    \              l(left),\n              r(right) {}\n    };\n\n    int root;\n\
    \    std::uint32_t rng_state;\n    Compare comp;\n    std::shared_ptr<std::deque<Node>>\
    \ pool;\n\n    int subtree_size(int t) const {\n        return t == -1 ? 0 : (*pool)[t].size;\n\
    \    }\n\n    int subtree_distinct_size(int t) const {\n        return t == -1\
    \ ? 0 : (*pool)[t].distinct_size;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    bool equal(const T& a, const T& b) const {\n        return !comp(a, b) &&\
    \ !comp(b, a);\n    }\n\n    int make_node(T key, int priority, int count, int\
    \ l, int r) const {\n        int size = count + subtree_size(l) + subtree_size(r);\n\
    \        int distinct_size = 1 + subtree_distinct_size(l) + subtree_distinct_size(r);\n\
    \        pool->emplace_back(std::move(key), priority, count, size, distinct_size,\
    \ l, r);\n        return int(pool->size()) - 1;\n    }\n\n    int merge(int l,\
    \ int r) const {\n        if (l == -1 || r == -1) return l == -1 ? r : l;\n  \
    \      if ((*pool)[l].priority > (*pool)[r].priority) {\n            Node node\
    \ = (*pool)[l];\n            int right = merge(node.r, r);\n            return\
    \ make_node(std::move(node.key), node.priority, node.count, node.l, right);\n\
    \        }\n        Node node = (*pool)[r];\n        int left = merge(l, node.l);\n\
    \        return make_node(std::move(node.key), node.priority, node.count, left,\
    \ node.r);\n    }\n\n    int rotate_right(int t) const {\n        Node node =\
    \ (*pool)[t];\n        Node child = (*pool)[node.l];\n        int new_t = make_node(std::move(node.key),\
    \ node.priority, node.count, child.r, node.r);\n        return make_node(std::move(child.key),\
    \ child.priority, child.count, child.l, new_t);\n    }\n\n    int rotate_left(int\
    \ t) const {\n        Node node = (*pool)[t];\n        Node child = (*pool)[node.r];\n\
    \        int new_t = make_node(std::move(node.key), node.priority, node.count,\
    \ node.l, child.l);\n        return make_node(std::move(child.key), child.priority,\
    \ child.count, new_t, child.r);\n    }\n\n    int insert_impl(int t, T& key, int\
    \ multiplicity, int priority) const {\n        if (t == -1) return make_node(std::move(key),\
    \ priority, multiplicity, -1, -1);\n        Node node = (*pool)[t];\n        if\
    \ (equal(key, node.key)) {\n            return make_node(std::move(node.key),\
    \ node.priority, node.count + multiplicity, node.l, node.r);\n        }\n    \
    \    if (comp(key, node.key)) {\n            int l = insert_impl(node.l, key,\
    \ multiplicity, priority);\n            int res = make_node(std::move(node.key),\
    \ node.priority, node.count, l, node.r);\n            return (*pool)[l].priority\
    \ > (*pool)[res].priority ? rotate_right(res) : res;\n        }\n        int r\
    \ = insert_impl(node.r, key, multiplicity, priority);\n        int res = make_node(std::move(node.key),\
    \ node.priority, node.count, node.l, r);\n        return (*pool)[r].priority >\
    \ (*pool)[res].priority ? rotate_left(res) : res;\n    }\n\n    int erase_one_impl(int\
    \ t, const T& key, bool& erased) const {\n        if (t == -1) return -1;\n  \
    \      Node node = (*pool)[t];\n        if (equal(key, node.key)) {\n        \
    \    erased = true;\n            if (node.count > 1) {\n                return\
    \ make_node(std::move(node.key), node.priority, node.count - 1, node.l, node.r);\n\
    \            }\n            return merge(node.l, node.r);\n        }\n       \
    \ if (comp(key, node.key)) {\n            int l = erase_one_impl(node.l, key,\
    \ erased);\n            return erased ? make_node(std::move(node.key), node.priority,\
    \ node.count, l, node.r) : t;\n        }\n        int r = erase_one_impl(node.r,\
    \ key, erased);\n        return erased ? make_node(std::move(node.key), node.priority,\
    \ node.count, node.l, r) : t;\n    }\n\n    int erase_all_impl(int t, const T&\
    \ key, int& erased) const {\n        if (t == -1) return -1;\n        Node node\
    \ = (*pool)[t];\n        if (equal(key, node.key)) {\n            erased = node.count;\n\
    \            return merge(node.l, node.r);\n        }\n        if (comp(key, node.key))\
    \ {\n            int l = erase_all_impl(node.l, key, erased);\n            return\
    \ erased ? make_node(std::move(node.key), node.priority, node.count, l, node.r)\
    \ : t;\n        }\n        int r = erase_all_impl(node.r, key, erased);\n    \
    \    return erased ? make_node(std::move(node.key), node.priority, node.count,\
    \ node.l, r) : t;\n    }\n\n    const T* kth_impl(int t, int k) const {\n    \
    \    while (t != -1) {\n            const Node& node = (*pool)[t];\n         \
    \   int left_size = subtree_size(node.l);\n            if (k < left_size) {\n\
    \                t = node.l;\n            } else if (k < left_size + node.count)\
    \ {\n                return &node.key;\n            } else {\n               \
    \ k -= left_size + node.count;\n                t = node.r;\n            }\n \
    \       }\n        return nullptr;\n    }\n\n    int count_impl(int t, const T&\
    \ key) const {\n        while (t != -1) {\n            const Node& node = (*pool)[t];\n\
    \            if (equal(key, node.key)) return node.count;\n            t = comp(key,\
    \ node.key) ? node.l : node.r;\n        }\n        return 0;\n    }\n\n    int\
    \ order_of_key_impl(int t, const T& key) const {\n        int res = 0;\n     \
    \   while (t != -1) {\n            const Node& node = (*pool)[t];\n          \
    \  if (comp(node.key, key)) {\n                res += subtree_size(node.l) + node.count;\n\
    \                t = node.r;\n            } else {\n                t = node.l;\n\
    \            }\n        }\n        return res;\n    }\n\n    int order_of_key_upper_impl(int\
    \ t, const T& key) const {\n        int res = 0;\n        while (t != -1) {\n\
    \            const Node& node = (*pool)[t];\n            if (!comp(key, node.key))\
    \ {\n                res += subtree_size(node.l) + node.count;\n             \
    \   t = node.r;\n            } else {\n                t = node.l;\n         \
    \   }\n        }\n        return res;\n    }\n\n    const T* lower_bound_impl(int\
    \ t, const T& key) const {\n        const T* res = nullptr;\n        while (t\
    \ != -1) {\n            const Node& node = (*pool)[t];\n            if (!comp(node.key,\
    \ key)) {\n                res = &node.key;\n                t = node.l;\n   \
    \         } else {\n                t = node.r;\n            }\n        }\n  \
    \      return res;\n    }\n\n    const T* upper_bound_impl(int t, const T& key)\
    \ const {\n        const T* res = nullptr;\n        while (t != -1) {\n      \
    \      const Node& node = (*pool)[t];\n            if (comp(key, node.key)) {\n\
    \                res = &node.key;\n                t = node.l;\n            }\
    \ else {\n                t = node.r;\n            }\n        }\n        return\
    \ res;\n    }\n\n    const T* max_less_impl(int t, const T& key, bool strict)\
    \ const {\n        const T* res = nullptr;\n        while (t != -1) {\n      \
    \      const Node& node = (*pool)[t];\n            bool ok = strict ? comp(node.key,\
    \ key) : !comp(key, node.key);\n            if (ok) {\n                res = &node.key;\n\
    \                t = node.r;\n            } else {\n                t = node.l;\n\
    \            }\n        }\n        return res;\n    }\n\n    void dump_impl(int\
    \ t, std::vector<T>& res) const {\n        if (t == -1) return;\n        const\
    \ Node& node = (*pool)[t];\n        dump_impl(node.l, res);\n        for (int\
    \ i = 0; i < node.count; i++) res.push_back(node.key);\n        dump_impl(node.r,\
    \ res);\n    }\n\n    PersistentOrderedMultiset(int node, std::uint32_t state,\
    \ Compare compare,\n                              std::shared_ptr<std::deque<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), comp(std::move(compare)),\
    \ pool(std::move(node_pool)) {}\n\n   public:\n    explicit PersistentOrderedMultiset(Compare\
    \ compare)\n        : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          comp(std::move(compare)),\n          pool(std::make_shared<std::deque<Node>>())\
    \ {\n        if (rng_state == 0) rng_state = 1;\n    }\n\n    PersistentOrderedMultiset()\
    \ : PersistentOrderedMultiset(Compare()) {}\n\n    PersistentOrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        for (const T& x : init) *this = insert(x);\n    }\n\n    template\
    \ <typename Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator\
    \ last, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) {\n            *this = insert(*first);\n  \
    \          ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ subtree_size(root);\n    }\n\n    int unique_size() const {\n        return\
    \ subtree_distinct_size(root);\n    }\n\n    bool empty() const {\n        return\
    \ size() == 0;\n    }\n\n    PersistentOrderedMultiset clear() const {\n     \
    \   return PersistentOrderedMultiset(-1, rng_state, comp, pool);\n    }\n\n  \
    \  PersistentOrderedMultiset insert(T key, int multiplicity = 1) const {\n   \
    \     assert(multiplicity > 0);\n        std::uint32_t next = next_state(rng_state);\n\
    \        return PersistentOrderedMultiset(insert_impl(root, key, multiplicity,\
    \ int(next)), next, comp, pool);\n    }\n\n    PersistentOrderedMultiset erase_one(const\
    \ T& key) const {\n        bool erased = false;\n        int next_root = erase_one_impl(root,\
    \ key, erased);\n        return erased ? PersistentOrderedMultiset(next_root,\
    \ rng_state, comp, pool) : *this;\n    }\n\n    PersistentOrderedMultiset erase(const\
    \ T& key) const {\n        return erase_one(key);\n    }\n\n    PersistentOrderedMultiset\
    \ erase_all(const T& key) const {\n        int erased = 0;\n        int next_root\
    \ = erase_all_impl(root, key, erased);\n        return erased ? PersistentOrderedMultiset(next_root,\
    \ rng_state, comp, pool) : *this;\n    }\n\n    bool contains(const T& key) const\
    \ {\n        return count(key) > 0;\n    }\n\n    int count(const T& key) const\
    \ {\n        return count_impl(root, key);\n    }\n\n    const T* find_by_order(int\
    \ k) const {\n        assert(0 <= k && k < size());\n        return kth_impl(root,\
    \ k);\n    }\n\n    T kth(int k) const {\n        assert(0 <= k && k < size());\n\
    \        return *kth_impl(root, k);\n    }\n\n    int order_of_key(const T& key)\
    \ const {\n        return order_of_key_impl(root, key);\n    }\n\n    int count_less(const\
    \ T& key) const {\n        return order_of_key(key);\n    }\n\n    int count_less_equal(const\
    \ T& key) const {\n        return order_of_key_upper_impl(root, key);\n    }\n\
    \n    int count_greater(const T& key) const {\n        return size() - count_less_equal(key);\n\
    \    }\n\n    int count_greater_equal(const T& key) const {\n        return size()\
    \ - count_less(key);\n    }\n\n    const T* lower_bound(const T& key) const {\n\
    \        return lower_bound_impl(root, key);\n    }\n\n    const T* upper_bound(const\
    \ T& key) const {\n        return upper_bound_impl(root, key);\n    }\n\n    const\
    \ T* min_ge(const T& key) const {\n        return lower_bound(key);\n    }\n\n\
    \    const T* min_gt(const T& key) const {\n        return upper_bound(key);\n\
    \    }\n\n    const T* max_le(const T& key) const {\n        return max_less_impl(root,\
    \ key, false);\n    }\n\n    const T* max_lt(const T& key) const {\n        return\
    \ max_less_impl(root, key, true);\n    }\n\n    const T* min() const {\n     \
    \   return empty() ? nullptr : kth_impl(root, 0);\n    }\n\n    const T* max()\
    \ const {\n        return empty() ? nullptr : kth_impl(root, size() - 1);\n  \
    \  }\n\n    std::vector<T> to_vector() const {\n        std::vector<T> res;\n\
    \        res.reserve(size());\n        dump_impl(root, res);\n        return res;\n\
    \    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/data_structure/persistent_ordered_multiset.test.cpp\"\n\n#include\
    \ <algorithm>\n#include <iostream>\n#line 8 \"verify/data_structure/persistent_ordered_multiset.test.cpp\"\
    \n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n\n    int N, Q;\n    std::cin >> N >> Q;\n\n\
    \    std::vector<int> a(N);\n    std::vector<int> xs;\n    xs.reserve(N);\n  \
    \  for (int i = 0; i < N; i++) {\n        std::cin >> a[i];\n        xs.push_back(a[i]);\n\
    \    }\n\n    std::sort(xs.begin(), xs.end());\n    xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n    auto rank = [&](int value) { return int(std::lower_bound(xs.begin(),\
    \ xs.end(), value) - xs.begin()); };\n\n    std::vector<m1une::data_structure::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        std::cin >> l >> r >> k;\n\n        int ok = int(xs.size()) -\
    \ 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        std::cout << xs[ok] << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"data_structure/persistent_ordered_multiset.hpp\"\n\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    std::vector<int> a(N);\n    std::vector<int> xs;\n\
    \    xs.reserve(N);\n    for (int i = 0; i < N; i++) {\n        std::cin >> a[i];\n\
    \        xs.push_back(a[i]);\n    }\n\n    std::sort(xs.begin(), xs.end());\n\
    \    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\n    auto rank =\
    \ [&](int value) { return int(std::lower_bound(xs.begin(), xs.end(), value) -\
    \ xs.begin()); };\n\n    std::vector<m1une::data_structure::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        std::cin >> l >> r >> k;\n\n        int ok = int(xs.size()) -\
    \ 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        std::cout << xs[ok] << '\\n';\n    }\n}\n"
  dependsOn:
  - data_structure/persistent_ordered_multiset.hpp
  isVerificationFile: true
  path: verify/data_structure/persistent_ordered_multiset.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/persistent_ordered_multiset.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/persistent_ordered_multiset.test.cpp
- /verify/verify/data_structure/persistent_ordered_multiset.test.cpp.html
title: verify/data_structure/persistent_ordered_multiset.test.cpp
---
