#ifndef M1UNE_PERSISTENT_TREAP_HPP
#define M1UNE_PERSISTENT_TREAP_HPP 1

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <random>

namespace m1une {

template <typename T>
struct persistent_treap {
   private:
    struct node {
        T key;
        int priority;
        std::shared_ptr<node> l, r;
        int count;

        node(T key)
            : key(key), priority(rand()), l(nullptr), r(nullptr), count(1) {}
    };

    std::shared_ptr<node> root;

    int count(std::shared_ptr<node> t) {
        return t ? t->count : 0;
    }

    void update_count(std::shared_ptr<node> t) {
        if (t) {
            t->count = 1 + count(t->l) + count(t->r);
        }
    }

    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>& l,
               std::shared_ptr<node>& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (key < t->key) {
            auto new_node = std::make_shared<node>(*t);
            split(new_node->l, key, l, new_node->l);
            r = new_node;
            update_count(r);
        } else {
            auto new_node = std::make_shared<node>(*t);
            split(new_node->r, key, new_node->r, r);
            l = new_node;
            update_count(l);
        }
    }

    std::shared_ptr<node> merge(std::shared_ptr<node> l,
                                std::shared_ptr<node> r) {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            auto new_node = std::make_shared<node>(*l);
            new_node->r = merge(new_node->r, r);
            update_count(new_node);
            return new_node;
        } else {
            auto new_node = std::make_shared<node>(*r);
            new_node->l = merge(l, new_node->l);
            update_count(new_node);
            return new_node;
        }
    }

    std::shared_ptr<node> insert_impl(std::shared_ptr<node> t,
                                      std::shared_ptr<node> item) {
        if (!t) return item;
        if (item->priority > t->priority) {
            split(t, item->key, item->l, item->r);
            update_count(item);
            return item;
        }
        auto new_node = std::make_shared<node>(*t);
        if (item->key < new_node->key) {
            new_node->l = insert_impl(new_node->l, item);
        } else {
            new_node->r = insert_impl(new_node->r, item);
        }
        update_count(new_node);
        return new_node;
    }

    std::shared_ptr<node> erase_impl(std::shared_ptr<node> t, T key) {
        if (!t) return nullptr;
        if (t->key == key) return merge(t->l, t->r);
        auto new_node = std::make_shared<node>(*t);
        if (key < new_node->key) {
            new_node->l = erase_impl(new_node->l, key);
        } else {
            new_node->r = erase_impl(new_node->r, key);
        }
        update_count(new_node);
        return new_node;
    }

    T find_by_order_impl(std::shared_ptr<node> t, int k) {
        if (!t) return T();
        int left_count = count(t->l);
        if (k < left_count) return find_by_order_impl(t->l, k);
        if (k == left_count) return t->key;
        return find_by_order_impl(t->r, k - left_count - 1);
    }

    int order_of_key_impl(std::shared_ptr<node> t, T key) {
        if (!t) return 0;
        if (key <= t->key) return order_of_key_impl(t->l, key);
        return count(t->l) + 1 + order_of_key_impl(t->r, key);
    }

    std::optional<T> lower_bound_impl(std::shared_ptr<node> t, T key) {
        if (!t) return std::nullopt;
        if (key <= t->key) {
            auto res = lower_bound_impl(t->l, key);
            return res.has_value() ? res : t->key;
        }
        return lower_bound_impl(t->r, key);
    }

    std::optional<T> upper_bound_impl(std::shared_ptr<node> t, T key) {
        if (!t) return std::nullopt;
        if (key < t->key) {
            auto res = upper_bound_impl(t->l, key);
            return res.has_value() ? res : t->key;
        }
        return upper_bound_impl(t->r, key);
    }

   public:
    persistent_treap() : root(nullptr) {
        srand(time(NULL));
    }

    persistent_treap(std::shared_ptr<node> root) : root(root) {}

    persistent_treap insert(T key) {
        return persistent_treap(insert_impl(root, std::make_shared<node>(key)));
    }

    persistent_treap erase(T key) {
        return persistent_treap(erase_impl(root, key));
    }

    T find_by_order(int k) {
        return find_by_order_impl(root, k);
    }

    int order_of_key(T key) {
        return order_of_key_impl(root, key);
    }

    std::optional<T> lower_bound(T key) {
        return lower_bound_impl(root, key);
    }

    std::optional<T> upper_bound(T key) {
        return upper_bound_impl(root, key);
    }

    int size() {
        return count(root);
    }
};

}  // namespace m1une
#endif  // M1UNE_PERSISTENT_TREAP_HPP

/**
 * @brief Persistent Treap
 */
