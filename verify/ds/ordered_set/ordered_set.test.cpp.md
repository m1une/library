---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/ordered_set/ordered_multiset.hpp
    title: Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/ordered_set/ordered_set.hpp
    title: Ordered Set
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"verify/ds/ordered_set/ordered_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#line 1 \"ds/ordered_set/ordered_set.hpp\"\
    \n\n\n\n#line 1 \"ds/ordered_set/ordered_multiset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <functional>\n#include <initializer_list>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <typename T, typename Compare = std::less<T>>\nstruct OrderedMultiset\
    \ {\n   private:\n    struct Node {\n        T key;\n        int priority;\n \
    \       int count;\n        int size;\n        int distinct_size;\n        int\
    \ l, r;\n\n        Node(T value, int node_priority, int multiplicity)\n      \
    \      : key(std::move(value)),\n              priority(node_priority),\n    \
    \          count(multiplicity),\n              size(multiplicity),\n         \
    \     distinct_size(1),\n              l(-1),\n              r(-1) {}\n    };\n\
    \n    std::vector<Node> pool;\n    int root;\n    std::uint32_t rng_state;\n \
    \   Compare comp;\n\n    bool equal(const T& a, const T& b) const {\n        return\
    \ !comp(a, b) && !comp(b, a);\n    }\n\n    int subtree_size(int t) const {\n\
    \        return t == -1 ? 0 : pool[t].size;\n    }\n\n    int subtree_distinct_size(int\
    \ t) const {\n        return t == -1 ? 0 : pool[t].distinct_size;\n    }\n\n \
    \   int next_priority() {\n        rng_state ^= rng_state << 13;\n        rng_state\
    \ ^= rng_state >> 17;\n        rng_state ^= rng_state << 5;\n        return int(rng_state);\n\
    \    }\n\n    int new_node(T key, int multiplicity) {\n        pool.emplace_back(std::move(key),\
    \ next_priority(), multiplicity);\n        return int(pool.size()) - 1;\n    }\n\
    \n    void update(int t) {\n        if (t == -1) return;\n        pool[t].size\
    \ = pool[t].count + subtree_size(pool[t].l) + subtree_size(pool[t].r);\n     \
    \   pool[t].distinct_size = 1 + subtree_distinct_size(pool[t].l) + subtree_distinct_size(pool[t].r);\n\
    \    }\n\n    int merge(int l, int r) {\n        if (l == -1 || r == -1) return\
    \ l == -1 ? r : l;\n        if (pool[l].priority > pool[r].priority) {\n     \
    \       pool[l].r = merge(pool[l].r, r);\n            update(l);\n           \
    \ return l;\n        }\n        pool[r].l = merge(l, pool[r].l);\n        update(r);\n\
    \        return r;\n    }\n\n    void rotate_right(int& t) {\n        int s =\
    \ pool[t].l;\n        pool[t].l = pool[s].r;\n        pool[s].r = t;\n       \
    \ update(t);\n        update(s);\n        t = s;\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int s = pool[t].r;\n        pool[t].r = pool[s].l;\n        pool[s].l\
    \ = t;\n        update(t);\n        update(s);\n        t = s;\n    }\n\n    int\
    \ insert_impl(int t, T& key, int multiplicity) {\n        if (t == -1) {\n   \
    \         return new_node(std::move(key), multiplicity);\n        }\n        if\
    \ (equal(key, pool[t].key)) {\n            pool[t].count += multiplicity;\n  \
    \          update(t);\n            return t;\n        }\n        if (comp(key,\
    \ pool[t].key)) {\n            int l = insert_impl(pool[t].l, key, multiplicity);\n\
    \            pool[t].l = l;\n            if (pool[pool[t].l].priority > pool[t].priority)\
    \ rotate_right(t);\n        } else {\n            int r = insert_impl(pool[t].r,\
    \ key, multiplicity);\n            pool[t].r = r;\n            if (pool[pool[t].r].priority\
    \ > pool[t].priority) rotate_left(t);\n        }\n        update(t);\n       \
    \ return t;\n    }\n\n    bool erase_one_impl(int& t, const T& key) {\n      \
    \  if (t == -1) return false;\n        bool erased = false;\n        if (equal(key,\
    \ pool[t].key)) {\n            erased = true;\n            if (pool[t].count >\
    \ 1) {\n                pool[t].count--;\n            } else {\n             \
    \   t = merge(pool[t].l, pool[t].r);\n                return true;\n         \
    \   }\n        } else if (comp(key, pool[t].key)) {\n            erased = erase_one_impl(pool[t].l,\
    \ key);\n        } else {\n            erased = erase_one_impl(pool[t].r, key);\n\
    \        }\n        update(t);\n        return erased;\n    }\n\n    int erase_all_impl(int&\
    \ t, const T& key) {\n        if (t == -1) return 0;\n        int erased = 0;\n\
    \        if (equal(key, pool[t].key)) {\n            erased = pool[t].count;\n\
    \            t = merge(pool[t].l, pool[t].r);\n            return erased;\n  \
    \      }\n        if (comp(key, pool[t].key)) {\n            erased = erase_all_impl(pool[t].l,\
    \ key);\n        } else {\n            erased = erase_all_impl(pool[t].r, key);\n\
    \        }\n        update(t);\n        return erased;\n    }\n\n    const T*\
    \ kth_impl(int t, int k) const {\n        while (t != -1) {\n            int left_size\
    \ = subtree_size(pool[t].l);\n            if (k < left_size) {\n             \
    \   t = pool[t].l;\n            } else if (k < left_size + pool[t].count) {\n\
    \                return &pool[t].key;\n            } else {\n                k\
    \ -= left_size + pool[t].count;\n                t = pool[t].r;\n            }\n\
    \        }\n        return nullptr;\n    }\n\n    int count_impl(int t, const\
    \ T& key) const {\n        while (t != -1) {\n            if (equal(key, pool[t].key))\
    \ return pool[t].count;\n            t = comp(key, pool[t].key) ? pool[t].l :\
    \ pool[t].r;\n        }\n        return 0;\n    }\n\n    int order_of_key_impl(int\
    \ t, const T& key) const {\n        int res = 0;\n        while (t != -1) {\n\
    \            if (comp(pool[t].key, key)) {\n                res += subtree_size(pool[t].l)\
    \ + pool[t].count;\n                t = pool[t].r;\n            } else {\n   \
    \             t = pool[t].l;\n            }\n        }\n        return res;\n\
    \    }\n\n    int order_of_key_upper_impl(int t, const T& key) const {\n     \
    \   int res = 0;\n        while (t != -1) {\n            if (!comp(key, pool[t].key))\
    \ {\n                res += subtree_size(pool[t].l) + pool[t].count;\n       \
    \         t = pool[t].r;\n            } else {\n                t = pool[t].l;\n\
    \            }\n        }\n        return res;\n    }\n\n    const T* lower_bound_impl(int\
    \ t, const T& key) const {\n        const T* res = nullptr;\n        while (t\
    \ != -1) {\n            if (!comp(pool[t].key, key)) {\n                res =\
    \ &pool[t].key;\n                t = pool[t].l;\n            } else {\n      \
    \          t = pool[t].r;\n            }\n        }\n        return res;\n   \
    \ }\n\n    const T* upper_bound_impl(int t, const T& key) const {\n        const\
    \ T* res = nullptr;\n        while (t != -1) {\n            if (comp(key, pool[t].key))\
    \ {\n                res = &pool[t].key;\n                t = pool[t].l;\n   \
    \         } else {\n                t = pool[t].r;\n            }\n        }\n\
    \        return res;\n    }\n\n    const T* max_less_impl(int t, const T& key,\
    \ bool strict) const {\n        const T* res = nullptr;\n        while (t != -1)\
    \ {\n            bool ok = strict ? comp(pool[t].key, key) : !comp(key, pool[t].key);\n\
    \            if (ok) {\n                res = &pool[t].key;\n                t\
    \ = pool[t].r;\n            } else {\n                t = pool[t].l;\n       \
    \     }\n        }\n        return res;\n    }\n\n    void dump_impl(int t, std::vector<T>&\
    \ res) const {\n        if (t == -1) return;\n        dump_impl(pool[t].l, res);\n\
    \        for (int i = 0; i < pool[t].count; i++) {\n            res.push_back(pool[t].key);\n\
    \        }\n        dump_impl(pool[t].r, res);\n    }\n\n   public:\n    explicit\
    \ OrderedMultiset(Compare compare)\n        : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          comp(std::move(compare)) {\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    OrderedMultiset() : OrderedMultiset(Compare()) {}\n\n    OrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {\n\
    \        for (const T& x : init) insert(x);\n    }\n\n    template <typename Iterator>\n\
    \    OrderedMultiset(Iterator first, Iterator last, Compare compare = Compare())\
    \ : OrderedMultiset(std::move(compare)) {\n        while (first != last) {\n \
    \           insert(*first);\n            ++first;\n        }\n    }\n\n    int\
    \ size() const {\n        return subtree_size(root);\n    }\n\n    int unique_size()\
    \ const {\n        return subtree_distinct_size(root);\n    }\n\n    bool empty()\
    \ const {\n        return size() == 0;\n    }\n\n    void clear() {\n        pool.clear();\n\
    \        root = -1;\n    }\n\n    void insert(T key, int multiplicity = 1) {\n\
    \        assert(multiplicity > 0);\n        root = insert_impl(root, key, multiplicity);\n\
    \    }\n\n    bool erase_one(const T& key) {\n        return erase_one_impl(root,\
    \ key);\n    }\n\n    bool erase(const T& key) {\n        return erase_one(key);\n\
    \    }\n\n    int erase_all(const T& key) {\n        return erase_all_impl(root,\
    \ key);\n    }\n\n    bool contains(const T& key) const {\n        return count(key)\
    \ > 0;\n    }\n\n    int count(const T& key) const {\n        return count_impl(root,\
    \ key);\n    }\n\n    const T* find_by_order(int k) const {\n        assert(0\
    \ <= k && k < size());\n        return kth_impl(root, k);\n    }\n\n    T kth(int\
    \ k) const {\n        assert(0 <= k && k < size());\n        return *kth_impl(root,\
    \ k);\n    }\n\n    int order_of_key(const T& key) const {\n        return order_of_key_impl(root,\
    \ key);\n    }\n\n    int count_less(const T& key) const {\n        return order_of_key(key);\n\
    \    }\n\n    int count_less_equal(const T& key) const {\n        return order_of_key_upper_impl(root,\
    \ key);\n    }\n\n    int count_greater(const T& key) const {\n        return\
    \ size() - count_less_equal(key);\n    }\n\n    int count_greater_equal(const\
    \ T& key) const {\n        return size() - count_less(key);\n    }\n\n    const\
    \ T* lower_bound(const T& key) const {\n        return lower_bound_impl(root,\
    \ key);\n    }\n\n    const T* upper_bound(const T& key) const {\n        return\
    \ upper_bound_impl(root, key);\n    }\n\n    const T* min_ge(const T& key) const\
    \ {\n        return lower_bound(key);\n    }\n\n    const T* min_gt(const T& key)\
    \ const {\n        return upper_bound(key);\n    }\n\n    const T* max_le(const\
    \ T& key) const {\n        return max_less_impl(root, key, false);\n    }\n\n\
    \    const T* max_lt(const T& key) const {\n        return max_less_impl(root,\
    \ key, true);\n    }\n\n    const T* min() const {\n        return empty() ? nullptr\
    \ : kth_impl(root, 0);\n    }\n\n    const T* max() const {\n        return empty()\
    \ ? nullptr : kth_impl(root, size() - 1);\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        std::vector<T> res;\n        res.reserve(size());\n       \
    \ dump_impl(root, res);\n        return res;\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n#line 5 \"ds/ordered_set/ordered_set.hpp\"\n\n#line\
    \ 10 \"ds/ordered_set/ordered_set.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \ntemplate <typename T, typename Compare = std::less<T>>\nstruct OrderedSet {\n\
    \   private:\n    OrderedMultiset<T, Compare> data;\n\n   public:\n    explicit\
    \ OrderedSet(Compare compare) : data(std::move(compare)) {}\n\n    OrderedSet()\
    \ : OrderedSet(Compare()) {}\n\n    OrderedSet(std::initializer_list<T> init,\
    \ Compare compare = Compare()) : OrderedSet(std::move(compare)) {\n        for\
    \ (const T& x : init) insert(x);\n    }\n\n    template <typename Iterator>\n\
    \    OrderedSet(Iterator first, Iterator last, Compare compare = Compare()) :\
    \ OrderedSet(std::move(compare)) {\n        while (first != last) {\n        \
    \    insert(*first);\n            ++first;\n        }\n    }\n\n    int size()\
    \ const {\n        return data.size();\n    }\n\n    int unique_size() const {\n\
    \        return data.size();\n    }\n\n    bool empty() const {\n        return\
    \ data.empty();\n    }\n\n    void clear() {\n        data.clear();\n    }\n\n\
    \    bool insert(T key) {\n        if (data.contains(key)) return false;\n   \
    \     data.insert(std::move(key));\n        return true;\n    }\n\n    bool erase(const\
    \ T& key) {\n        return data.erase(key);\n    }\n\n    bool contains(const\
    \ T& key) const {\n        return data.contains(key);\n    }\n\n    int count(const\
    \ T& key) const {\n        return contains(key) ? 1 : 0;\n    }\n\n    const T*\
    \ find_by_order(int k) const {\n        return data.find_by_order(k);\n    }\n\
    \n    T kth(int k) const {\n        return data.kth(k);\n    }\n\n    int order_of_key(const\
    \ T& key) const {\n        return data.order_of_key(key);\n    }\n\n    int count_less(const\
    \ T& key) const {\n        return data.count_less(key);\n    }\n\n    int count_less_equal(const\
    \ T& key) const {\n        return data.count_less_equal(key);\n    }\n\n    int\
    \ count_greater(const T& key) const {\n        return data.count_greater(key);\n\
    \    }\n\n    int count_greater_equal(const T& key) const {\n        return data.count_greater_equal(key);\n\
    \    }\n\n    const T* lower_bound(const T& key) const {\n        return data.lower_bound(key);\n\
    \    }\n\n    const T* upper_bound(const T& key) const {\n        return data.upper_bound(key);\n\
    \    }\n\n    const T* min_ge(const T& key) const {\n        return data.min_ge(key);\n\
    \    }\n\n    const T* min_gt(const T& key) const {\n        return data.min_gt(key);\n\
    \    }\n\n    const T* max_le(const T& key) const {\n        return data.max_le(key);\n\
    \    }\n\n    const T* max_lt(const T& key) const {\n        return data.max_lt(key);\n\
    \    }\n\n    const T* min() const {\n        return data.min();\n    }\n\n  \
    \  const T* max() const {\n        return data.max();\n    }\n\n    std::vector<T>\
    \ to_vector() const {\n        return data.to_vector();\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/ordered_set/ordered_set.test.cpp\"\
    \n\n#include <iostream>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    m1une::ds::OrderedSet<int> st;\n    for (int i\
    \ = 0; i < N; i++) {\n        int a;\n        std::cin >> a;\n        st.insert(a);\n\
    \    }\n\n    while (Q--) {\n        int type, x;\n        std::cin >> type >>\
    \ x;\n\n        if (type == 0) {\n            st.insert(x);\n        } else if\
    \ (type == 1) {\n            st.erase(x);\n        } else if (type == 2) {\n \
    \           if (st.size() < x) {\n                std::cout << -1 << '\\n';\n\
    \            } else {\n                std::cout << st.kth(x - 1) << '\\n';\n\
    \            }\n        } else if (type == 3) {\n            std::cout << st.count_less_equal(x)\
    \ << '\\n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            std::cout << (ans ? *ans : -1) << '\\n';\n        } else {\n    \
    \        const int* ans = st.min_ge(x);\n            std::cout << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"ds/ordered_set/ordered_set.hpp\"\n\n#include <iostream>\n\nvoid fast_io()\
    \ {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n\n    int N, Q;\n    std::cin >> N >> Q;\n\n\
    \    m1une::ds::OrderedSet<int> st;\n    for (int i = 0; i < N; i++) {\n     \
    \   int a;\n        std::cin >> a;\n        st.insert(a);\n    }\n\n    while\
    \ (Q--) {\n        int type, x;\n        std::cin >> type >> x;\n\n        if\
    \ (type == 0) {\n            st.insert(x);\n        } else if (type == 1) {\n\
    \            st.erase(x);\n        } else if (type == 2) {\n            if (st.size()\
    \ < x) {\n                std::cout << -1 << '\\n';\n            } else {\n  \
    \              std::cout << st.kth(x - 1) << '\\n';\n            }\n        }\
    \ else if (type == 3) {\n            std::cout << st.count_less_equal(x) << '\\\
    n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            std::cout << (ans ? *ans : -1) << '\\n';\n        } else {\n    \
    \        const int* ans = st.min_ge(x);\n            std::cout << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/ordered_set/ordered_set.hpp
  - ds/ordered_set/ordered_multiset.hpp
  isVerificationFile: true
  path: verify/ds/ordered_set/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/ordered_set/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/ordered_set/ordered_set.test.cpp
- /verify/verify/ds/ordered_set/ordered_set.test.cpp.html
title: verify/ds/ordered_set/ordered_set.test.cpp
---
