---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data-structure/persistent-treap.hpp\"\n\n\n\n#include <iostream>\n\
    #include <random>\n#include <algorithm>\n#include <memory>\n\nnamespace m1une\
    \ {\n\ntemplate <typename T>\nstruct persistent_treap {\nprivate:\n    struct\
    \ node {\n        T key;\n        int priority;\n        std::shared_ptr<node>\
    \ l, r;\n        int count;\n\n        node(T key) : key(key), priority(rand()),\
    \ l(nullptr), r(nullptr), count(1) {}\n    };\n\n    std::shared_ptr<node> root;\n\
    \n    int count(std::shared_ptr<node> t) {\n        return t ? t->count : 0;\n\
    \    }\n\n    void update_count(std::shared_ptr<node> t) {\n        if (t) {\n\
    \            t->count = 1 + count(t->l) + count(t->r);\n        }\n    }\n\n \
    \   // Splitting the treap\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
    \ l, std::shared_ptr<node>& r) {\n        if (!t) {\n            l = r = nullptr;\n\
    \            return;\n        }\n        if (key < t->key) {\n            auto\
    \ new_node = std::make_shared<node>(*t);\n            split(new_node->l, key,\
    \ l, new_node->l);\n            r = new_node;\n        } else {\n            auto\
    \ new_node = std::make_shared<node>(*t);\n            split(new_node->r, key,\
    \ new_node->r, r);\n            l = new_node;\n        }\n        update_count(l);\n\
    \        update_count(r);\n    }\n\n    // Merging two treaps\n    std::shared_ptr<node>\
    \ merge(std::shared_ptr<node> l, std::shared_ptr<node> r) {\n        if (!l ||\
    \ !r) {\n            return l ? l : r;\n        }\n        if (l->priority > r->priority)\
    \ {\n            auto new_node = std::make_shared<node>(*l);\n            new_node->r\
    \ = merge(new_node->r, r);\n            update_count(new_node);\n            return\
    \ new_node;\n        } else {\n            auto new_node = std::make_shared<node>(*r);\n\
    \            new_node->l = merge(l, new_node->l);\n            update_count(new_node);\n\
    \            return new_node;\n        }\n    }\n    \n    // Inserting a key\n\
    \    std::shared_ptr<node> insert_impl(std::shared_ptr<node> t, std::shared_ptr<node>\
    \ item) {\n        if (!t) {\n            return item;\n        }\n        if\
    \ (item->priority > t->priority) {\n            split(t, item->key, item->l, item->r);\n\
    \            update_count(item);\n            return item;\n        }\n      \
    \  \n        auto new_node = std::make_shared<node>(*t);\n        if (item->key\
    \ < new_node->key) {\n            new_node->l = insert_impl(new_node->l, item);\n\
    \        } else {\n            new_node->r = insert_impl(new_node->r, item);\n\
    \        }\n        update_count(new_node);\n        return new_node;\n    }\n\
    \n\n    // Erasing a key\n    std::shared_ptr<node> erase_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) {\n            return nullptr;\n        }\n   \
    \     if (t->key == key) {\n            return merge(t->l, t->r);\n        }\n\
    \        \n        auto new_node = std::make_shared<node>(*t);\n        if (key\
    \ < new_node->key) {\n            new_node->l = erase_impl(new_node->l, key);\n\
    \        } else {\n            new_node->r = erase_impl(new_node->r, key);\n \
    \       }\n        update_count(new_node);\n        return new_node;\n    }\n\n\
    \    // Find the k-th element\n    T find_by_order_impl(std::shared_ptr<node>\
    \ t, int k) {\n        if (!t) {\n            // Or throw an exception\n     \
    \       return T();\n        }\n        int left_count = count(t->l);\n      \
    \  if (k < left_count) {\n            return find_by_order_impl(t->l, k);\n  \
    \      }\n        if (k == left_count) {\n            return t->key;\n       \
    \ }\n        return find_by_order_impl(t->r, k - left_count - 1);\n    }\n\n \
    \   // Count elements less than key\n    int order_of_key_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) {\n            return 0;\n        }\n        if\
    \ (key < t->key) {\n            return order_of_key_impl(t->l, key);\n       \
    \ }\n        if (key == t->key) {\n            return count(t->l);\n        }\n\
    \        return count(t->l) + 1 + order_of_key_impl(t->r, key);\n    }\n\n\npublic:\n\
    \    persistent_treap() : root(nullptr) {\n        srand(time(NULL));\n    }\n\
    \    \n    persistent_treap(std::shared_ptr<node> root) : root(root) {}\n\n\n\
    \    persistent_treap insert(T key) {\n        return persistent_treap(insert_impl(root,\
    \ std::make_shared<node>(key)));\n    }\n\n    persistent_treap erase(T key) {\n\
    \        return persistent_treap(erase_impl(root, key));\n    }\n    \n    T find_by_order(int\
    \ k) {\n        return find_by_order_impl(root, k);\n    }\n    \n    int order_of_key(T\
    \ key) {\n        return order_of_key_impl(root, key);\n    }\n\n\n    int size()\
    \ {\n        return count(root);\n    }\n};\n\n} // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_TREAP_HPP\n#define M1UNE_PERSISTENT_TREAP_HPP 1\n\
    \n#include <iostream>\n#include <random>\n#include <algorithm>\n#include <memory>\n\
    \nnamespace m1une {\n\ntemplate <typename T>\nstruct persistent_treap {\nprivate:\n\
    \    struct node {\n        T key;\n        int priority;\n        std::shared_ptr<node>\
    \ l, r;\n        int count;\n\n        node(T key) : key(key), priority(rand()),\
    \ l(nullptr), r(nullptr), count(1) {}\n    };\n\n    std::shared_ptr<node> root;\n\
    \n    int count(std::shared_ptr<node> t) {\n        return t ? t->count : 0;\n\
    \    }\n\n    void update_count(std::shared_ptr<node> t) {\n        if (t) {\n\
    \            t->count = 1 + count(t->l) + count(t->r);\n        }\n    }\n\n \
    \   // Splitting the treap\n    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>&\
    \ l, std::shared_ptr<node>& r) {\n        if (!t) {\n            l = r = nullptr;\n\
    \            return;\n        }\n        if (key < t->key) {\n            auto\
    \ new_node = std::make_shared<node>(*t);\n            split(new_node->l, key,\
    \ l, new_node->l);\n            r = new_node;\n        } else {\n            auto\
    \ new_node = std::make_shared<node>(*t);\n            split(new_node->r, key,\
    \ new_node->r, r);\n            l = new_node;\n        }\n        update_count(l);\n\
    \        update_count(r);\n    }\n\n    // Merging two treaps\n    std::shared_ptr<node>\
    \ merge(std::shared_ptr<node> l, std::shared_ptr<node> r) {\n        if (!l ||\
    \ !r) {\n            return l ? l : r;\n        }\n        if (l->priority > r->priority)\
    \ {\n            auto new_node = std::make_shared<node>(*l);\n            new_node->r\
    \ = merge(new_node->r, r);\n            update_count(new_node);\n            return\
    \ new_node;\n        } else {\n            auto new_node = std::make_shared<node>(*r);\n\
    \            new_node->l = merge(l, new_node->l);\n            update_count(new_node);\n\
    \            return new_node;\n        }\n    }\n    \n    // Inserting a key\n\
    \    std::shared_ptr<node> insert_impl(std::shared_ptr<node> t, std::shared_ptr<node>\
    \ item) {\n        if (!t) {\n            return item;\n        }\n        if\
    \ (item->priority > t->priority) {\n            split(t, item->key, item->l, item->r);\n\
    \            update_count(item);\n            return item;\n        }\n      \
    \  \n        auto new_node = std::make_shared<node>(*t);\n        if (item->key\
    \ < new_node->key) {\n            new_node->l = insert_impl(new_node->l, item);\n\
    \        } else {\n            new_node->r = insert_impl(new_node->r, item);\n\
    \        }\n        update_count(new_node);\n        return new_node;\n    }\n\
    \n\n    // Erasing a key\n    std::shared_ptr<node> erase_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) {\n            return nullptr;\n        }\n   \
    \     if (t->key == key) {\n            return merge(t->l, t->r);\n        }\n\
    \        \n        auto new_node = std::make_shared<node>(*t);\n        if (key\
    \ < new_node->key) {\n            new_node->l = erase_impl(new_node->l, key);\n\
    \        } else {\n            new_node->r = erase_impl(new_node->r, key);\n \
    \       }\n        update_count(new_node);\n        return new_node;\n    }\n\n\
    \    // Find the k-th element\n    T find_by_order_impl(std::shared_ptr<node>\
    \ t, int k) {\n        if (!t) {\n            // Or throw an exception\n     \
    \       return T();\n        }\n        int left_count = count(t->l);\n      \
    \  if (k < left_count) {\n            return find_by_order_impl(t->l, k);\n  \
    \      }\n        if (k == left_count) {\n            return t->key;\n       \
    \ }\n        return find_by_order_impl(t->r, k - left_count - 1);\n    }\n\n \
    \   // Count elements less than key\n    int order_of_key_impl(std::shared_ptr<node>\
    \ t, T key) {\n        if (!t) {\n            return 0;\n        }\n        if\
    \ (key < t->key) {\n            return order_of_key_impl(t->l, key);\n       \
    \ }\n        if (key == t->key) {\n            return count(t->l);\n        }\n\
    \        return count(t->l) + 1 + order_of_key_impl(t->r, key);\n    }\n\n\npublic:\n\
    \    persistent_treap() : root(nullptr) {\n        srand(time(NULL));\n    }\n\
    \    \n    persistent_treap(std::shared_ptr<node> root) : root(root) {}\n\n\n\
    \    persistent_treap insert(T key) {\n        return persistent_treap(insert_impl(root,\
    \ std::make_shared<node>(key)));\n    }\n\n    persistent_treap erase(T key) {\n\
    \        return persistent_treap(erase_impl(root, key));\n    }\n    \n    T find_by_order(int\
    \ k) {\n        return find_by_order_impl(root, k);\n    }\n    \n    int order_of_key(T\
    \ key) {\n        return order_of_key_impl(root, key);\n    }\n\n\n    int size()\
    \ {\n        return count(root);\n    }\n};\n\n} // namespace m1une\n\n#endif\
    \ // M1UNE_PERSISTENT_TREAP_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data-structure/persistent-treap.hpp
  requiredBy: []
  timestamp: '2025-09-25 04:22:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data-structure/persistent-treap.hpp
layout: document
redirect_from:
- /library/data-structure/persistent-treap.hpp
- /library/data-structure/persistent-treap.hpp.html
title: data-structure/persistent-treap.hpp
---
