#ifndef M1UNE_LAZY_SEGTREE_HPP
#define M1UNE_LAZY_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "acted_monoid/concept.hpp"
#include "math/bit_ceil.hpp"

namespace m1une {
namespace data_structure {

// A highly generic Lazy Segment Tree utilizing C++20 Concepts for type safety.
// It operates on any Acted Monoid structure satisfying the `m1une::acted_monoid::IsActedMonoid` concept.
template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct LazySegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    int _n, _size, _log;
    std::vector<T> _d;
    std::vector<F> _lz;

    // Recalculates the value of the node k from its children.
    void update(int k) {
        _d[k] = ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);
    }

    // Applies the operator f to the node k and updates its lazy tag if it's an internal node.
    void all_apply(int k, F f) {
        _d[k] = ActedMonoid::mapping(f, _d[k]);
        if (k < _size) {
            _lz[k] = ActedMonoid::op_comp(f, _lz[k]);
        }
    }

    // Propagates the lazy tag of the node k down to its children.
    void push(int k) {
        all_apply(2 * k, _lz[k]);
        all_apply(2 * k + 1, _lz[k]);
        _lz[k] = ActedMonoid::op_id();
    }

   public:
    // Constructs an empty lazy segment tree.
    LazySegtree() : LazySegtree(0) {}

    // Constructs a lazy segment tree of size `n`, initialized with the identity element.
    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n, ActedMonoid::id())) {}

    // Constructs a lazy segment tree from an existing vector.
    explicit LazySegtree(const std::vector<T>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];
        for (int i = _size - 1; i >= 1; i--) update(i);
    }
    explicit LazySegtree(std::vector<T>&& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);
        for (int i = _size - 1; i >= 1; i--) update(i);
    }

    // Constructs a lazy segment tree from a vector of a different type U.
    // It automatically adapts to the Monoid's initialization requirements:
    // 1. ActedMonoid::make(val) if it exists.
    // 2. ActedMonoid::make(val, index) if the monoid requires global indices.
    // 3. static_cast<T>(val) as a fallback for simple monoids.
    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit LazySegtree(const std::vector<U>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) {
            if constexpr (requires(U x) { ActedMonoid::make(x); }) {
                _d[_size + i] = ActedMonoid::make(v[i]);
            } else if constexpr (requires(U x, int idx) { ActedMonoid::make(x, idx); }) {
                _d[_size + i] = ActedMonoid::make(v[i], i);
            } else {
                _d[_size + i] = static_cast<T>(v[i]);
            }
        }
        for (int i = _size - 1; i >= 1; i--) update(i);
    }

    // Returns the number of elements.
    int size() const {
        return _n;
    }

    // Returns whether the tree is empty.
    bool empty() const {
        return _n == 0;
    }

    // Assigns x to the p-th element.
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _d[p] = x;
        for (int i = 1; i <= _log; i++) update(p >> i);
    }

    // Returns the value of the p-th element.
    T get(int p) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        return _d[p];
    }

    // Returns the value of the p-th element.
    T operator[](int p) {
        return get(p);
    }

    // Returns the product (result of the monoid operation) in the range [l, r).
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return ActedMonoid::id();

        l += _size;
        r += _size;

        for (int i = _log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        T sml = ActedMonoid::id(), smr = ActedMonoid::id();
        while (l < r) {
            if (l & 1) sml = ActedMonoid::op(sml, _d[l++]);
            if (r & 1) smr = ActedMonoid::op(_d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return ActedMonoid::op(sml, smr);
    }

    // Returns the product of the entire array.
    T all_prod() const {
        return _d[1];
    }

    // Returns all elements as a vector.
    std::vector<T> to_vector() {
        for (int k = 1; k < _size; k++) push(k);
        std::vector<T> res;
        res.reserve(_n);
        for (int i = 0; i < _n; i++) res.push_back(_d[_size + i]);
        return res;
    }

    // Returns the elements in the range [l, r) as a vector.
    std::vector<T> to_vector(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        for (int i = l; i < r; i++) res.push_back(get(i));
        return res;
    }

    // Applies the operator f to the p-th element.
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _d[p] = ActedMonoid::mapping(f, _d[p]);
        for (int i = 1; i <= _log; i++) update(p >> i);
    }

    // Applies the operator f to all elements in the range [l, r).
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += _size;
        r += _size;

        for (int i = _log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= _log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    // Finds the largest r such that g(prod(l, r)) is true.
    template <class F_pred>
    int max_right(int l, F_pred g) {
        assert(0 <= l && l <= _n);
        assert(g(ActedMonoid::id()));
        if (l == _n) return _n;
        l += _size;
        for (int i = _log; i >= 1; i--) push(l >> i);
        T sm = ActedMonoid::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(ActedMonoid::op(sm, _d[l]))) {
                while (l < _size) {
                    push(l);
                    l = (2 * l);
                    if (g(ActedMonoid::op(sm, _d[l]))) {
                        sm = ActedMonoid::op(sm, _d[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = ActedMonoid::op(sm, _d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Finds the smallest l such that g(prod(l, r)) is true.
    template <class F_pred>
    int min_left(int r, F_pred g) {
        assert(0 <= r && r <= _n);
        assert(g(ActedMonoid::id()));
        if (r == 0) return 0;
        r += _size;
        for (int i = _log; i >= 1; i--) push((r - 1) >> i);
        T sm = ActedMonoid::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(ActedMonoid::op(_d[r], sm))) {
                while (r < _size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(ActedMonoid::op(_d[r], sm))) {
                        sm = ActedMonoid::op(_d[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = ActedMonoid::op(_d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_LAZY_SEGTREE_HPP
