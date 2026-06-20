#ifndef M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP
#define M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <memory>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/segtree/dynamic_segtree_common.hpp"
#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

// A persistent sparse segment tree over an integral half-open interval.
template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct PersistentDynamicSegtree {
    using T = typename Monoid::value_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T val;
        int left;
        int right;

        explicit Node(T value)
            : val(std::move(value)), left(0), right(0) {}
    };

    struct Config {
        detail::UniformMonoidDomain<Monoid, Index> domain;

        Config(Index left, Index right, T initial_value)
            : domain(left, right, std::move(initial_value)) {}
    };

    std::shared_ptr<const Config> _config;
    std::shared_ptr<std::vector<Node>> _pool;
    int _root;

    PersistentDynamicSegtree(
        std::shared_ptr<const Config> config,
        std::shared_ptr<std::vector<Node>> pool,
        int root
    ) : _config(std::move(config)), _pool(std::move(pool)), _root(root) {}

    int new_node(T value) const {
        assert(_pool->size() < std::size_t(std::numeric_limits<int>::max()));
        _pool->emplace_back(std::move(value));
        return int(_pool->size()) - 1;
    }

    const T& value(int t, Index left, Index right, int depth) const {
        if (t) return (*_pool)[t].val;
        return _config->domain.default_product(depth, left, right);
    }

    int set_node(int t, Index left, Index right, int depth, Index p, T x) const {
        Index middle = std::midpoint(left, right);
        if (middle == left) return new_node(std::move(x));

        int left_child = t ? (*_pool)[t].left : 0;
        int right_child = t ? (*_pool)[t].right : 0;
        if (p < middle) {
            left_child = set_node(
                left_child,
                left,
                middle,
                depth + 1,
                p,
                std::move(x)
            );
        } else {
            right_child = set_node(
                right_child,
                middle,
                right,
                depth + 1,
                p,
                std::move(x)
            );
        }

        int result = new_node(Monoid::op(
            value(left_child, left, middle, depth + 1),
            value(right_child, middle, right, depth + 1)
        ));
        (*_pool)[result].left = left_child;
        (*_pool)[result].right = right_child;
        return result;
    }

    T prod_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_left,
        Index query_right
    ) const {
        if (query_right <= left || right <= query_left) return Monoid::id();
        if (query_left <= left && right <= query_right) {
            return value(t, left, right, depth);
        }
        Index middle = std::midpoint(left, right);
        return Monoid::op(
            prod_node(
                t ? (*_pool)[t].left : 0,
                left,
                middle,
                depth + 1,
                query_left,
                query_right
            ),
            prod_node(
                t ? (*_pool)[t].right : 0,
                middle,
                right,
                depth + 1,
                query_left,
                query_right
            )
        );
    }

    template <class F>
    Index max_right_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_left,
        T& product,
        F& predicate
    ) const {
        if (right <= query_left) return right;
        if (query_left <= left) {
            T next = Monoid::op(product, value(t, left, right, depth));
            if (predicate(next)) {
                product = std::move(next);
                return right;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return left;
        }

        Index middle = std::midpoint(left, right);
        Index result = max_right_node(
            t ? (*_pool)[t].left : 0,
            left,
            middle,
            depth + 1,
            query_left,
            product,
            predicate
        );
        if (result < middle) return result;
        return max_right_node(
            t ? (*_pool)[t].right : 0,
            middle,
            right,
            depth + 1,
            query_left,
            product,
            predicate
        );
    }

    template <class F>
    Index min_left_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_right,
        T& product,
        F& predicate
    ) const {
        if (query_right <= left) return left;
        if (right <= query_right) {
            T next = Monoid::op(value(t, left, right, depth), product);
            if (predicate(next)) {
                product = std::move(next);
                return left;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return right;
        }

        Index middle = std::midpoint(left, right);
        Index result = min_left_node(
            t ? (*_pool)[t].right : 0,
            middle,
            right,
            depth + 1,
            query_right,
            product,
            predicate
        );
        if (middle < result) return result;
        return min_left_node(
            t ? (*_pool)[t].left : 0,
            left,
            middle,
            depth + 1,
            query_right,
            product,
            predicate
        );
    }

   public:
    PersistentDynamicSegtree()
        : PersistentDynamicSegtree(Index(0), Index(0), Monoid::id()) {}

    explicit PersistentDynamicSegtree(Index n)
        : PersistentDynamicSegtree(Index(0), n, Monoid::id()) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }

    PersistentDynamicSegtree(Index left, Index right)
        : PersistentDynamicSegtree(left, right, Monoid::id()) {}

    PersistentDynamicSegtree(Index left, Index right, T initial_value)
        : _config(std::make_shared<Config>(left, right, std::move(initial_value))),
          _pool(std::make_shared<std::vector<Node>>()),
          _root(0) {
        _pool->emplace_back(Monoid::id());
    }

    size_type size() const {
        return _config->domain.size();
    }

    bool empty() const {
        return _config->domain.empty();
    }

    Index left_bound() const {
        return _config->domain.left_bound();
    }

    Index right_bound() const {
        return _config->domain.right_bound();
    }

    const T& initial_value() const {
        return _config->domain.initial_value();
    }

    void reserve(std::size_t node_capacity) const {
        assert(node_capacity < std::numeric_limits<std::size_t>::max());
        _pool->reserve(node_capacity + 1);
    }

    std::size_t node_count() const {
        return _pool->size() - 1;
    }

    PersistentDynamicSegtree set(Index p, T x) const {
        assert(left_bound() <= p && p < right_bound());
        return PersistentDynamicSegtree(
            _config,
            _pool,
            set_node(_root, left_bound(), right_bound(), 0, p, std::move(x))
        );
    }

    T get(Index p) const {
        assert(left_bound() <= p && p < right_bound());
        int t = _root;
        Index left = left_bound();
        Index right = right_bound();

        while (t) {
            Index middle = std::midpoint(left, right);
            if (middle == left) return (*_pool)[t].val;
            if (p < middle) {
                t = (*_pool)[t].left;
                right = middle;
            } else {
                t = (*_pool)[t].right;
                left = middle;
            }
        }
        return initial_value();
    }

    T operator[](Index p) const {
        return get(p);
    }

    T prod(Index left, Index right) const {
        assert(left_bound() <= left && left <= right && right <= right_bound());
        if (left == right) return Monoid::id();
        return prod_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            left,
            right
        );
    }

    T all_prod() const {
        return value(_root, left_bound(), right_bound(), 0);
    }

    template <class F>
    Index max_right(Index left, F predicate) const {
        assert(left_bound() <= left && left <= right_bound());
        assert(predicate(Monoid::id()));
        if (left == right_bound()) return right_bound();
        T product = Monoid::id();
        return max_right_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            left,
            product,
            predicate
        );
    }

    template <class F>
    Index min_left(Index right, F predicate) const {
        assert(left_bound() <= right && right <= right_bound());
        assert(predicate(Monoid::id()));
        if (right == left_bound()) return left_bound();
        T product = Monoid::id();
        return min_left_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            right,
            product,
            predicate
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DYNAMIC_SEGTREE_HPP
