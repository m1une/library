---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/persistent_treap.hpp
    title: Persistent Treap
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
  bundledCode: "#line 1 \"verify/data_structure/persistent_treap.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    data_structure/persistent_treap.hpp\"\n\n\n\n#include <algorithm>\n#include <ctime>\n\
    #include <iostream>\n#include <memory>\n#include <optional>\n#include <random>\n\
    \nnamespace m1une {\n\ntemplate <typename T>\nstruct persistent_treap {\n   private:\n\
    \    struct node {\n        T _key;\n        int _priority;\n        std::shared_ptr<node>\
    \ _l, _r;\n        int _count;\n\n        node(T key) : _key(key), _priority(rand()),\
    \ _l(nullptr), _r(nullptr), _count(1) {}\n    };\n\n    std::shared_ptr<node>\
    \ _root;\n\n    int count(std::shared_ptr<node> t) {\n        return t ? t->_count\
    \ : 0;\n    }\n\n    void update_count(std::shared_ptr<node> t) {\n        if\
    \ (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n        }\n\
    \    }\n\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
    \ l, std::shared_ptr<node>& r) {\n        if (!t) {\n            l = r = nullptr;\n\
    \            return;\n        }\n        if (key < t->_key) {\n            auto\
    \ new_node = std::make_shared<node>(*t);\n            split(new_node->_l, key,\
    \ l, new_node->_l);\n            r = new_node;\n            update_count(r);\n\
    \        } else {\n            auto new_node = std::make_shared<node>(*t);\n \
    \           split(new_node->_r, key, new_node->_r, r);\n            l = new_node;\n\
    \            update_count(l);\n        }\n    }\n\n    std::shared_ptr<node> merge(std::shared_ptr<node>\
    \ l, std::shared_ptr<node> r) {\n        if (!l || !r) return l ? l : r;\n   \
    \     if (l->_priority > r->_priority) {\n            auto new_node = std::make_shared<node>(*l);\n\
    \            new_node->_r = merge(new_node->_r, r);\n            update_count(new_node);\n\
    \            return new_node;\n        } else {\n            auto new_node = std::make_shared<node>(*r);\n\
    \            new_node->_l = merge(l, new_node->_l);\n            update_count(new_node);\n\
    \            return new_node;\n        }\n    }\n\n    std::shared_ptr<node> insert_impl(std::shared_ptr<node>\
    \ t, std::shared_ptr<node> item) {\n        if (!t) return item;\n        if (item->_priority\
    \ > t->_priority) {\n            split(t, item->_key, item->_l, item->_r);\n \
    \           update_count(item);\n            return item;\n        }\n       \
    \ auto new_node = std::make_shared<node>(*t);\n        if (item->_key < new_node->_key)\
    \ {\n            new_node->_l = insert_impl(new_node->_l, item);\n        } else\
    \ {\n            new_node->_r = insert_impl(new_node->_r, item);\n        }\n\
    \        update_count(new_node);\n        return new_node;\n    }\n\n    std::shared_ptr<node>\
    \ erase_impl(std::shared_ptr<node> t, T key) {\n        if (!t) return nullptr;\n\
    \        if (t->_key == key) return merge(t->_l, t->_r);\n        auto new_node\
    \ = std::make_shared<node>(*t);\n        if (key < new_node->_key) {\n       \
    \     new_node->_l = erase_impl(new_node->_l, key);\n        } else {\n      \
    \      new_node->_r = erase_impl(new_node->_r, key);\n        }\n        update_count(new_node);\n\
    \        return new_node;\n    }\n\n    T find_by_order_impl(std::shared_ptr<node>\
    \ t, int k) {\n        if (!t) return T();\n        int left_count = count(t->_l);\n\
    \        if (k < left_count) return find_by_order_impl(t->_l, k);\n        if\
    \ (k == left_count) return t->_key;\n        return find_by_order_impl(t->_r,\
    \ k - left_count - 1);\n    }\n\n    int order_of_key_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) return 0;\n        if (key <= t->_key) return order_of_key_impl(t->_l,\
    \ key);\n        return count(t->_l) + 1 + order_of_key_impl(t->_r, key);\n  \
    \  }\n\n    std::optional<T> lower_bound_impl(std::shared_ptr<node> t, T key)\
    \ {\n        if (!t) return std::nullopt;\n        if (key <= t->_key) {\n   \
    \         auto res = lower_bound_impl(t->_l, key);\n            return res.has_value()\
    \ ? res : t->_key;\n        }\n        return lower_bound_impl(t->_r, key);\n\
    \    }\n\n    std::optional<T> upper_bound_impl(std::shared_ptr<node> t, T key)\
    \ {\n        if (!t) return std::nullopt;\n        if (key < t->_key) {\n    \
    \        auto res = upper_bound_impl(t->_l, key);\n            return res.has_value()\
    \ ? res : t->_key;\n        }\n        return upper_bound_impl(t->_r, key);\n\
    \    }\n\n   public:\n    persistent_treap() : _root(nullptr) {\n        srand(time(NULL));\n\
    \    }\n\n    persistent_treap(std::shared_ptr<node> root) : _root(root) {}\n\n\
    \    persistent_treap insert(T key) {\n        return persistent_treap(insert_impl(_root,\
    \ std::make_shared<node>(key)));\n    }\n\n    persistent_treap erase(T key) {\n\
    \        return persistent_treap(erase_impl(_root, key));\n    }\n\n    T find_by_order(int\
    \ k) {\n        return find_by_order_impl(_root, k);\n    }\n\n    int order_of_key(T\
    \ key) {\n        return order_of_key_impl(_root, key);\n    }\n\n    std::optional<T>\
    \ lower_bound(T key) {\n        return lower_bound_impl(_root, key);\n    }\n\n\
    \    std::optional<T> upper_bound(T key) {\n        return upper_bound_impl(_root,\
    \ key);\n    }\n\n    int size() {\n        return count(_root);\n    }\n};\n\n\
    }  // namespace m1une\n\n\n\n/**\n * @brief Persistent Treap\n */\n#line 4 \"\
    verify/data_structure/persistent_treap.test.cpp\"\n\n#line 7 \"verify/data_structure/persistent_treap.test.cpp\"\
    \n#include <vector>\n\n// Fast I/O\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n    int N, Q;\n \
    \   std::cin >> N >> Q;\n    std::vector<int> a(N);\n    std::vector<int> distinct_elements;\n\
    \n    for (int i = 0; i < N; ++i) {\n        std::cin >> a[i];\n        distinct_elements.push_back(a[i]);\n\
    \    }\n\n    // Coordinate Compression\n    std::sort(distinct_elements.begin(),\
    \ distinct_elements.end());\n    distinct_elements.erase(std::unique(distinct_elements.begin(),\
    \ distinct_elements.end()), distinct_elements.end());\n\n    auto get_compressed_rank\
    \ = [&](int val) {\n        return std::lower_bound(distinct_elements.begin(),\
    \ distinct_elements.end(), val) - distinct_elements.begin();\n    };\n\n    //\
    \ Build a persistent treap for each prefix of the array\n    std::vector<m1une::persistent_treap<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; ++i) {\n        versions[i + 1]\
    \ = versions[i].insert(get_compressed_rank(a[i]));\n    }\n\n    for (int q =\
    \ 0; q < Q; ++q) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\n\
    \        // Meguru-style Binary Search\n        // We are looking for the smallest\
    \ rank 'ok' such that the number of elements\n        // in a[l..r-1] with rank\
    \ <= 'ok' is strictly greater than k.\n        int ng = -1;                  \
    \          // 'ng' is a rank that is always \"not good enough\"\n        int ok\
    \ = distinct_elements.size() - 1;  // 'ok' is a rank that is \"good enough\"\n\
    \n        while (std::abs(ok - ng) > 1) {\n            int mid = ng + (ok - ng)\
    \ / 2;\n\n            // Count elements in the range a[l..r-1] with a compressed\
    \ rank <= mid\n            int count_le = versions[r].order_of_key(mid + 1) -\
    \ versions[l].order_of_key(mid + 1);\n\n            if (count_le > k) {\n    \
    \            // mid is a possible answer, try for a smaller one\n            \
    \    ok = mid;\n            } else {\n                // mid is not the answer,\
    \ we need a larger rank\n                ng = mid;\n            }\n        }\n\
    \n        // The answer is the original value corresponding to the 'ok' rank\n\
    \        std::cout << distinct_elements[ok] << \"\\n\";\n    }\n\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../data_structure/persistent_treap.hpp\"\n\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n// Fast I/O\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n    int N, Q;\n \
    \   std::cin >> N >> Q;\n    std::vector<int> a(N);\n    std::vector<int> distinct_elements;\n\
    \n    for (int i = 0; i < N; ++i) {\n        std::cin >> a[i];\n        distinct_elements.push_back(a[i]);\n\
    \    }\n\n    // Coordinate Compression\n    std::sort(distinct_elements.begin(),\
    \ distinct_elements.end());\n    distinct_elements.erase(std::unique(distinct_elements.begin(),\
    \ distinct_elements.end()), distinct_elements.end());\n\n    auto get_compressed_rank\
    \ = [&](int val) {\n        return std::lower_bound(distinct_elements.begin(),\
    \ distinct_elements.end(), val) - distinct_elements.begin();\n    };\n\n    //\
    \ Build a persistent treap for each prefix of the array\n    std::vector<m1une::persistent_treap<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; ++i) {\n        versions[i + 1]\
    \ = versions[i].insert(get_compressed_rank(a[i]));\n    }\n\n    for (int q =\
    \ 0; q < Q; ++q) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\n\
    \        // Meguru-style Binary Search\n        // We are looking for the smallest\
    \ rank 'ok' such that the number of elements\n        // in a[l..r-1] with rank\
    \ <= 'ok' is strictly greater than k.\n        int ng = -1;                  \
    \          // 'ng' is a rank that is always \"not good enough\"\n        int ok\
    \ = distinct_elements.size() - 1;  // 'ok' is a rank that is \"good enough\"\n\
    \n        while (std::abs(ok - ng) > 1) {\n            int mid = ng + (ok - ng)\
    \ / 2;\n\n            // Count elements in the range a[l..r-1] with a compressed\
    \ rank <= mid\n            int count_le = versions[r].order_of_key(mid + 1) -\
    \ versions[l].order_of_key(mid + 1);\n\n            if (count_le > k) {\n    \
    \            // mid is a possible answer, try for a smaller one\n            \
    \    ok = mid;\n            } else {\n                // mid is not the answer,\
    \ we need a larger rank\n                ng = mid;\n            }\n        }\n\
    \n        // The answer is the original value corresponding to the 'ok' rank\n\
    \        std::cout << distinct_elements[ok] << \"\\n\";\n    }\n\n    return 0;\n\
    }\n"
  dependsOn:
  - data_structure/persistent_treap.hpp
  isVerificationFile: true
  path: verify/data_structure/persistent_treap.test.cpp
  requiredBy: []
  timestamp: '2025-09-25 23:11:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/persistent_treap.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/persistent_treap.test.cpp
- /verify/verify/data_structure/persistent_treap.test.cpp.html
title: verify/data_structure/persistent_treap.test.cpp
---
