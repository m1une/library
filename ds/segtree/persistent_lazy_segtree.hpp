#ifndef M1UNE_PERSISTENT_LAZY_SEGTREE_HPP
#define M1UNE_PERSISTENT_LAZY_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct PersistentLazySegtree {
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
        Node(T value, int left, int right)
            : val(std::move(value)), lazy(ActedMonoid::op_id()), l(left), r(right), has_lazy(false) {}
    };

    int _n;
    int _root;
    std::shared_ptr<std::vector<Node>> _pool;

    explicit PersistentLazySegtree(int n, int root, std::shared_ptr<std::vector<Node>> pool)
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
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        int left = build_from_values(l, m, v);
        int right = build_from_values(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    void all_apply_to_node(int t, const F& f) const {
        Node& node = (*_pool)[t];
        node.val = mapping_at(f, node.val, 0);
        node.lazy = ActedMonoid::op_comp(f, node.lazy);
        node.has_lazy = true;
    }

    int all_apply_clone(int t, const F& f) const {
        int res = clone_node(t);
        all_apply_to_node(res, f);
        return res;
    }

    void push(int t, int l, int r) const {
        Node& node = (*_pool)[t];
        if (!node.has_lazy) return;
        int m = (l + r) >> 1;
        node.l = all_apply_clone(node.l, node.lazy);
        node.r = all_apply_clone(node.r, shift_operator(node.lazy, m - l));
        node.lazy = ActedMonoid::op_id();
        node.has_lazy = false;
    }

    void update(int t) const {
        Node& node = (*_pool)[t];
        node.val = ActedMonoid::op((*_pool)[node.l].val, (*_pool)[node.r].val);
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
        update(t);
        return t;
    }

    int apply_node(int t, int l, int r, int ql, int qr, const F& f) const {
        if (qr <= l || r <= ql) return t;
        t = clone_node(t);
        if (ql <= l && r <= qr) {
            all_apply_to_node(t, shift_operator(f, l - ql));
            return t;
        }
        push(t, l, r);
        int m = (l + r) >> 1;
        (*_pool)[t].l = apply_node((*_pool)[t].l, l, m, ql, qr, f);
        (*_pool)[t].r = apply_node((*_pool)[t].r, m, r, ql, qr, f);
        update(t);
        return t;
    }

    T prod_node(int t, int l, int r, int ql, int qr, const F& inherited) const {
        if (!t || qr <= l || r <= ql) return ActedMonoid::id();
        const Node& node = (*_pool)[t];
        if (ql <= l && r <= qr) return mapping_at(inherited, node.val, 0);
        int m = (l + r) >> 1;
        return ActedMonoid::op(prod_node(node.l, l, m, ql, qr, compose_for_child(inherited, node, 0)),
                               prod_node(node.r, m, r, ql, qr, compose_for_child(inherited, node, m - l)));
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

    template <class G>
    int max_right_node(int t, int l, int r, int ql, T& sm, const F& inherited, G& g) const {
        if (r <= ql) return r;
        const Node& node = (*_pool)[t];
        if (ql <= l) {
            T nxt = ActedMonoid::op(sm, mapping_at(inherited, node.val, 0));
            if (g(nxt)) {
                sm = std::move(nxt);
                return r;
            }
            if (r - l == 1) return l;
        }
        int m = (l + r) >> 1;
        int res = max_right_node(node.l, l, m, ql, sm, compose_for_child(inherited, node, 0), g);
        if (res < m) return res;
        return max_right_node(node.r, m, r, ql, sm, compose_for_child(inherited, node, m - l), g);
    }

    template <class G>
    int min_left_node(int t, int l, int r, int qr, T& sm, const F& inherited, G& g) const {
        if (qr <= l) return l;
        const Node& node = (*_pool)[t];
        if (r <= qr) {
            T nxt = ActedMonoid::op(mapping_at(inherited, node.val, 0), sm);
            if (g(nxt)) {
                sm = std::move(nxt);
                return l;
            }
            if (r - l == 1) return r;
        }
        int m = (l + r) >> 1;
        int res = min_left_node(node.r, m, r, qr, sm, compose_for_child(inherited, node, m - l), g);
        if (m < res) return res;
        return min_left_node(node.l, l, m, qr, sm, compose_for_child(inherited, node, 0), g);
    }

   public:
    PersistentLazySegtree() : PersistentLazySegtree(0) {}

    explicit PersistentLazySegtree(int n)
        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        assert(0 <= n);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, ActedMonoid::id()));
    }

    explicit PersistentLazySegtree(const std::vector<T>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    explicit PersistentLazySegtree(std::vector<T>&& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { ActedMonoid::make(x); } || requires(U x, int i) { ActedMonoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentLazySegtree(const std::vector<U>& v)
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

    PersistentLazySegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentLazySegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        return prod(p, p + 1);
    }

    T operator[](int p) const {
        return get(p);
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return ActedMonoid::id();
        return prod_node(_root, 0, _n, l, r, ActedMonoid::op_id());
    }

    T all_prod() const {
        return _root ? (*_pool)[_root].val : ActedMonoid::id();
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

    PersistentLazySegtree apply(int p, const F& f) const {
        assert(0 <= p && p < _n);
        return apply(p, p + 1, f);
    }

    PersistentLazySegtree apply(int l, int r, const F& f) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return *this;
        return PersistentLazySegtree(_n, apply_node(_root, 0, _n, l, r, f), _pool);
    }

    template <class G>
    int max_right(int l, G g) const {
        assert(0 <= l && l <= _n);
        assert(g(ActedMonoid::id()));
        if (l == _n) return _n;
        T sm = ActedMonoid::id();
        return max_right_node(_root, 0, _n, l, sm, ActedMonoid::op_id(), g);
    }

    template <class G>
    int min_left(int r, G g) const {
        assert(0 <= r && r <= _n);
        assert(g(ActedMonoid::id()));
        if (r == 0) return 0;
        T sm = ActedMonoid::id();
        return min_left_node(_root, 0, _n, r, sm, ActedMonoid::op_id(), g);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_LAZY_SEGTREE_HPP
