#ifndef M1UNE_DYNAMIC_LAZY_SEGTREE_HPP
#define M1UNE_DYNAMIC_LAZY_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "dynamic_segtree_common.hpp"

namespace m1une {
namespace ds {

// A sparse lazy segment tree over an integral half-open interval.
template <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral Index = long long>
requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct DynamicLazySegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T val;
        F lazy;
        int left;
        int right;
        bool has_lazy;

        explicit Node(T value)
            : val(std::move(value)),
              lazy(ActedMonoid::op_id()),
              left(0),
              right(0),
              has_lazy(false) {}
    };

    detail::UniformMonoidDomain<ActedMonoid, Index> _domain;
    int _root;
    std::vector<Node> _nodes;

    int new_node(Index left, Index right, int depth) {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back(_domain.default_product(depth, left, right));
        return int(_nodes.size()) - 1;
    }

    const T& value(int t, Index left, Index right, int depth) const {
        if (t) return _nodes[t].val;
        return _domain.default_product(depth, left, right);
    }

    void all_apply(int& t, Index left, Index right, int depth, const F& f) {
        if (!t) t = new_node(left, right, depth);
        Node& node = _nodes[t];
        node.val = detail::dynamic_mapping<ActedMonoid>(f, node.val);
        if (std::midpoint(left, right) != left) {
            node.lazy = ActedMonoid::op_comp(f, node.lazy);
            node.has_lazy = true;
        }
    }

    void push(int t, Index left, Index right, int depth) {
        if (!_nodes[t].has_lazy) return;
        Index middle = std::midpoint(left, right);
        if (middle == left) return;

        F lazy = _nodes[t].lazy;
        int left_child = _nodes[t].left;
        int right_child = _nodes[t].right;
        all_apply(left_child, left, middle, depth + 1, lazy);
        all_apply(
            right_child,
            middle,
            right,
            depth + 1,
            detail::dynamic_shift<ActedMonoid>(lazy, detail::dynamic_distance(left, middle))
        );

        Node& node = _nodes[t];
        node.left = left_child;
        node.right = right_child;
        node.lazy = ActedMonoid::op_id();
        node.has_lazy = false;
    }

    void update(int t, Index left, Index right, int depth) {
        Index middle = std::midpoint(left, right);
        _nodes[t].val = ActedMonoid::op(
            value(_nodes[t].left, left, middle, depth + 1),
            value(_nodes[t].right, middle, right, depth + 1)
        );
    }

    int set_node(int t, Index left, Index right, int depth, Index p, T x) {
        if (!t) t = new_node(left, right, depth);
        Index middle = std::midpoint(left, right);
        if (middle == left) {
            Node& node = _nodes[t];
            node.val = std::move(x);
            node.lazy = ActedMonoid::op_id();
            node.has_lazy = false;
            return t;
        }

        push(t, left, right, depth);
        if (p < middle) {
            int child = set_node(_nodes[t].left, left, middle, depth + 1, p, std::move(x));
            _nodes[t].left = child;
        } else {
            int child = set_node(_nodes[t].right, middle, right, depth + 1, p, std::move(x));
            _nodes[t].right = child;
        }
        update(t, left, right, depth);
        return t;
    }

    int apply_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_left,
        Index query_right,
        const F& f
    ) {
        if (query_right <= left || right <= query_left) return t;
        if (query_left <= left && right <= query_right) {
            all_apply(
                t,
                left,
                right,
                depth,
                detail::dynamic_shift<ActedMonoid>(f, detail::dynamic_distance(query_left, left))
            );
            return t;
        }

        if (!t) t = new_node(left, right, depth);
        push(t, left, right, depth);
        Index middle = std::midpoint(left, right);
        int left_child = apply_node(_nodes[t].left, left, middle, depth + 1, query_left, query_right, f);
        int right_child = apply_node(_nodes[t].right, middle, right, depth + 1, query_left, query_right, f);
        _nodes[t].left = left_child;
        _nodes[t].right = right_child;
        update(t, left, right, depth);
        return t;
    }

    F compose_for_child(const F& inherited, int t, size_type offset) const {
        F shifted = detail::dynamic_shift<ActedMonoid>(inherited, offset);
        if (!t || !_nodes[t].has_lazy) return shifted;
        return ActedMonoid::op_comp(
            shifted,
            detail::dynamic_shift<ActedMonoid>(_nodes[t].lazy, offset)
        );
    }

    T prod_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_left,
        Index query_right,
        const F& inherited
    ) const {
        if (query_right <= left || right <= query_left) return ActedMonoid::id();
        if (query_left <= left && right <= query_right) {
            return detail::dynamic_mapping<ActedMonoid>(
                inherited,
                value(t, left, right, depth)
            );
        }
        Index middle = std::midpoint(left, right);
        return ActedMonoid::op(
            prod_node(
                t ? _nodes[t].left : 0,
                left,
                middle,
                depth + 1,
                query_left,
                query_right,
                compose_for_child(inherited, t, 0)
            ),
            prod_node(
                t ? _nodes[t].right : 0,
                middle,
                right,
                depth + 1,
                query_left,
                query_right,
                compose_for_child(inherited, t, detail::dynamic_distance(left, middle))
            )
        );
    }

    template <class G>
    Index max_right_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_left,
        T& product,
        const F& inherited,
        G& predicate
    ) const {
        if (right <= query_left) return right;
        if (query_left <= left) {
            T next = ActedMonoid::op(
                product,
                detail::dynamic_mapping<ActedMonoid>(
                    inherited,
                    value(t, left, right, depth)
                )
            );
            if (predicate(next)) {
                product = std::move(next);
                return right;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return left;
        }
        Index middle = std::midpoint(left, right);
        Index result = max_right_node(
            t ? _nodes[t].left : 0,
            left,
            middle,
            depth + 1,
            query_left,
            product,
            compose_for_child(inherited, t, 0),
            predicate
        );
        if (result < middle) return result;
        return max_right_node(
            t ? _nodes[t].right : 0,
            middle,
            right,
            depth + 1,
            query_left,
            product,
            compose_for_child(inherited, t, detail::dynamic_distance(left, middle)),
            predicate
        );
    }

    template <class G>
    Index min_left_node(
        int t,
        Index left,
        Index right,
        int depth,
        Index query_right,
        T& product,
        const F& inherited,
        G& predicate
    ) const {
        if (query_right <= left) return left;
        if (right <= query_right) {
            T next = ActedMonoid::op(
                detail::dynamic_mapping<ActedMonoid>(
                    inherited,
                    value(t, left, right, depth)
                ),
                product
            );
            if (predicate(next)) {
                product = std::move(next);
                return left;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return right;
        }
        Index middle = std::midpoint(left, right);
        Index result = min_left_node(
            t ? _nodes[t].right : 0,
            middle,
            right,
            depth + 1,
            query_right,
            product,
            compose_for_child(inherited, t, detail::dynamic_distance(left, middle)),
            predicate
        );
        if (middle < result) return result;
        return min_left_node(
            t ? _nodes[t].left : 0,
            left,
            middle,
            depth + 1,
            query_right,
            product,
            compose_for_child(inherited, t, 0),
            predicate
        );
    }

   public:
    DynamicLazySegtree()
        : DynamicLazySegtree(Index(0), Index(0), ActedMonoid::id()) {}

    explicit DynamicLazySegtree(Index n)
        : DynamicLazySegtree(Index(0), n, ActedMonoid::id()) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }

    DynamicLazySegtree(Index left, Index right)
        : DynamicLazySegtree(left, right, ActedMonoid::id()) {}

    DynamicLazySegtree(Index left, Index right, T initial_value)
        : _domain(left, right, std::move(initial_value)), _root(0) {
        _nodes.emplace_back(ActedMonoid::id());
    }

    size_type size() const {
        return _domain.size();
    }

    bool empty() const {
        return _domain.empty();
    }

    Index left_bound() const {
        return _domain.left_bound();
    }

    Index right_bound() const {
        return _domain.right_bound();
    }

    const T& initial_value() const {
        return _domain.initial_value();
    }

    void reserve(std::size_t node_capacity) {
        assert(node_capacity < std::numeric_limits<std::size_t>::max());
        _nodes.reserve(node_capacity + 1);
    }

    std::size_t node_count() const {
        return _nodes.size() - 1;
    }

    void clear() {
        _root = 0;
        _nodes.erase(_nodes.begin() + 1, _nodes.end());
    }

    void set(Index p, T x) {
        assert(left_bound() <= p && p < right_bound());
        _root = set_node(_root, left_bound(), right_bound(), 0, p, std::move(x));
    }

    T get(Index p) const {
        assert(left_bound() <= p && p < right_bound());
        return prod(p, p + 1);
    }

    T operator[](Index p) const {
        return get(p);
    }

    T prod(Index left, Index right) const {
        assert(left_bound() <= left && left <= right && right <= right_bound());
        if (left == right) return ActedMonoid::id();
        return prod_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            left,
            right,
            ActedMonoid::op_id()
        );
    }

    T all_prod() const {
        return value(_root, left_bound(), right_bound(), 0);
    }

    void apply(Index p, const F& f) {
        assert(left_bound() <= p && p < right_bound());
        apply(p, p + 1, f);
    }

    void apply(Index left, Index right, const F& f) {
        assert(left_bound() <= left && left <= right && right <= right_bound());
        if (left == right) return;
        _root = apply_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            left,
            right,
            f
        );
    }

    template <class G>
    Index max_right(Index left, G predicate) const {
        assert(left_bound() <= left && left <= right_bound());
        assert(predicate(ActedMonoid::id()));
        if (left == right_bound()) return right_bound();
        T product = ActedMonoid::id();
        return max_right_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            left,
            product,
            ActedMonoid::op_id(),
            predicate
        );
    }

    template <class G>
    Index min_left(Index right, G predicate) const {
        assert(left_bound() <= right && right <= right_bound());
        assert(predicate(ActedMonoid::id()));
        if (right == left_bound()) return left_bound();
        T product = ActedMonoid::id();
        return min_left_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            right,
            product,
            ActedMonoid::op_id(),
            predicate
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_LAZY_SEGTREE_HPP
