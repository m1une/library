#ifndef M1UNE_PERSISTENT_DUAL_SEGTREE_HPP
#define M1UNE_PERSISTENT_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "acted_monoid/concept.hpp"

namespace m1une {
namespace data_structure {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct PersistentDualSegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node {
        T val;
        F lazy;
        int l, r;
        bool has_lazy;

        Node() : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), l(0), r(0), has_lazy(false) {}
        explicit Node(T value)
            : val(std::move(value)), lazy(ActedMonoid::op_id()), l(0), r(0), has_lazy(false) {}
        Node(int left, int right)
            : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), l(left), r(right), has_lazy(false) {}
    };

    int _n;
    int _root;
    std::shared_ptr<std::vector<Node>> _pool;

    explicit PersistentDualSegtree(int n, int root, std::shared_ptr<std::vector<Node>> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {}

    int new_node(const Node& node) const {
        _pool->push_back(node);
        return int(_pool->size()) - 1;
    }

    int new_node(Node&& node) const {
        _pool->push_back(std::move(node));
        return int(_pool->size()) - 1;
    }

    int clone_node(int t) const {
        return new_node((*_pool)[t]);
    }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else if constexpr (requires(U x, int i) { ActedMonoid::make(x, i); }) {
            return ActedMonoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    static T mapping_at(const F& f, const T& value, long long ord) {
        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {
            return ActedMonoid::mapping(f, value, ord);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static F shift_operator(const F& f, long long ord) {
        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {
            return ActedMonoid::op_shift(f, ord);
        } else {
            return f;
        }
    }

    F compose_for_child(const F& inherited, const Node& node, long long ord) const {
        F shifted = shift_operator(inherited, ord);
        if (!node.has_lazy) return shifted;
        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy, ord));
    }

    int build(int l, int r, const std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(v[l]));
        int m = (l + r) >> 1;
        return new_node(Node(build(l, m, v), build(m, r, v)));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        return new_node(Node(build(l, m, v), build(m, r, v)));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        return new_node(Node(build_from_values(l, m, v), build_from_values(m, r, v)));
    }

    void all_apply_to_node(int t, const F& f, int l, int r) const {
        Node& node = (*_pool)[t];
        if (r - l == 1) {
            node.val = mapping_at(f, node.val, 0);
        } else {
            node.lazy = ActedMonoid::op_comp(f, node.lazy);
            node.has_lazy = true;
        }
    }

    int all_apply_clone(int t, const F& f, int l, int r) const {
        int res = clone_node(t);
        all_apply_to_node(res, f, l, r);
        return res;
    }

    void push(int t, int l, int r) const {
        Node node = (*_pool)[t];
        if (!node.has_lazy || r - l == 1) return;
        int m = (l + r) >> 1;
        int left = all_apply_clone(node.l, node.lazy, l, m);
        int right = all_apply_clone(node.r, shift_operator(node.lazy, m - l), m, r);
        Node& target = (*_pool)[t];
        target.l = left;
        target.r = right;
        target.lazy = ActedMonoid::op_id();
        target.has_lazy = false;
    }

    int set_node(int t, int l, int r, int p, T value) const {
        t = clone_node(t);
        if (r - l == 1) {
            Node& node = (*_pool)[t];
            node.val = std::move(value);
            node.lazy = ActedMonoid::op_id();
            node.has_lazy = false;
            return t;
        }
        push(t, l, r);
        int m = (l + r) >> 1;
        if (p < m) {
            (*_pool)[t].l = set_node((*_pool)[t].l, l, m, p, std::move(value));
        } else {
            (*_pool)[t].r = set_node((*_pool)[t].r, m, r, p, std::move(value));
        }
        return t;
    }

    int apply_node(int t, int l, int r, int ql, int qr, const F& f) const {
        if (qr <= l || r <= ql) return t;
        t = clone_node(t);
        if (ql <= l && r <= qr) {
            all_apply_to_node(t, shift_operator(f, l - ql), l, r);
            return t;
        }
        push(t, l, r);
        int m = (l + r) >> 1;
        (*_pool)[t].l = apply_node((*_pool)[t].l, l, m, ql, qr, f);
        (*_pool)[t].r = apply_node((*_pool)[t].r, m, r, ql, qr, f);
        return t;
    }

    T get_node(int t, int l, int r, int p, const F& inherited) const {
        const Node& node = (*_pool)[t];
        if (r - l == 1) return mapping_at(inherited, node.val, 0);
        int m = (l + r) >> 1;
        if (p < m) return get_node(node.l, l, m, p, compose_for_child(inherited, node, 0));
        return get_node(node.r, m, r, p, compose_for_child(inherited, node, m - l));
    }

    void collect_node(int t, int l, int r, int ql, int qr, const F& inherited, std::vector<T>& res) const {
        if (!t || qr <= l || r <= ql) return;
        const Node& node = (*_pool)[t];
        if (r - l == 1) {
            res.push_back(mapping_at(inherited, node.val, 0));
            return;
        }
        int m = (l + r) >> 1;
        collect_node(node.l, l, m, ql, qr, compose_for_child(inherited, node, 0), res);
        collect_node(node.r, m, r, ql, qr, compose_for_child(inherited, node, m - l), res);
    }

   public:
    PersistentDualSegtree() : PersistentDualSegtree(0) {}

    explicit PersistentDualSegtree(int n)
        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        assert(0 <= n);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, ActedMonoid::id()));
    }

    explicit PersistentDualSegtree(const std::vector<T>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    explicit PersistentDualSegtree(std::vector<T>&& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { ActedMonoid::make(x); } || requires(U x, int i) { ActedMonoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentDualSegtree(const std::vector<U>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build_from_values(0, _n, v);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    PersistentDualSegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentDualSegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        return get_node(_root, 0, _n, p, ActedMonoid::op_id());
    }

    T operator[](int p) const {
        return get(p);
    }

    PersistentDualSegtree apply(int p, const F& f) const {
        assert(0 <= p && p < _n);
        return apply(p, p + 1, f);
    }

    PersistentDualSegtree apply(int l, int r, const F& f) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return *this;
        return PersistentDualSegtree(_n, apply_node(_root, 0, _n, l, r, f), _pool);
    }

    std::vector<T> to_vector() const {
        return to_vector(0, _n);
    }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        collect_node(_root, 0, _n, l, r, ActedMonoid::op_id(), res);
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DUAL_SEGTREE_HPP
