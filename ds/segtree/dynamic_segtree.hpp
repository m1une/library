#ifndef M1UNE_DYNAMIC_SEGTREE_HPP
#define M1UNE_DYNAMIC_SEGTREE_HPP 1

#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#include "dynamic_segtree_common.hpp"
#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A sparse segment tree over an integral half-open interval.
// Nodes are allocated from a contiguous pool only when a position is touched.
template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct DynamicSegtree {
    using T = typename Monoid::value_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T val;
        int left;
        int right;

        Node() : val(Monoid::id()), left(0), right(0) {}
    };

    static constexpr int path_capacity = std::numeric_limits<size_type>::digits + 1;

    detail::UniformMonoidDomain<Monoid, Index> _domain;
    int _root;
    std::vector<Node> _nodes;

    int new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

    const T& value(int t, Index left, Index right, int depth) const {
        if (t) return _nodes[t].val;
        return _domain.default_product(depth, left, right);
    }

    void update(int t, Index left, Index right, int depth) {
        Index middle = std::midpoint(left, right);
        _nodes[t].val = Monoid::op(
            value(_nodes[t].left, left, middle, depth + 1),
            value(_nodes[t].right, middle, right, depth + 1)
        );
    }

    T prod_node(int t, Index l, Index r, int depth, Index ql, Index qr) const {
        if (qr <= l || r <= ql) return Monoid::id();
        if (ql <= l && r <= qr) return value(t, l, r, depth);
        Index m = std::midpoint(l, r);
        return Monoid::op(
            prod_node(t ? _nodes[t].left : 0, l, m, depth + 1, ql, qr),
            prod_node(t ? _nodes[t].right : 0, m, r, depth + 1, ql, qr)
        );
    }

    template <class F>
    Index max_right_node(
        int t,
        Index l,
        Index r,
        int depth,
        Index ql,
        T& sm,
        F& f
    ) const {
        if (r <= ql) return r;
        if (ql <= l) {
            T next = Monoid::op(sm, value(t, l, r, depth));
            if (f(next)) {
                sm = std::move(next);
                return r;
            }
            Index m = std::midpoint(l, r);
            if (m == l) return l;
        }
        Index m = std::midpoint(l, r);
        Index res = max_right_node(
            t ? _nodes[t].left : 0,
            l,
            m,
            depth + 1,
            ql,
            sm,
            f
        );
        if (res < m) return res;
        return max_right_node(
            t ? _nodes[t].right : 0,
            m,
            r,
            depth + 1,
            ql,
            sm,
            f
        );
    }

    template <class F>
    Index min_left_node(
        int t,
        Index l,
        Index r,
        int depth,
        Index qr,
        T& sm,
        F& f
    ) const {
        if (qr <= l) return l;
        if (r <= qr) {
            T next = Monoid::op(value(t, l, r, depth), sm);
            if (f(next)) {
                sm = std::move(next);
                return l;
            }
            Index m = std::midpoint(l, r);
            if (m == l) return r;
        }
        Index m = std::midpoint(l, r);
        Index res = min_left_node(
            t ? _nodes[t].right : 0,
            m,
            r,
            depth + 1,
            qr,
            sm,
            f
        );
        if (m < res) return res;
        return min_left_node(
            t ? _nodes[t].left : 0,
            l,
            m,
            depth + 1,
            qr,
            sm,
            f
        );
    }

   public:
    // Constructs an empty tree over [0, 0).
    DynamicSegtree() : DynamicSegtree(Index(0), Index(0)) {}

    // Constructs a tree over [0, n).
    explicit DynamicSegtree(Index n) : DynamicSegtree(Index(0), n) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }

    // Constructs a tree over [left, right).
    DynamicSegtree(Index left, Index right)
        : DynamicSegtree(left, right, Monoid::id()) {}

    // Constructs a tree over [left, right) with every coordinate initialized to
    // `initial_value`.
    DynamicSegtree(Index left, Index right, T initial_value)
        : _domain(left, right, std::move(initial_value)), _root(0), _nodes(1) {}

    // Returns the number of coordinates in the domain.
    size_type size() const {
        return _domain.size();
    }

    // Returns whether the coordinate domain is empty.
    bool empty() const {
        return _domain.empty();
    }

    // Returns the left endpoint of the coordinate domain.
    Index left_bound() const {
        return _domain.left_bound();
    }

    // Returns the right endpoint of the coordinate domain.
    Index right_bound() const {
        return _domain.right_bound();
    }

    // Returns the value assigned to untouched coordinates.
    const T& initial_value() const {
        return _domain.initial_value();
    }

    // Reserves space for `node_capacity` allocated nodes.
    void reserve(std::size_t node_capacity) {
        assert(node_capacity < std::numeric_limits<std::size_t>::max());
        _nodes.reserve(node_capacity + 1);
    }

    // Returns the number of allocated nodes, excluding the sentinel.
    std::size_t node_count() const {
        return _nodes.size() - 1;
    }

    // Restores every coordinate to the initial value while preserving capacity.
    void clear() {
        _root = 0;
        _nodes.resize(1);
    }

    // Sets the value at coordinate `p` to `x`.
    void set(Index p, T x) {
        assert(left_bound() <= p && p < right_bound());
        if (!_root) _root = new_node();

        std::array<int, path_capacity> path;
        std::array<Index, path_capacity> path_left;
        std::array<Index, path_capacity> path_right;
        int depth = 0;
        int t = _root;
        Index l = left_bound();
        Index r = right_bound();

        while (true) {
            assert(depth < path_capacity);
            path[depth] = t;
            path_left[depth] = l;
            path_right[depth] = r;
            depth++;
            Index m = std::midpoint(l, r);
            if (m == l) break;

            if (p < m) {
                int child = _nodes[t].left;
                if (!child) {
                    child = new_node();
                    _nodes[t].left = child;
                }
                t = child;
                r = m;
            } else {
                int child = _nodes[t].right;
                if (!child) {
                    child = new_node();
                    _nodes[t].right = child;
                }
                t = child;
                l = m;
            }
        }

        _nodes[t].val = std::move(x);
        for (int i = depth - 2; i >= 0; i--) {
            update(path[i], path_left[i], path_right[i], i);
        }
    }

    // Returns the value at coordinate `p`.
    T get(Index p) const {
        assert(left_bound() <= p && p < right_bound());
        int t = _root;
        Index l = left_bound();
        Index r = right_bound();
        int depth = 0;

        while (t) {
            Index m = std::midpoint(l, r);
            if (m == l) return value(t, l, r, depth);
            if (p < m) {
                t = _nodes[t].left;
                r = m;
            } else {
                t = _nodes[t].right;
                l = m;
            }
            depth++;
        }
        return initial_value();
    }

    // Returns the value at coordinate `p`.
    T operator[](Index p) const {
        return get(p);
    }

    // Returns the monoid product over [l, r).
    T prod(Index l, Index r) const {
        assert(left_bound() <= l && l <= r && r <= right_bound());
        if (l == r) return Monoid::id();
        return prod_node(_root, left_bound(), right_bound(), 0, l, r);
    }

    // Returns the monoid product over the entire coordinate domain.
    T all_prod() const {
        return value(_root, left_bound(), right_bound(), 0);
    }

    // Finds the largest r such that f(prod(l, r)) is true.
    template <class F>
    Index max_right(Index l, F f) const {
        assert(left_bound() <= l && l <= right_bound());
        assert(f(Monoid::id()));
        if (l == right_bound()) return right_bound();
        T sm = Monoid::id();
        return max_right_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            l,
            sm,
            f
        );
    }

    // Finds the smallest l such that f(prod(l, r)) is true.
    template <class F>
    Index min_left(Index r, F f) const {
        assert(left_bound() <= r && r <= right_bound());
        assert(f(Monoid::id()));
        if (r == left_bound()) return left_bound();
        T sm = Monoid::id();
        return min_left_node(
            _root,
            left_bound(),
            right_bound(),
            0,
            r,
            sm,
            f
        );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_SEGTREE_HPP
