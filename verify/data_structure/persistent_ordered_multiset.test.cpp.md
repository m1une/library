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
    #include <chrono>\n#include <cstdint>\n#include <functional>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <typename T, typename Compare = std::less<T>>\n\
    struct PersistentOrderedMultiset {\n   private:\n    struct Node;\n    using NodePtr\
    \ = std::shared_ptr<const Node>;\n\n    struct Node {\n        T key;\n      \
    \  int priority;\n        int count;\n        int size;\n        int distinct_size;\n\
    \        NodePtr l, r;\n\n        Node(T value, int node_priority, int multiplicity,\
    \ NodePtr left, NodePtr right)\n            : key(std::move(value)),\n       \
    \       priority(node_priority),\n              count(multiplicity),\n       \
    \       size(multiplicity + subtree_size(left) + subtree_size(right)),\n     \
    \         distinct_size(1 + subtree_distinct_size(left) + subtree_distinct_size(right)),\n\
    \              l(std::move(left)),\n              r(std::move(right)) {}\n   \
    \ };\n\n    NodePtr root;\n    std::uint32_t rng_state;\n    Compare comp;\n\n\
    \    static int subtree_size(const NodePtr& t) {\n        return t ? t->size :\
    \ 0;\n    }\n\n    static int subtree_distinct_size(const NodePtr& t) {\n    \
    \    return t ? t->distinct_size : 0;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    bool equal(const T& a, const T& b) const {\n        return !comp(a, b) &&\
    \ !comp(b, a);\n    }\n\n    NodePtr make_node(T key, int priority, int count,\
    \ NodePtr l, NodePtr r) const {\n        return std::make_shared<Node>(std::move(key),\
    \ priority, count, std::move(l), std::move(r));\n    }\n\n    NodePtr merge(const\
    \ NodePtr& l, const NodePtr& r) const {\n        if (!l || !r) return l ? l :\
    \ r;\n        if (l->priority > r->priority) {\n            return make_node(l->key,\
    \ l->priority, l->count, l->l, merge(l->r, r));\n        }\n        return make_node(r->key,\
    \ r->priority, r->count, merge(l, r->l), r->r);\n    }\n\n    NodePtr rotate_right(const\
    \ NodePtr& t) const {\n        NodePtr s = t->l;\n        NodePtr new_t = make_node(t->key,\
    \ t->priority, t->count, s->r, t->r);\n        return make_node(s->key, s->priority,\
    \ s->count, s->l, new_t);\n    }\n\n    NodePtr rotate_left(const NodePtr& t)\
    \ const {\n        NodePtr s = t->r;\n        NodePtr new_t = make_node(t->key,\
    \ t->priority, t->count, t->l, s->l);\n        return make_node(s->key, s->priority,\
    \ s->count, new_t, s->r);\n    }\n\n    NodePtr insert_impl(const NodePtr& t,\
    \ T& key, int multiplicity, int priority) const {\n        if (!t) return make_node(std::move(key),\
    \ priority, multiplicity, nullptr, nullptr);\n        if (equal(key, t->key))\
    \ {\n            return make_node(t->key, t->priority, t->count + multiplicity,\
    \ t->l, t->r);\n        }\n        if (comp(key, t->key)) {\n            NodePtr\
    \ l = insert_impl(t->l, key, multiplicity, priority);\n            NodePtr res\
    \ = make_node(t->key, t->priority, t->count, l, t->r);\n            return l->priority\
    \ > res->priority ? rotate_right(res) : res;\n        }\n        NodePtr r = insert_impl(t->r,\
    \ key, multiplicity, priority);\n        NodePtr res = make_node(t->key, t->priority,\
    \ t->count, t->l, r);\n        return r->priority > res->priority ? rotate_left(res)\
    \ : res;\n    }\n\n    NodePtr erase_one_impl(const NodePtr& t, const T& key,\
    \ bool& erased) const {\n        if (!t) return nullptr;\n        if (equal(key,\
    \ t->key)) {\n            erased = true;\n            if (t->count > 1) return\
    \ make_node(t->key, t->priority, t->count - 1, t->l, t->r);\n            return\
    \ merge(t->l, t->r);\n        }\n        if (comp(key, t->key)) {\n          \
    \  NodePtr l = erase_one_impl(t->l, key, erased);\n            return erased ?\
    \ make_node(t->key, t->priority, t->count, l, t->r) : t;\n        }\n        NodePtr\
    \ r = erase_one_impl(t->r, key, erased);\n        return erased ? make_node(t->key,\
    \ t->priority, t->count, t->l, r) : t;\n    }\n\n    NodePtr erase_all_impl(const\
    \ NodePtr& t, const T& key, int& erased) const {\n        if (!t) return nullptr;\n\
    \        if (equal(key, t->key)) {\n            erased = t->count;\n         \
    \   return merge(t->l, t->r);\n        }\n        if (comp(key, t->key)) {\n \
    \           NodePtr l = erase_all_impl(t->l, key, erased);\n            return\
    \ erased ? make_node(t->key, t->priority, t->count, l, t->r) : t;\n        }\n\
    \        NodePtr r = erase_all_impl(t->r, key, erased);\n        return erased\
    \ ? make_node(t->key, t->priority, t->count, t->l, r) : t;\n    }\n\n    const\
    \ T* kth_impl(NodePtr t, int k) const {\n        while (t) {\n            int\
    \ left_size = subtree_size(t->l);\n            if (k < left_size) {\n        \
    \        t = t->l;\n            } else if (k < left_size + t->count) {\n     \
    \           return &t->key;\n            } else {\n                k -= left_size\
    \ + t->count;\n                t = t->r;\n            }\n        }\n        return\
    \ nullptr;\n    }\n\n    int count_impl(NodePtr t, const T& key) const {\n   \
    \     while (t) {\n            if (equal(key, t->key)) return t->count;\n    \
    \        t = comp(key, t->key) ? t->l : t->r;\n        }\n        return 0;\n\
    \    }\n\n    int order_of_key_impl(NodePtr t, const T& key) const {\n       \
    \ int res = 0;\n        while (t) {\n            if (comp(t->key, key)) {\n  \
    \              res += subtree_size(t->l) + t->count;\n                t = t->r;\n\
    \            } else {\n                t = t->l;\n            }\n        }\n \
    \       return res;\n    }\n\n    int order_of_key_upper_impl(NodePtr t, const\
    \ T& key) const {\n        int res = 0;\n        while (t) {\n            if (!comp(key,\
    \ t->key)) {\n                res += subtree_size(t->l) + t->count;\n        \
    \        t = t->r;\n            } else {\n                t = t->l;\n        \
    \    }\n        }\n        return res;\n    }\n\n    const T* lower_bound_impl(NodePtr\
    \ t, const T& key) const {\n        const T* res = nullptr;\n        while (t)\
    \ {\n            if (!comp(t->key, key)) {\n                res = &t->key;\n \
    \               t = t->l;\n            } else {\n                t = t->r;\n \
    \           }\n        }\n        return res;\n    }\n\n    const T* upper_bound_impl(NodePtr\
    \ t, const T& key) const {\n        const T* res = nullptr;\n        while (t)\
    \ {\n            if (comp(key, t->key)) {\n                res = &t->key;\n  \
    \              t = t->l;\n            } else {\n                t = t->r;\n  \
    \          }\n        }\n        return res;\n    }\n\n    const T* max_less_impl(NodePtr\
    \ t, const T& key, bool strict) const {\n        const T* res = nullptr;\n   \
    \     while (t) {\n            bool ok = strict ? comp(t->key, key) : !comp(key,\
    \ t->key);\n            if (ok) {\n                res = &t->key;\n          \
    \      t = t->r;\n            } else {\n                t = t->l;\n          \
    \  }\n        }\n        return res;\n    }\n\n    void dump_impl(const NodePtr&\
    \ t, std::vector<T>& res) const {\n        if (!t) return;\n        dump_impl(t->l,\
    \ res);\n        for (int i = 0; i < t->count; i++) {\n            res.push_back(t->key);\n\
    \        }\n        dump_impl(t->r, res);\n    }\n\n    PersistentOrderedMultiset(NodePtr\
    \ node, std::uint32_t state, Compare compare)\n        : root(std::move(node)),\
    \ rng_state(state), comp(std::move(compare)) {}\n\n   public:\n    explicit PersistentOrderedMultiset(Compare\
    \ compare)\n        : root(nullptr),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          comp(std::move(compare)) {\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    PersistentOrderedMultiset() : PersistentOrderedMultiset(Compare())\
    \ {}\n\n    PersistentOrderedMultiset(std::initializer_list<T> init, Compare compare\
    \ = Compare())\n        : PersistentOrderedMultiset(std::move(compare)) {\n  \
    \      for (const T& x : init) *this = insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator last, Compare\
    \ compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) {\n            *this = insert(*first);\n  \
    \          ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ subtree_size(root);\n    }\n\n    int unique_size() const {\n        return\
    \ subtree_distinct_size(root);\n    }\n\n    bool empty() const {\n        return\
    \ size() == 0;\n    }\n\n    PersistentOrderedMultiset clear() const {\n     \
    \   return PersistentOrderedMultiset(nullptr, rng_state, comp);\n    }\n\n   \
    \ PersistentOrderedMultiset insert(T key, int multiplicity = 1) const {\n    \
    \    assert(multiplicity > 0);\n        std::uint32_t next = next_state(rng_state);\n\
    \        return PersistentOrderedMultiset(insert_impl(root, key, multiplicity,\
    \ int(next)), next, comp);\n    }\n\n    PersistentOrderedMultiset erase_one(const\
    \ T& key) const {\n        bool erased = false;\n        NodePtr next_root = erase_one_impl(root,\
    \ key, erased);\n        return erased ? PersistentOrderedMultiset(next_root,\
    \ rng_state, comp) : *this;\n    }\n\n    PersistentOrderedMultiset erase(const\
    \ T& key) const {\n        return erase_one(key);\n    }\n\n    PersistentOrderedMultiset\
    \ erase_all(const T& key) const {\n        int erased = 0;\n        NodePtr next_root\
    \ = erase_all_impl(root, key, erased);\n        return erased ? PersistentOrderedMultiset(next_root,\
    \ rng_state, comp) : *this;\n    }\n\n    bool contains(const T& key) const {\n\
    \        return count(key) > 0;\n    }\n\n    int count(const T& key) const {\n\
    \        return count_impl(root, key);\n    }\n\n    const T* find_by_order(int\
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
  timestamp: '2026-06-14 14:10:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/persistent_ordered_multiset.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/persistent_ordered_multiset.test.cpp
- /verify/verify/data_structure/persistent_ordered_multiset.test.cpp.html
title: verify/data_structure/persistent_ordered_multiset.test.cpp
---
