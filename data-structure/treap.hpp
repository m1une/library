#ifndef M1UNE_TREAP_HPP
#define M1UNE_TREAP_HPP 1

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

namespace m1une {

template <typename T>
struct treap {
   private:
    struct node {
        T _key;
        int _priority;
        node *_l, *_r;
        int _count;

        node(T key)
            : _key(key),
              _priority(rand()),
              _l(nullptr),
              _r(nullptr),
              _count(1) {}
    };

    node* _root;

    int count(node* t) {
        return t ? t->_count : 0;
    }

    void update_count(node* t) {
        if (t) {
            t->_count = 1 + count(t->_l) + count(t->_r);
        }
    }

    void split(node* t, T key, node*& l, node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (key < t->_key) {
            split(t->_l, key, l, t->_l);
            r = t;
        } else {
            split(t->_r, key, t->_r, r);
            l = t;
        }
        update_count(t);
    }

    node* merge(node* l, node* r) {
        if (!l || !r) {
            return l ? l : r;
        }
        if (l->_priority > r->_priority) {
            l->_r = merge(l->_r, r);
            update_count(l);
            return l;
        } else {
            r->_l = merge(l, r->_l);
            update_count(r);
            return r;
        }
    }

    void insert_impl(node*& t, node* item) {
        if (!t) {
            t = item;
            return;
        }
        if (item->_priority > t->_priority) {
            split(t, item->_key, item->_l, item->_r);
            t = item;
        } else {
            insert_impl(item->_key < t->_key ? t->_l : t->_r, item);
        }
        update_count(t);
    }

    void erase_impl(node*& t, T key) {
        if (!t) {
            return;
        }
        if (t->_key == key) {
            node* temp = t;
            t = merge(t->_l, t->_r);
            delete temp;
        } else {
            erase_impl(key < t->_key ? t->_l : t->_r, key);
        }
        update_count(t);
    }

    bool contains_impl(node* t, T key) {
        if (!t) return false;
        if (t->_key == key) return true;
        if (key < t->_key) {
            return contains_impl(t->_l, key);
        } else {
            return contains_impl(t->_r, key);
        }
    }

    T find_by_order_impl(node* t, int k) {
        if (!t) return T();  // Should not happen with valid k
        int left_count = count(t->_l);
        if (k < left_count) return find_by_order_impl(t->_l, k);
        if (k == left_count) return t->_key;
        return find_by_order_impl(t->_r, k - left_count - 1);
    }

    int order_of_key_impl(node* t, T key) {
        if (!t) return 0;
        if (key <= t->_key) return order_of_key_impl(t->_l, key);
        return count(t->_l) + 1 + order_of_key_impl(t->_r, key);
    }

    T* lower_bound_impl(node* t, T key) {
        if (!t) return nullptr;
        if (key <= t->_key) {
            T* res = lower_bound_impl(t->_l, key);
            return res ? res : &t->_key;
        }
        return lower_bound_impl(t->_r, key);
    }

    T* upper_bound_impl(node* t, T key) {
        if (!t) return nullptr;
        if (key < t->_key) {
            T* res = upper_bound_impl(t->_l, key);
            return res ? res : &t->_key;
        }
        return upper_bound_impl(t->_r, key);
    }

   public:
    treap() : _root(nullptr) {
        srand(time(NULL));
    }

    void insert(T key) {
        insert_impl(_root, new node(key));
    }

    void erase(T key) {
        erase_impl(_root, key);
    }

    bool contains(T key) {
        return contains_impl(_root, key);
    }

    T find_by_order(int k) {
        return find_by_order_impl(_root, k);
    }

    int order_of_key(T key) {
        return order_of_key_impl(_root, key);
    }

    T* lower_bound(T key) {
        return lower_bound_impl(_root, key);
    }

    T* upper_bound(T key) {
        return upper_bound_impl(_root, key);
    }

    int size() {
        return count(_root);
    }
};

}  // namespace m1une
#endif  // M1UNE_TREAP_HPP
