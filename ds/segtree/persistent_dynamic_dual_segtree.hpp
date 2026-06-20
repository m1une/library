#ifndef M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP
#define M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <memory>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#include "dynamic_segtree_common.hpp"
#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A persistent sparse dual segment tree over an integral half-open interval.
template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct PersistentDynamicDualSegtree {
    using T = typename Monoid::value_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T val;
        int left;
        int right;
        bool has_lazy;

        Node() : val(Monoid::id()), left(0), right(0), has_lazy(false) {}
    };

    struct Config {
        Index left;
        Index right;
        T initial_value;

        Config(Index left_bound, Index right_bound, T value)
            : left(left_bound), right(right_bound), initial_value(std::move(value)) {
            assert(left <= right);
        }
    };

    std::shared_ptr<const Config> _config;
    std::shared_ptr<std::vector<Node>> _pool;
    int _root;

    PersistentDynamicDualSegtree(
        std::shared_ptr<const Config> config,
        std::shared_ptr<std::vector<Node>> pool,
        int root
    ) : _config(std::move(config)), _pool(std::move(pool)), _root(root) {}

    int new_node() const {
        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));
        _pool->emplace_back();
        return int(_pool->size()) - 1;
    }

    int clone_or_new(int t) const {
        if (!t) return new_node();
        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));
        _pool->push_back((*_pool)[t]);
        return int(_pool->size()) - 1;
    }

    void all_apply_to_node(int t, Index left, Index right, const T& x) const {
        Node& node = (*_pool)[t];
        if (std::midpoint(left, right) == left) {
            T value = node.has_lazy ? node.val : _config->initial_value;
            node.val = Monoid::op(x, value);
            node.has_lazy = true;
        } else {
            node.val = node.has_lazy ? Monoid::op(x, node.val) : x;
            node.has_lazy = true;
        }
    }

    int all_apply_clone(int t, Index left, Index right, const T& x) const {
        int result = clone_or_new(t);
        all_apply_to_node(result, left, right, x);
        return result;
    }

    void push(int t, Index left, Index right) const {
        if (!(*_pool)[t].has_lazy) return;
        Index middle = std::midpoint(left, right);
        if (middle == left) return;

        T lazy = (*_pool)[t].val;
        int left_child = all_apply_clone((*_pool)[t].left, left, middle, lazy);
        int right_child = all_apply_clone((*_pool)[t].right, middle, right, lazy);

        Node& node = (*_pool)[t];
        node.left = left_child;
        node.right = right_child;
        node.val = Monoid::id();
        node.has_lazy = false;
    }

    int set_node(int t, Index left, Index right, Index p, T x) const {
        t = clone_or_new(t);
        Index middle = std::midpoint(left, right);
        if (middle == left) {
            Node& node = (*_pool)[t];
            node.val = std::move(x);
            node.has_lazy = true;
            return t;
        }

        push(t, left, right);
        if (p < middle) {
            int child = set_node((*_pool)[t].left, left, middle, p, std::move(x));
            (*_pool)[t].left = child;
        } else {
            int child = set_node((*_pool)[t].right, middle, right, p, std::move(x));
            (*_pool)[t].right = child;
        }
        return t;
    }

    int apply_node(
        int t,
        Index left,
        Index right,
        Index query_left,
        Index query_right,
        const T& x
    ) const {
        if (query_right <= left || right <= query_left) return t;
        if (query_left <= left && right <= query_right) {
            return all_apply_clone(t, left, right, x);
        }

        t = clone_or_new(t);
        push(t, left, right);
        Index middle = std::midpoint(left, right);
        int left_child = apply_node(
            (*_pool)[t].left,
            left,
            middle,
            query_left,
            query_right,
            x
        );
        int right_child = apply_node(
            (*_pool)[t].right,
            middle,
            right,
            query_left,
            query_right,
            x
        );
        (*_pool)[t].left = left_child;
        (*_pool)[t].right = right_child;
        return t;
    }

    T compose(const T& inherited, int t) const {
        if (!t || !(*_pool)[t].has_lazy) return inherited;
        return Monoid::op(inherited, (*_pool)[t].val);
    }

   public:
    PersistentDynamicDualSegtree()
        : PersistentDynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}

    explicit PersistentDynamicDualSegtree(Index n)
        : PersistentDynamicDualSegtree(Index(0), n, Monoid::id()) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }

    PersistentDynamicDualSegtree(Index left, Index right)
        : PersistentDynamicDualSegtree(left, right, Monoid::id()) {}

    PersistentDynamicDualSegtree(Index left, Index right, T initial_value)
        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),
          _pool(std::make_shared<std::vector<Node>>()),
          _root(0) {
        _pool->emplace_back();
    }

    size_type size() const {
        return detail::dynamic_distance(_config->left, _config->right);
    }

    bool empty() const {
        return _config->left == _config->right;
    }

    Index left_bound() const {
        return _config->left;
    }

    Index right_bound() const {
        return _config->right;
    }

    const T& initial_value() const {
        return _config->initial_value;
    }

    void reserve(std::size_t node_capacity) const {
        assert(node_capacity < std::numeric_limits<std::size_t>::max());
        _pool->reserve(node_capacity + 1);
    }

    std::size_t node_count() const {
        return _pool->size() - 1;
    }

    PersistentDynamicDualSegtree set(Index p, T x) const {
        assert(left_bound() <= p && p < right_bound());
        return PersistentDynamicDualSegtree(
            _config,
            _pool,
            set_node(_root, left_bound(), right_bound(), p, std::move(x))
        );
    }

    T get(Index p) const {
        assert(left_bound() <= p && p < right_bound());
        int t = _root;
        Index left = left_bound();
        Index right = right_bound();
        T inherited = Monoid::id();

        while (t) {
            Index middle = std::midpoint(left, right);
            if (middle == left) {
                T value = (*_pool)[t].has_lazy ? (*_pool)[t].val : initial_value();
                return Monoid::op(inherited, value);
            }
            inherited = compose(inherited, t);
            if (p < middle) {
                t = (*_pool)[t].left;
                right = middle;
            } else {
                t = (*_pool)[t].right;
                left = middle;
            }
        }
        return Monoid::op(inherited, initial_value());
    }

    T operator[](Index p) const {
        return get(p);
    }

    PersistentDynamicDualSegtree apply(Index p, const T& x) const {
        assert(left_bound() <= p && p < right_bound());
        return apply(p, p + 1, x);
    }

    PersistentDynamicDualSegtree apply(Index left, Index right, const T& x) const {
        assert(left_bound() <= left && left <= right && right <= right_bound());
        if (left == right) return *this;
        return PersistentDynamicDualSegtree(
            _config,
            _pool,
            apply_node(_root, left_bound(), right_bound(), left, right, x)
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DYNAMIC_DUAL_SEGTREE_HPP
