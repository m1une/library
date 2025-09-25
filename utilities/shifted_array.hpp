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
        T _key;
        int _priority;
        std::shared_ptr<node> _l, _r;
        int _count;

        node(T key)
            : _key(key),
              _priority(rand()),
              _l(nullptr),
              _r(nullptr),
              _count(1) {}
    };

    std::shared_ptr<node> _root;

    int count(std::shared_ptr<node> t) {
        return t ? t->_count : 0;
    }

    void update_count(std::shared_ptr<node> t) {
        if (t) {
            t->_count = 1 + count(t->_l) + count(t->_r);
        }
    }

    void split(std::shared_ptr<node> t, T key, std::shared_ptr<node>& l,
               std::shared_ptr<node>& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (key < t->_key) {
            auto new_node = std::make_shared<node>(*t);
            split(new_node->_l, key, l, new_node->_l);
            r = new_node;
            update_count(r);
        } else {
            auto new_node = std::make_shared<node>(*t);
            split(new_node->_r, key, new_node->_r, r);
            l = new_node;
            update_count(l);
        }
    }

    std::shared_ptr<node> merge(std::shared_ptr<node> l,
                                std::shared_ptr<node> r) {
        if (!l || !r) return l ? l : r;
        if (l->_priority > r->_priority) {
            auto new_node = std::make_shared<node>(*l);
            new_node->_r = merge(new_node->_r, r);
            update_count(new_node);
            return new_node;
        } else {
            auto new_node = std::make_shared<node>(*r);
            new_node->_l = merge(l, new_node->_l);
            update_count(new_node);
            return new_node;
        }
    }

    std::shared_ptr<node> insert_impl(std::shared_ptr<node> t,
                                      std::shared_ptr<node> item) {
        if (!t) return item;
        if (item->_priority > t->_priority) {
            split(t, item->_key, item->_l, item->_r);
            update_count(item);
            return item;
        }
        auto new_node = std::make_shared<node>(*t);
        if (item->_key < new_node->_key) {
            new_node->_l = insert_impl(new_node->_l, item);
        } else {
            new_node->_r = insert_impl(new_node->_r, item);
        }
        update_count(new_node);
        return new_node;
    }

    std::shared_ptr<node> erase_impl(std::shared_ptr<node> t, T key) {
        if (!t) return nullptr;
        if (t->_key == key) return merge(t->_l, t->_r);
        auto new_node = std::make_shared<node>(*t);
        if (key < new_node->_key) {
            new_node->_l = erase_impl(new_node->_l, key);
        } else {
            new_node->_r = erase_impl(new_node->_r, key);
        }
        update_count(new_node);
        return new_node;
    }

    T find_by_order_impl(std::shared_ptr<node> t, int k) {
        if (!t) return T();
        int left_count = count(t->_l);
        if (k < left_count) return find_by_order_impl(t->_l, k);
        if (k == left_count) return t->_key;
        return find_by_order_impl(t->_r, k - left_count - 1);
    }

    int order_of_key_impl(std::shared_ptr<node> t, T key) {
        if (!t) return 0;
        if (key <= t->_key) return order_of_key_impl(t->_l, key);
        return count(t->_l) + 1 + order_of_key_impl(t->_r, key);
    }

    std::optional<T> lower_bound_impl(std::shared_ptr<node> t, T key) {
        if (!t) return std::nullopt;
        if (key <= t->_key) {
            auto res = lower_bound_impl(t->_l, key);
            return res.has_value() ? res : t->_key;
        }
        return lower_bound_impl(t->_r, key);
    }

    std::optional<T> upper_bound_impl(std::shared_ptr<node> t, T key) {
        if (!t) return std::nullopt;
        if (key < t->_key) {
            auto res = upper_bound_impl(t->_l, key);
            return res.has_value() ? res : t->_key;
        }
        return upper_bound_impl(t->_r, key);
    }

   public:
    persistent_treap() : _root(nullptr) {
        srand(time(NULL));
    }

    persistent_treap(std::shared_ptr<node> root) : _root(root) {}

    persistent_treap insert(T key) {
        return persistent_treap(
            insert_impl(_root, std::make_shared<node>(key)));
    }

    persistent_treap erase(T key) {
        return persistent_treap(erase_impl(_root, key));
    }

    T find_by_order(int k) {
        return find_by_order_impl(_root, k);
    }

    int order_of_key(T key) {
        return order_of_key_impl(_root, key);
    }

    std::optional<T> lower_bound(T key) {
        return lower_bound_impl(_root, key);
    }

    std::optional<T> upper_bound(T key) {
        return upper_bound_impl(_root, key);
    }

    int size() {
        return count(_root);
    }
};

}  // namespace m1une

#endif  // M1UNE_PERSISTENT_TREAP_HPP

/**
 * @brief Persistent Treap
 */
