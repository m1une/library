#ifndef M1UNE_TREAP_HPP
#define M1UNE_TREAP_HPP 1

#include <algorithm>
#include <iostream>
#include <random>

namespace m1une {

template <typename T>
struct treap {
   private:
    struct node {
        T key;
        int priority;
        node *l, *r;
        int count;

        node(T key)
            : key(key), priority(rand()), l(nullptr), r(nullptr), count(1) {}
    };

    node* root;

    int count(node* t) {
        return t ? t->count : 0;
    }

    void update_count(node* t) {
        if (t) {
            t->count = 1 + count(t->l) + count(t->r);
        }
    }

    // Splitting the treap
    void split(node* t, T key, node*& l, node*& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (key < t->key) {
            split(t->l, key, l, t->l);
            r = t;
        } else {
            split(t->r, key, t->r, r);
            l = t;
        }
        update_count(t);
    }

    // Merging two treaps
    node* merge(node* l, node* r) {
        if (!l || !r) {
            return l ? l : r;
        }
        if (l->priority > r->priority) {
            l->r = merge(l->r, r);
            update_count(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update_count(r);
            return r;
        }
    }

    // Inserting a key
    void insert(node*& t, node* item) {
        if (!t) {
            t = item;
            return;
        }
        if (item->priority > t->priority) {
            split(t, item->key, item->l, item->r);
            t = item;
        } else {
            insert(item->key < t->key ? t->l : t->r, item);
        }
        update_count(t);
    }

    // Erasing a key
    void erase(node*& t, T key) {
        if (!t) {
            return;
        }
        if (t->key == key) {
            node* temp = t;
            t = merge(t->l, t->r);
            delete temp;
        } else {
            erase(key < t->key ? t->l : t->r, key);
        }
        update_count(t);
    }

    // Find the k-th element
    T find_by_order_impl(node* t, int k) {
        if (!t) return T();
        int left_count = count(t->l);
        if (k < left_count) return find_by_order_impl(t->l, k);
        if (k == left_count) return t->key;
        return find_by_order_impl(t->r, k - left_count - 1);
    }

    // Count elements less than key
    int order_of_key_impl(node* t, T key) {
        if (!t) return 0;
        if (key <= t->key) return order_of_key_impl(t->l, key);
        return count(t->l) + 1 + order_of_key_impl(t->r, key);
    }

    T* lower_bound_impl(node* t, T key) {
        if (!t) return nullptr;
        if (key <= t->key) {
            T* res = lower_bound_impl(t->l, key);
            return res ? res : &t->key;
        }
        return lower_bound_impl(t->r, key);
    }

    T* upper_bound_impl(node* t, T key) {
        if (!t) return nullptr;
        if (key < t->key) {
            T* res = upper_bound_impl(t->l, key);
            return res ? res : &t->key;
        }
        return upper_bound_impl(t->r, key);
    }

   public:
    treap() : root(nullptr) {
        srand(time(NULL));
    }

    void insert(T key) {
        insert(root, new node(key));
    }

    void erase(T key) {
        erase(root, key);
    }

    T find_by_order(int k) {
        return find_by_order_impl(root, k);
    }

    int order_of_key(T key) {
        return order_of_key_impl(root, key);
    }

    T* lower_bound(T key) {
        return lower_bound_impl(root, key);
    }

    T* upper_bound(T key) {
        return upper_bound_impl(root, key);
    }

    int size() {
        return count(root);
    }
};

}  // namespace m1une

#endif  // M1UNE_TREAP_HPP

/**
 * @brief Treap
 */
