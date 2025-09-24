---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Treap
    links: []
  bundledCode: "#line 1 \"data-structure/treap.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <iostream>\n#include <random>\n\nnamespace m1une {\n\ntemplate <typename\
    \ T>\nstruct treap {\n   private:\n    struct node {\n        T key;\n       \
    \ int priority;\n        node *l, *r;\n        int count;\n\n        node(T key)\n\
    \            : key(key), priority(rand()), l(nullptr), r(nullptr), count(1) {}\n\
    \    };\n\n    node* root;\n\n    int count(node* t) {\n        return t ? t->count\
    \ : 0;\n    }\n\n    void update_count(node* t) {\n        if (t) {\n        \
    \    t->count = 1 + count(t->l) + count(t->r);\n        }\n    }\n\n    // Splitting\
    \ the treap\n    void split(node* t, T key, node*& l, node*& r) {\n        if\
    \ (!t) {\n            l = r = nullptr;\n            return;\n        }\n     \
    \   if (key < t->key) {\n            split(t->l, key, l, t->l);\n            r\
    \ = t;\n        } else {\n            split(t->r, key, t->r, r);\n           \
    \ l = t;\n        }\n        update_count(t);\n    }\n\n    // Merging two treaps\n\
    \    node* merge(node* l, node* r) {\n        if (!l || !r) {\n            return\
    \ l ? l : r;\n        }\n        if (l->priority > r->priority) {\n          \
    \  l->r = merge(l->r, r);\n            update_count(l);\n            return l;\n\
    \        } else {\n            r->l = merge(l, r->l);\n            update_count(r);\n\
    \            return r;\n        }\n    }\n\n    // Inserting a key\n    void insert(node*&\
    \ t, node* item) {\n        if (!t) {\n            t = item;\n            return;\n\
    \        }\n        if (item->priority > t->priority) {\n            split(t,\
    \ item->key, item->l, item->r);\n            t = item;\n        } else {\n   \
    \         insert(item->key < t->key ? t->l : t->r, item);\n        }\n       \
    \ update_count(t);\n    }\n\n    // Erasing a key\n    void erase(node*& t, T\
    \ key) {\n        if (!t) {\n            return;\n        }\n        if (t->key\
    \ == key) {\n            node* temp = t;\n            t = merge(t->l, t->r);\n\
    \            delete temp;\n        } else {\n            erase(key < t->key ?\
    \ t->l : t->r, key);\n        }\n        update_count(t);\n    }\n\n    // Find\
    \ the k-th element\n    T find_by_order_impl(node* t, int k) {\n        if (!t)\
    \ return T();\n        int left_count = count(t->l);\n        if (k < left_count)\
    \ return find_by_order_impl(t->l, k);\n        if (k == left_count) return t->key;\n\
    \        return find_by_order_impl(t->r, k - left_count - 1);\n    }\n\n    //\
    \ Count elements less than key\n    int order_of_key_impl(node* t, T key) {\n\
    \        if (!t) return 0;\n        if (key <= t->key) return order_of_key_impl(t->l,\
    \ key);\n        return count(t->l) + 1 + order_of_key_impl(t->r, key);\n    }\n\
    \n    T* lower_bound_impl(node* t, T key) {\n        if (!t) return nullptr;\n\
    \        if (key <= t->key) {\n            T* res = lower_bound_impl(t->l, key);\n\
    \            return res ? res : &t->key;\n        }\n        return lower_bound_impl(t->r,\
    \ key);\n    }\n\n    T* upper_bound_impl(node* t, T key) {\n        if (!t) return\
    \ nullptr;\n        if (key < t->key) {\n            T* res = upper_bound_impl(t->l,\
    \ key);\n            return res ? res : &t->key;\n        }\n        return upper_bound_impl(t->r,\
    \ key);\n    }\n\n   public:\n    treap() : root(nullptr) {\n        srand(time(NULL));\n\
    \    }\n\n    void insert(T key) {\n        insert(root, new node(key));\n   \
    \ }\n\n    void erase(T key) {\n        erase(root, key);\n    }\n\n    T find_by_order(int\
    \ k) {\n        return find_by_order_impl(root, k);\n    }\n\n    int order_of_key(T\
    \ key) {\n        return order_of_key_impl(root, key);\n    }\n\n    T* lower_bound(T\
    \ key) {\n        return lower_bound_impl(root, key);\n    }\n\n    T* upper_bound(T\
    \ key) {\n        return upper_bound_impl(root, key);\n    }\n\n    int size()\
    \ {\n        return count(root);\n    }\n};\n\n}  // namespace m1une\n\n\n\n/**\n\
    \ * @brief Treap\n */\n"
  code: "#ifndef M1UNE_TREAP_HPP\n#define M1UNE_TREAP_HPP 1\n\n#include <algorithm>\n\
    #include <iostream>\n#include <random>\n\nnamespace m1une {\n\ntemplate <typename\
    \ T>\nstruct treap {\n   private:\n    struct node {\n        T key;\n       \
    \ int priority;\n        node *l, *r;\n        int count;\n\n        node(T key)\n\
    \            : key(key), priority(rand()), l(nullptr), r(nullptr), count(1) {}\n\
    \    };\n\n    node* root;\n\n    int count(node* t) {\n        return t ? t->count\
    \ : 0;\n    }\n\n    void update_count(node* t) {\n        if (t) {\n        \
    \    t->count = 1 + count(t->l) + count(t->r);\n        }\n    }\n\n    // Splitting\
    \ the treap\n    void split(node* t, T key, node*& l, node*& r) {\n        if\
    \ (!t) {\n            l = r = nullptr;\n            return;\n        }\n     \
    \   if (key < t->key) {\n            split(t->l, key, l, t->l);\n            r\
    \ = t;\n        } else {\n            split(t->r, key, t->r, r);\n           \
    \ l = t;\n        }\n        update_count(t);\n    }\n\n    // Merging two treaps\n\
    \    node* merge(node* l, node* r) {\n        if (!l || !r) {\n            return\
    \ l ? l : r;\n        }\n        if (l->priority > r->priority) {\n          \
    \  l->r = merge(l->r, r);\n            update_count(l);\n            return l;\n\
    \        } else {\n            r->l = merge(l, r->l);\n            update_count(r);\n\
    \            return r;\n        }\n    }\n\n    // Inserting a key\n    void insert(node*&\
    \ t, node* item) {\n        if (!t) {\n            t = item;\n            return;\n\
    \        }\n        if (item->priority > t->priority) {\n            split(t,\
    \ item->key, item->l, item->r);\n            t = item;\n        } else {\n   \
    \         insert(item->key < t->key ? t->l : t->r, item);\n        }\n       \
    \ update_count(t);\n    }\n\n    // Erasing a key\n    void erase(node*& t, T\
    \ key) {\n        if (!t) {\n            return;\n        }\n        if (t->key\
    \ == key) {\n            node* temp = t;\n            t = merge(t->l, t->r);\n\
    \            delete temp;\n        } else {\n            erase(key < t->key ?\
    \ t->l : t->r, key);\n        }\n        update_count(t);\n    }\n\n    // Find\
    \ the k-th element\n    T find_by_order_impl(node* t, int k) {\n        if (!t)\
    \ return T();\n        int left_count = count(t->l);\n        if (k < left_count)\
    \ return find_by_order_impl(t->l, k);\n        if (k == left_count) return t->key;\n\
    \        return find_by_order_impl(t->r, k - left_count - 1);\n    }\n\n    //\
    \ Count elements less than key\n    int order_of_key_impl(node* t, T key) {\n\
    \        if (!t) return 0;\n        if (key <= t->key) return order_of_key_impl(t->l,\
    \ key);\n        return count(t->l) + 1 + order_of_key_impl(t->r, key);\n    }\n\
    \n    T* lower_bound_impl(node* t, T key) {\n        if (!t) return nullptr;\n\
    \        if (key <= t->key) {\n            T* res = lower_bound_impl(t->l, key);\n\
    \            return res ? res : &t->key;\n        }\n        return lower_bound_impl(t->r,\
    \ key);\n    }\n\n    T* upper_bound_impl(node* t, T key) {\n        if (!t) return\
    \ nullptr;\n        if (key < t->key) {\n            T* res = upper_bound_impl(t->l,\
    \ key);\n            return res ? res : &t->key;\n        }\n        return upper_bound_impl(t->r,\
    \ key);\n    }\n\n   public:\n    treap() : root(nullptr) {\n        srand(time(NULL));\n\
    \    }\n\n    void insert(T key) {\n        insert(root, new node(key));\n   \
    \ }\n\n    void erase(T key) {\n        erase(root, key);\n    }\n\n    T find_by_order(int\
    \ k) {\n        return find_by_order_impl(root, k);\n    }\n\n    int order_of_key(T\
    \ key) {\n        return order_of_key_impl(root, key);\n    }\n\n    T* lower_bound(T\
    \ key) {\n        return lower_bound_impl(root, key);\n    }\n\n    T* upper_bound(T\
    \ key) {\n        return upper_bound_impl(root, key);\n    }\n\n    int size()\
    \ {\n        return count(root);\n    }\n};\n\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_TREAP_HPP\n\n/**\n * @brief Treap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data-structure/treap.hpp
  requiredBy: []
  timestamp: '2025-09-25 04:49:25+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data-structure/treap.hpp
layout: document
redirect_from:
- /library/data-structure/treap.hpp
- /library/data-structure/treap.hpp.html
title: Treap
---
