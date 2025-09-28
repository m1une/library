---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/treap.test.cpp
    title: verify/data_structure/treap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Treap
    links: []
  bundledCode: "#line 1 \"data_structure/bst/treap.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <ctime>\n#include <iostream>\n#include <random>\n\nnamespace m1une {\n\
    \ntemplate <typename T>\nstruct treap {\n   private:\n    struct node {\n    \
    \    T _key;\n        int _priority;\n        node *_l, *_r;\n        int _count;\n\
    \n        node(T key) : _key(key), _priority(rand()), _l(nullptr), _r(nullptr),\
    \ _count(1) {}\n    };\n\n    node* _root;\n\n    int count(node* t) {\n     \
    \   return t ? t->_count : 0;\n    }\n\n    void update_count(node* t) {\n   \
    \     if (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n   \
    \     }\n    }\n\n    void split(node* t, T key, node*& l, node*& r) {\n     \
    \   if (!t) {\n            l = r = nullptr;\n            return;\n        }\n\
    \        if (key < t->_key) {\n            split(t->_l, key, l, t->_l);\n    \
    \        r = t;\n        } else {\n            split(t->_r, key, t->_r, r);\n\
    \            l = t;\n        }\n        update_count(t);\n    }\n\n    node* merge(node*\
    \ l, node* r) {\n        if (!l || !r) {\n            return l ? l : r;\n    \
    \    }\n        if (l->_priority > r->_priority) {\n            l->_r = merge(l->_r,\
    \ r);\n            update_count(l);\n            return l;\n        } else {\n\
    \            r->_l = merge(l, r->_l);\n            update_count(r);\n        \
    \    return r;\n        }\n    }\n\n    void insert_impl(node*& t, node* item)\
    \ {\n        if (!t) {\n            t = item;\n            return;\n        }\n\
    \        if (item->_priority > t->_priority) {\n            split(t, item->_key,\
    \ item->_l, item->_r);\n            t = item;\n        } else {\n            insert_impl(item->_key\
    \ < t->_key ? t->_l : t->_r, item);\n        }\n        update_count(t);\n   \
    \ }\n\n    void erase_impl(node*& t, T key) {\n        if (!t) {\n           \
    \ return;\n        }\n        if (t->_key == key) {\n            node* temp =\
    \ t;\n            t = merge(t->_l, t->_r);\n            delete temp;\n       \
    \ } else {\n            erase_impl(key < t->_key ? t->_l : t->_r, key);\n    \
    \    }\n        update_count(t);\n    }\n\n    bool contains_impl(node* t, T key)\
    \ {\n        if (!t) return false;\n        if (t->_key == key) return true;\n\
    \        if (key < t->_key) {\n            return contains_impl(t->_l, key);\n\
    \        } else {\n            return contains_impl(t->_r, key);\n        }\n\
    \    }\n\n    T find_by_order_impl(node* t, int k) {\n        if (!t) return T();\
    \  // Should not happen with valid k\n        int left_count = count(t->_l);\n\
    \        if (k < left_count) return find_by_order_impl(t->_l, k);\n        if\
    \ (k == left_count) return t->_key;\n        return find_by_order_impl(t->_r,\
    \ k - left_count - 1);\n    }\n\n    int order_of_key_impl(node* t, T key) {\n\
    \        if (!t) return 0;\n        if (key <= t->_key) return order_of_key_impl(t->_l,\
    \ key);\n        return count(t->_l) + 1 + order_of_key_impl(t->_r, key);\n  \
    \  }\n\n    T* lower_bound_impl(node* t, T key) {\n        if (!t) return nullptr;\n\
    \        if (key <= t->_key) {\n            T* res = lower_bound_impl(t->_l, key);\n\
    \            return res ? res : &t->_key;\n        }\n        return lower_bound_impl(t->_r,\
    \ key);\n    }\n\n    T* upper_bound_impl(node* t, T key) {\n        if (!t) return\
    \ nullptr;\n        if (key < t->_key) {\n            T* res = upper_bound_impl(t->_l,\
    \ key);\n            return res ? res : &t->_key;\n        }\n        return upper_bound_impl(t->_r,\
    \ key);\n    }\n\n   public:\n    treap() : _root(nullptr) {\n        srand(time(NULL));\n\
    \    }\n\n    void insert(T key) {\n        insert_impl(_root, new node(key));\n\
    \    }\n\n    void erase(T key) {\n        erase_impl(_root, key);\n    }\n\n\
    \    bool contains(T key) {\n        return contains_impl(_root, key);\n    }\n\
    \n    T find_by_order(int k) {\n        return find_by_order_impl(_root, k);\n\
    \    }\n\n    int order_of_key(T key) {\n        return order_of_key_impl(_root,\
    \ key);\n    }\n\n    T* lower_bound(T key) {\n        return lower_bound_impl(_root,\
    \ key);\n    }\n\n    T* upper_bound(T key) {\n        return upper_bound_impl(_root,\
    \ key);\n    }\n\n    int size() {\n        return count(_root);\n    }\n};\n\n\
    }  // namespace m1une\n\n\n/**\n * @brief Treap\n */\n"
  code: "#ifndef M1UNE_TREAP_HPP\n#define M1UNE_TREAP_HPP 1\n\n#include <algorithm>\n\
    #include <ctime>\n#include <iostream>\n#include <random>\n\nnamespace m1une {\n\
    \ntemplate <typename T>\nstruct treap {\n   private:\n    struct node {\n    \
    \    T _key;\n        int _priority;\n        node *_l, *_r;\n        int _count;\n\
    \n        node(T key) : _key(key), _priority(rand()), _l(nullptr), _r(nullptr),\
    \ _count(1) {}\n    };\n\n    node* _root;\n\n    int count(node* t) {\n     \
    \   return t ? t->_count : 0;\n    }\n\n    void update_count(node* t) {\n   \
    \     if (t) {\n            t->_count = 1 + count(t->_l) + count(t->_r);\n   \
    \     }\n    }\n\n    void split(node* t, T key, node*& l, node*& r) {\n     \
    \   if (!t) {\n            l = r = nullptr;\n            return;\n        }\n\
    \        if (key < t->_key) {\n            split(t->_l, key, l, t->_l);\n    \
    \        r = t;\n        } else {\n            split(t->_r, key, t->_r, r);\n\
    \            l = t;\n        }\n        update_count(t);\n    }\n\n    node* merge(node*\
    \ l, node* r) {\n        if (!l || !r) {\n            return l ? l : r;\n    \
    \    }\n        if (l->_priority > r->_priority) {\n            l->_r = merge(l->_r,\
    \ r);\n            update_count(l);\n            return l;\n        } else {\n\
    \            r->_l = merge(l, r->_l);\n            update_count(r);\n        \
    \    return r;\n        }\n    }\n\n    void insert_impl(node*& t, node* item)\
    \ {\n        if (!t) {\n            t = item;\n            return;\n        }\n\
    \        if (item->_priority > t->_priority) {\n            split(t, item->_key,\
    \ item->_l, item->_r);\n            t = item;\n        } else {\n            insert_impl(item->_key\
    \ < t->_key ? t->_l : t->_r, item);\n        }\n        update_count(t);\n   \
    \ }\n\n    void erase_impl(node*& t, T key) {\n        if (!t) {\n           \
    \ return;\n        }\n        if (t->_key == key) {\n            node* temp =\
    \ t;\n            t = merge(t->_l, t->_r);\n            delete temp;\n       \
    \ } else {\n            erase_impl(key < t->_key ? t->_l : t->_r, key);\n    \
    \    }\n        update_count(t);\n    }\n\n    bool contains_impl(node* t, T key)\
    \ {\n        if (!t) return false;\n        if (t->_key == key) return true;\n\
    \        if (key < t->_key) {\n            return contains_impl(t->_l, key);\n\
    \        } else {\n            return contains_impl(t->_r, key);\n        }\n\
    \    }\n\n    T find_by_order_impl(node* t, int k) {\n        if (!t) return T();\
    \  // Should not happen with valid k\n        int left_count = count(t->_l);\n\
    \        if (k < left_count) return find_by_order_impl(t->_l, k);\n        if\
    \ (k == left_count) return t->_key;\n        return find_by_order_impl(t->_r,\
    \ k - left_count - 1);\n    }\n\n    int order_of_key_impl(node* t, T key) {\n\
    \        if (!t) return 0;\n        if (key <= t->_key) return order_of_key_impl(t->_l,\
    \ key);\n        return count(t->_l) + 1 + order_of_key_impl(t->_r, key);\n  \
    \  }\n\n    T* lower_bound_impl(node* t, T key) {\n        if (!t) return nullptr;\n\
    \        if (key <= t->_key) {\n            T* res = lower_bound_impl(t->_l, key);\n\
    \            return res ? res : &t->_key;\n        }\n        return lower_bound_impl(t->_r,\
    \ key);\n    }\n\n    T* upper_bound_impl(node* t, T key) {\n        if (!t) return\
    \ nullptr;\n        if (key < t->_key) {\n            T* res = upper_bound_impl(t->_l,\
    \ key);\n            return res ? res : &t->_key;\n        }\n        return upper_bound_impl(t->_r,\
    \ key);\n    }\n\n   public:\n    treap() : _root(nullptr) {\n        srand(time(NULL));\n\
    \    }\n\n    void insert(T key) {\n        insert_impl(_root, new node(key));\n\
    \    }\n\n    void erase(T key) {\n        erase_impl(_root, key);\n    }\n\n\
    \    bool contains(T key) {\n        return contains_impl(_root, key);\n    }\n\
    \n    T find_by_order(int k) {\n        return find_by_order_impl(_root, k);\n\
    \    }\n\n    int order_of_key(T key) {\n        return order_of_key_impl(_root,\
    \ key);\n    }\n\n    T* lower_bound(T key) {\n        return lower_bound_impl(_root,\
    \ key);\n    }\n\n    T* upper_bound(T key) {\n        return upper_bound_impl(_root,\
    \ key);\n    }\n\n    int size() {\n        return count(_root);\n    }\n};\n\n\
    }  // namespace m1une\n#endif  // M1UNE_TREAP_HPP\n\n/**\n * @brief Treap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/bst/treap.hpp
  requiredBy: []
  timestamp: '2025-09-28 20:25:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/treap.test.cpp
documentation_of: data_structure/bst/treap.hpp
layout: document
redirect_from:
- /library/data_structure/bst/treap.hpp
- /library/data_structure/bst/treap.hpp.html
title: Treap
---
