---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/ordered_set.hpp
    title: Ordered Set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/ordered_multiset.test.cpp
    title: verify/data_structure/ordered_multiset.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/ordered_set.test.cpp
    title: verify/data_structure/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/ordered_multiset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <functional>\n#include <initializer_list>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct OrderedMultiset\
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
    \ dump_impl(root, res);\n        return res;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ORDERED_MULTISET_HPP\n#define M1UNE_ORDERED_MULTISET_HPP 1\n\
    \n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <functional>\n\
    #include <initializer_list>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace data_structure {\n\ntemplate <typename T, typename Compare\
    \ = std::less<T>>\nstruct OrderedMultiset {\n   private:\n    struct Node {\n\
    \        T key;\n        int priority;\n        int count;\n        int size;\n\
    \        int distinct_size;\n        int l, r;\n\n        Node(T value, int node_priority,\
    \ int multiplicity)\n            : key(std::move(value)),\n              priority(node_priority),\n\
    \              count(multiplicity),\n              size(multiplicity),\n     \
    \         distinct_size(1),\n              l(-1),\n              r(-1) {}\n  \
    \  };\n\n    std::vector<Node> pool;\n    int root;\n    std::uint32_t rng_state;\n\
    \    Compare comp;\n\n    bool equal(const T& a, const T& b) const {\n       \
    \ return !comp(a, b) && !comp(b, a);\n    }\n\n    int subtree_size(int t) const\
    \ {\n        return t == -1 ? 0 : pool[t].size;\n    }\n\n    int subtree_distinct_size(int\
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
    \ dump_impl(root, res);\n        return res;\n    }\n};\n\n}  // namespace data_structure\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ORDERED_MULTISET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/ordered_multiset.hpp
  requiredBy:
  - data_structure/ordered_set.hpp
  timestamp: '2026-06-14 04:54:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/ordered_multiset.test.cpp
  - verify/data_structure/ordered_set.test.cpp
documentation_of: data_structure/ordered_multiset.hpp
layout: document
title: Ordered Multiset
---

## Overview

`OrderedMultiset` is a randomized binary search tree for multisets. It stores equal keys as one node with a multiplicity, so it supports standard multiset operations plus order-statistics queries such as k-th element and rank.

Pointers returned by bound and predecessor/successor methods remain valid until the multiset is modified.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

## Constructors

* `OrderedMultiset()`
  Constructs an empty multiset. ($O(1)$)

* `OrderedMultiset(Compare compare)`
  Constructs an empty multiset with a custom comparator. ($O(1)$)

* `OrderedMultiset(std::initializer_list<T> init)`
  Constructs a multiset from an initializer list. ($O(N \log N)$)

* `OrderedMultiset(Iterator first, Iterator last)`
  Constructs a multiset from a range. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the total number of elements, including duplicates. | $O(1)$ |
| `int unique_size() const` | Returns the number of distinct keys. | $O(1)$ |
| `bool empty() const` | Returns whether the multiset is empty. | $O(1)$ |
| `void clear()` | Removes all elements. | $O(1)$ |
| `void insert(T key, int multiplicity = 1)` | Inserts `multiplicity` copies of `key`. | $O(\log N)$ |
| `bool erase_one(const T& key)` | Removes one copy of `key`; returns whether an element was removed. | $O(\log N)$ |
| `bool erase(const T& key)` | Alias for `erase_one(key)`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Removes all copies of `key` and returns the number removed. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns the multiplicity of `key`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest element. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest element by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of elements strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of elements less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of elements strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of elements greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest element greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest element strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest element less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest element strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum element, or `nullptr` if the multiset is empty. | $O(\log N)$ |
| `std::vector<T> to_vector() const` | Returns all elements in sorted order, including duplicates. | $O(N)$ |

## Example

```cpp
#include "data_structure/ordered_multiset.hpp"

#include <iostream>

int main() {
    m1une::data_structure::OrderedMultiset<int> ms = {3, 1, 3, 5};

    ms.insert(2);
    ms.erase_one(3);

    std::cout << ms.kth(2) << "\n";           // 3
    std::cout << ms.order_of_key(4) << "\n";  // 3

    if (auto p = ms.max_le(4)) {
        std::cout << *p << "\n";              // 3
    }
}
```
