#ifndef M1UNE_PERSISTENT_SEGTREE_HPP
#define M1UNE_PERSISTENT_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct PersistentSegtree {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T val;
        int l, r;

        Node() : val(Monoid::id()), l(0), r(0) {}
        explicit Node(T value) : val(std::move(value)), l(0), r(0) {}
        Node(T value, int left, int right) : val(std::move(value)), l(left), r(right) {}
    };

    int _n;
    int _root;
    std::shared_ptr<std::vector<Node>> _pool;

    explicit PersistentSegtree(int n, int root, std::shared_ptr<std::vector<Node>> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {}

    int new_node(const Node& node) const {
        _pool->push_back(node);
        return int(_pool->size()) - 1;
    }

    int new_node(Node&& node) const {
        _pool->push_back(std::move(node));
        return int(_pool->size()) - 1;
    }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {
            return Monoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    int build(int l, int r, const std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(v[l]));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(Monoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(Monoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        int left = build_from_values(l, m, v);
        int right = build_from_values(m, r, v);
        return new_node(Node(Monoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    int set_node(int t, int l, int r, int p, T value) const {
        if (r - l == 1) return new_node(Node(std::move(value)));
        int m = (l + r) >> 1;
        int left = (*_pool)[t].l;
        int right = (*_pool)[t].r;
        if (p < m) {
            left = set_node(left, l, m, p, std::move(value));
        } else {
            right = set_node(right, m, r, p, std::move(value));
        }
        return new_node(Node(Monoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    T prod_node(int t, int l, int r, int ql, int qr) const {
        if (!t || qr <= l || r <= ql) return Monoid::id();
        if (ql <= l && r <= qr) return (*_pool)[t].val;
        int m = (l + r) >> 1;
        return Monoid::op(prod_node((*_pool)[t].l, l, m, ql, qr), prod_node((*_pool)[t].r, m, r, ql, qr));
    }

    void collect_node(int t, int l, int r, int ql, int qr, std::vector<T>& res) const {
        if (!t || qr <= l || r <= ql) return;
        if (r - l == 1) {
            res.push_back((*_pool)[t].val);
            return;
        }
        int m = (l + r) >> 1;
        collect_node((*_pool)[t].l, l, m, ql, qr, res);
        collect_node((*_pool)[t].r, m, r, ql, qr, res);
    }

    template <class F>
    int max_right_node(int t, int l, int r, int ql, T& sm, F& f) const {
        if (r <= ql) return r;
        if (ql <= l) {
            T nxt = Monoid::op(sm, (*_pool)[t].val);
            if (f(nxt)) {
                sm = std::move(nxt);
                return r;
            }
            if (r - l == 1) return l;
        }
        int m = (l + r) >> 1;
        int res = max_right_node((*_pool)[t].l, l, m, ql, sm, f);
        if (res < m) return res;
        return max_right_node((*_pool)[t].r, m, r, ql, sm, f);
    }

    template <class F>
    int min_left_node(int t, int l, int r, int qr, T& sm, F& f) const {
        if (qr <= l) return l;
        if (r <= qr) {
            T nxt = Monoid::op((*_pool)[t].val, sm);
            if (f(nxt)) {
                sm = std::move(nxt);
                return l;
            }
            if (r - l == 1) return r;
        }
        int m = (l + r) >> 1;
        int res = min_left_node((*_pool)[t].r, m, r, qr, sm, f);
        if (m < res) return res;
        return min_left_node((*_pool)[t].l, l, m, qr, sm, f);
    }

   public:
    PersistentSegtree() : PersistentSegtree(0) {}

    explicit PersistentSegtree(int n)
        : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        assert(0 <= n);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));
    }

    explicit PersistentSegtree(const std::vector<T>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    explicit PersistentSegtree(std::vector<T>&& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        _pool->reserve(v.size() * 2 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n, v);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentSegtree(const std::vector<U>& v)
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

    PersistentSegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentSegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        int t = _root;
        int l = 0, r = _n;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (p < m) {
                t = (*_pool)[t].l;
                r = m;
            } else {
                t = (*_pool)[t].r;
                l = m;
            }
        }
        return (*_pool)[t].val;
    }

    T operator[](int p) const {
        return get(p);
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return Monoid::id();
        return prod_node(_root, 0, _n, l, r);
    }

    T all_prod() const {
        return _root ? (*_pool)[_root].val : Monoid::id();
    }

    std::vector<T> to_vector() const {
        return to_vector(0, _n);
    }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        collect_node(_root, 0, _n, l, r, res);
        return res;
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(Monoid::id()));
        if (l == _n) return _n;
        T sm = Monoid::id();
        return max_right_node(_root, 0, _n, l, sm, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(Monoid::id()));
        if (r == 0) return 0;
        T sm = Monoid::id();
        return min_left_node(_root, 0, _n, r, sm, f);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_SEGTREE_HPP
