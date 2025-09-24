#ifndef M1UNE_TREAP_HPP
#define M1UNE_TREAP_HPP 1

#include <iostream>
#include <random>
#include <algorithm>

namespace m1une {

template <typename T>
struct treap {
private:
    struct node {
        T key;
        int priority;
        node *l, *r;
        int count;

        node(T key) : key(key), priority(rand()), l(nullptr), r(nullptr), count(1) {}
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

    int size() {
        return count(root);
    }
};

} // namespace m1une

#endif // M1UNE_TREAP_HPP