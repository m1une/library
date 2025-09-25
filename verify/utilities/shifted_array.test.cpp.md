---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/shifted_array.hpp
    title: Persistent Treap
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858
  bundledCode: "#line 1 \"verify/utilities/shifted_array.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"utilities/shifted_array.hpp\"\
    \n\n\n\n#line 7 \"utilities/shifted_array.hpp\"\n#include <optional>\n#line 9\
    \ \"utilities/shifted_array.hpp\"\n\nnamespace m1une {\n\ntemplate <typename T>\n\
    struct persistent_treap {\n   private:\n    struct node {\n        T _key;\n \
    \       int _priority;\n        std::shared_ptr<node> _l, _r;\n        int _count;\n\
    \n        node(T key)\n            : _key(key),\n              _priority(rand()),\n\
    \              _l(nullptr),\n              _r(nullptr),\n              _count(1)\
    \ {}\n    };\n\n    std::shared_ptr<node> _root;\n\n    int count(std::shared_ptr<node>\
    \ t) {\n        return t ? t->_count : 0;\n    }\n\n    void update_count(std::shared_ptr<node>\
    \ t) {\n        if (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n\
    \        }\n    }\n\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
    \ l,\n               std::shared_ptr<node>& r) {\n        if (!t) {\n        \
    \    l = r = nullptr;\n            return;\n        }\n        if (key < t->_key)\
    \ {\n            auto new_node = std::make_shared<node>(*t);\n            split(new_node->_l,\
    \ key, l, new_node->_l);\n            r = new_node;\n            update_count(r);\n\
    \        } else {\n            auto new_node = std::make_shared<node>(*t);\n \
    \           split(new_node->_r, key, new_node->_r, r);\n            l = new_node;\n\
    \            update_count(l);\n        }\n    }\n\n    std::shared_ptr<node> merge(std::shared_ptr<node>\
    \ l,\n                                std::shared_ptr<node> r) {\n        if (!l\
    \ || !r) return l ? l : r;\n        if (l->_priority > r->_priority) {\n     \
    \       auto new_node = std::make_shared<node>(*l);\n            new_node->_r\
    \ = merge(new_node->_r, r);\n            update_count(new_node);\n           \
    \ return new_node;\n        } else {\n            auto new_node = std::make_shared<node>(*r);\n\
    \            new_node->_l = merge(l, new_node->_l);\n            update_count(new_node);\n\
    \            return new_node;\n        }\n    }\n\n    std::shared_ptr<node> insert_impl(std::shared_ptr<node>\
    \ t,\n                                      std::shared_ptr<node> item) {\n  \
    \      if (!t) return item;\n        if (item->_priority > t->_priority) {\n \
    \           split(t, item->_key, item->_l, item->_r);\n            update_count(item);\n\
    \            return item;\n        }\n        auto new_node = std::make_shared<node>(*t);\n\
    \        if (item->_key < new_node->_key) {\n            new_node->_l = insert_impl(new_node->_l,\
    \ item);\n        } else {\n            new_node->_r = insert_impl(new_node->_r,\
    \ item);\n        }\n        update_count(new_node);\n        return new_node;\n\
    \    }\n\n    std::shared_ptr<node> erase_impl(std::shared_ptr<node> t, T key)\
    \ {\n        if (!t) return nullptr;\n        if (t->_key == key) return merge(t->_l,\
    \ t->_r);\n        auto new_node = std::make_shared<node>(*t);\n        if (key\
    \ < new_node->_key) {\n            new_node->_l = erase_impl(new_node->_l, key);\n\
    \        } else {\n            new_node->_r = erase_impl(new_node->_r, key);\n\
    \        }\n        update_count(new_node);\n        return new_node;\n    }\n\
    \n    T find_by_order_impl(std::shared_ptr<node> t, int k) {\n        if (!t)\
    \ return T();\n        int left_count = count(t->_l);\n        if (k < left_count)\
    \ return find_by_order_impl(t->_l, k);\n        if (k == left_count) return t->_key;\n\
    \        return find_by_order_impl(t->_r, k - left_count - 1);\n    }\n\n    int\
    \ order_of_key_impl(std::shared_ptr<node> t, T key) {\n        if (!t) return\
    \ 0;\n        if (key <= t->_key) return order_of_key_impl(t->_l, key);\n    \
    \    return count(t->_l) + 1 + order_of_key_impl(t->_r, key);\n    }\n\n    std::optional<T>\
    \ lower_bound_impl(std::shared_ptr<node> t, T key) {\n        if (!t) return std::nullopt;\n\
    \        if (key <= t->_key) {\n            auto res = lower_bound_impl(t->_l,\
    \ key);\n            return res.has_value() ? res : t->_key;\n        }\n    \
    \    return lower_bound_impl(t->_r, key);\n    }\n\n    std::optional<T> upper_bound_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) return std::nullopt;\n        if (key < t->_key)\
    \ {\n            auto res = upper_bound_impl(t->_l, key);\n            return\
    \ res.has_value() ? res : t->_key;\n        }\n        return upper_bound_impl(t->_r,\
    \ key);\n    }\n\n   public:\n    persistent_treap() : _root(nullptr) {\n    \
    \    srand(time(NULL));\n    }\n\n    persistent_treap(std::shared_ptr<node> root)\
    \ : _root(root) {}\n\n    persistent_treap insert(T key) {\n        return persistent_treap(\n\
    \            insert_impl(_root, std::make_shared<node>(key)));\n    }\n\n    persistent_treap\
    \ erase(T key) {\n        return persistent_treap(erase_impl(_root, key));\n \
    \   }\n\n    T find_by_order(int k) {\n        return find_by_order_impl(_root,\
    \ k);\n    }\n\n    int order_of_key(T key) {\n        return order_of_key_impl(_root,\
    \ key);\n    }\n\n    std::optional<T> lower_bound(T key) {\n        return lower_bound_impl(_root,\
    \ key);\n    }\n\n    std::optional<T> upper_bound(T key) {\n        return upper_bound_impl(_root,\
    \ key);\n    }\n\n    int size() {\n        return count(_root);\n    }\n};\n\n\
    }  // namespace m1une\n\n\n\n/**\n * @brief Persistent Treap\n */\n#line 7 \"\
    verify/utilities/shifted_array.test.cpp\"\n\nconstexpr long long MAX = 100000;\n\
    \nlong long solve(long long l, long long r) {\n    vector<char> is_prime(MAX,\
    \ 1);\n    is_prime[0] = is_prime[1] = 0;\n    m1une::shifted_array<vector<long\
    \ long>> prime_factors(l, r);\n    for (long long p = 2; p * p <= r; ++p) {\n\
    \        if (!is_prime[p]) continue;\n        for (long long x = 2 * p; x < MAX;\
    \ x += p) {\n            is_prime[x] = 0;\n        }\n        for (long long x\
    \ = (l + p - 1) / p * p; x <= r; x += p) {\n            prime_factors[x].emplace_back(p);\n\
    \        }\n    }\n    long long res = 0;\n    for (long long x = l; x <= r; ++x)\
    \ {\n        long long factor_count = 0;\n        long long y = x;\n        for\
    \ (long long p : prime_factors[x]) {\n            while (y % p == 0) {\n     \
    \           y /= p;\n                ++factor_count;\n            }\n        }\n\
    \        if (y > 1) {\n            ++factor_count;\n        }\n        if (is_prime[factor_count])\
    \ {\n            ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n\
    \    long long l, r;\n    cin >> l >> r;\n    cout << solve(l, r) << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../utilities/shifted_array.hpp\"\
    \n\nconstexpr long long MAX = 100000;\n\nlong long solve(long long l, long long\
    \ r) {\n    vector<char> is_prime(MAX, 1);\n    is_prime[0] = is_prime[1] = 0;\n\
    \    m1une::shifted_array<vector<long long>> prime_factors(l, r);\n    for (long\
    \ long p = 2; p * p <= r; ++p) {\n        if (!is_prime[p]) continue;\n      \
    \  for (long long x = 2 * p; x < MAX; x += p) {\n            is_prime[x] = 0;\n\
    \        }\n        for (long long x = (l + p - 1) / p * p; x <= r; x += p) {\n\
    \            prime_factors[x].emplace_back(p);\n        }\n    }\n    long long\
    \ res = 0;\n    for (long long x = l; x <= r; ++x) {\n        long long factor_count\
    \ = 0;\n        long long y = x;\n        for (long long p : prime_factors[x])\
    \ {\n            while (y % p == 0) {\n                y /= p;\n             \
    \   ++factor_count;\n            }\n        }\n        if (y > 1) {\n        \
    \    ++factor_count;\n        }\n        if (is_prime[factor_count]) {\n     \
    \       ++res;\n        }\n    }\n    return res;\n}\n\nint main() {\n    long\
    \ long l, r;\n    cin >> l >> r;\n    cout << solve(l, r) << endl;\n}\n"
  dependsOn:
  - utilities/shifted_array.hpp
  isVerificationFile: true
  path: verify/utilities/shifted_array.test.cpp
  requiredBy: []
  timestamp: '2025-09-25 18:58:23+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/utilities/shifted_array.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/shifted_array.test.cpp
- /verify/verify/utilities/shifted_array.test.cpp.html
title: verify/utilities/shifted_array.test.cpp
---
