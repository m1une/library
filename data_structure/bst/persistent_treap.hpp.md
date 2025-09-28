---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/persistent_treap.test.cpp
    title: verify/data_structure/persistent_treap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Persistent Treap
    links: []
  bundledCode: "#line 1 \"data_structure/bst/persistent_treap.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <ctime>\n#include <iostream>\n#include <memory>\n#include\
    \ <optional>\n#include <random>\n\nnamespace m1une {\n\ntemplate <typename T>\n\
    struct persistent_treap {\n   private:\n    struct node {\n        T _key;\n \
    \       int _priority;\n        std::shared_ptr<node> _l, _r;\n        int _count;\n\
    \n        node(T key) : _key(key), _priority(rand()), _l(nullptr), _r(nullptr),\
    \ _count(1) {}\n    };\n\n    std::shared_ptr<node> _root;\n\n    int count(std::shared_ptr<node>\
    \ t) {\n        return t ? t->_count : 0;\n    }\n\n    void update_count(std::shared_ptr<node>\
    \ t) {\n        if (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n\
    \        }\n    }\n\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
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
    }  // namespace m1une\n\n\n\n/**\n * @brief Persistent Treap\n */\n"
  code: "#ifndef M1UNE_PERSISTENT_TREAP_HPP\n#define M1UNE_PERSISTENT_TREAP_HPP 1\n\
    \n#include <algorithm>\n#include <ctime>\n#include <iostream>\n#include <memory>\n\
    #include <optional>\n#include <random>\n\nnamespace m1une {\n\ntemplate <typename\
    \ T>\nstruct persistent_treap {\n   private:\n    struct node {\n        T _key;\n\
    \        int _priority;\n        std::shared_ptr<node> _l, _r;\n        int _count;\n\
    \n        node(T key) : _key(key), _priority(rand()), _l(nullptr), _r(nullptr),\
    \ _count(1) {}\n    };\n\n    std::shared_ptr<node> _root;\n\n    int count(std::shared_ptr<node>\
    \ t) {\n        return t ? t->_count : 0;\n    }\n\n    void update_count(std::shared_ptr<node>\
    \ t) {\n        if (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n\
    \        }\n    }\n\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
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
    }  // namespace m1une\n\n#endif  // M1UNE_PERSISTENT_TREAP_HPP\n\n/**\n * @brief\
    \ Persistent Treap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/bst/persistent_treap.hpp
  requiredBy: []
  timestamp: '2025-09-28 20:25:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/persistent_treap.test.cpp
documentation_of: data_structure/bst/persistent_treap.hpp
layout: document
redirect_from:
- /library/data_structure/bst/persistent_treap.hpp
- /library/data_structure/bst/persistent_treap.hpp.html
title: Persistent Treap
---
