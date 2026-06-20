#ifndef M1UNE_DYNAMIC_DUAL_SEGTREE_HPP
#define M1UNE_DYNAMIC_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

#include "ds/segtree/dynamic_segtree_common.hpp"
#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

// A sparse dual segment tree over an integral half-open interval.
template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct DynamicDualSegtree {
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

    Index _left;
    Index _right;
    T _initial_value;
    int _root;
    std::vector<Node> _nodes;

    int new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

    void all_apply(int& t, Index left, Index right, const T& x) {
        if (!t) t = new_node();
        Node& node = _nodes[t];
        if (std::midpoint(left, right) == left) {
            T value = node.has_lazy ? node.val : _initial_value;
            node.val = Monoid::op(x, value);
            node.has_lazy = true;
        } else {
            node.val = node.has_lazy ? Monoid::op(x, node.val) : x;
            node.has_lazy = true;
        }
    }

    void push(int t, Index left, Index right) {
        if (!_nodes[t].has_lazy) return;
        Index middle = std::midpoint(left, right);
        if (middle == left) return;

        T lazy = _nodes[t].val;
        int left_child = _nodes[t].left;
        int right_child = _nodes[t].right;
        all_apply(left_child, left, middle, lazy);
        all_apply(right_child, middle, right, lazy);

        Node& node = _nodes[t];
        node.left = left_child;
        node.right = right_child;
        node.val = Monoid::id();
        node.has_lazy = false;
    }

    int set_node(int t, Index left, Index right, Index p, T x) {
        if (!t) t = new_node();
        Index middle = std::midpoint(left, right);
        if (middle == left) {
            Node& node = _nodes[t];
            node.val = std::move(x);
            node.has_lazy = true;
            return t;
        }

        push(t, left, right);
        if (p < middle) {
            int child = set_node(_nodes[t].left, left, middle, p, std::move(x));
            _nodes[t].left = child;
        } else {
            int child = set_node(_nodes[t].right, middle, right, p, std::move(x));
            _nodes[t].right = child;
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
    ) {
        if (query_right <= left || right <= query_left) return t;
        if (query_left <= left && right <= query_right) {
            all_apply(t, left, right, x);
            return t;
        }

        if (!t) t = new_node();
        push(t, left, right);
        Index middle = std::midpoint(left, right);
        int left_child = apply_node(_nodes[t].left, left, middle, query_left, query_right, x);
        int right_child = apply_node(_nodes[t].right, middle, right, query_left, query_right, x);
        _nodes[t].left = left_child;
        _nodes[t].right = right_child;
        return t;
    }

    T compose(const T& inherited, int t) const {
        if (!t || !_nodes[t].has_lazy) return inherited;
        return Monoid::op(inherited, _nodes[t].val);
    }

   public:
    DynamicDualSegtree()
        : DynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}

    explicit DynamicDualSegtree(Index n)
        : DynamicDualSegtree(Index(0), n, Monoid::id()) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }

    DynamicDualSegtree(Index left, Index right)
        : DynamicDualSegtree(left, right, Monoid::id()) {}

    DynamicDualSegtree(Index left, Index right, T initial_value)
        : _left(left),
          _right(right),
          _initial_value(std::move(initial_value)),
          _root(0),
          _nodes(1) {
        assert(left <= right);
    }

    size_type size() const {
        return detail::dynamic_distance(_left, _right);
    }

    bool empty() const {
        return _left == _right;
    }

    Index left_bound() const {
        return _left;
    }

    Index right_bound() const {
        return _right;
    }

    const T& initial_value() const {
        return _initial_value;
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
        _nodes.resize(1);
    }

    void set(Index p, T x) {
        assert(_left <= p && p < _right);
        _root = set_node(_root, _left, _right, p, std::move(x));
    }

    T get(Index p) const {
        assert(_left <= p && p < _right);
        int t = _root;
        Index left = _left;
        Index right = _right;
        T inherited = Monoid::id();

        while (t) {
            Index middle = std::midpoint(left, right);
            if (middle == left) {
                T value = _nodes[t].has_lazy ? _nodes[t].val : _initial_value;
                return Monoid::op(inherited, value);
            }
            inherited = compose(inherited, t);
            if (p < middle) {
                t = _nodes[t].left;
                right = middle;
            } else {
                t = _nodes[t].right;
                left = middle;
            }
        }
        return Monoid::op(inherited, _initial_value);
    }

    T operator[](Index p) const {
        return get(p);
    }

    void apply(Index p, const T& x) {
        assert(_left <= p && p < _right);
        apply(p, p + 1, x);
    }

    void apply(Index left, Index right, const T& x) {
        assert(_left <= left && left <= right && right <= _right);
        if (left == right) return;
        _root = apply_node(_root, _left, _right, left, right, x);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_DUAL_SEGTREE_HPP
