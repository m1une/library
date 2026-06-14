#ifndef M1UNE_DUAL_SEGTREE_HPP
#define M1UNE_DUAL_SEGTREE_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "acted_monoid/concept.hpp"
#include "math/bit_ceil.hpp"

namespace m1une {
namespace data_structure {

// A generic Dual Segment Tree for range updates and point queries.
// It uses the operator monoid and mapping from an ActedMonoid.
template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct DualSegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    int _n, _size, _log;
    std::vector<T> _d;
    std::vector<F> _lz;

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

    int node_length(int k) const {
        int level = std::bit_width((unsigned int)k) - 1;
        return _size >> level;
    }

    int node_left(int k) const {
        int level = std::bit_width((unsigned int)k) - 1;
        int len = _size >> level;
        return (k - (1 << level)) * len;
    }

    void all_apply(int k, const F& f) {
        if (k < _size) {
            _lz[k] = ActedMonoid::op_comp(f, _lz[k]);
        } else {
            _d[k - _size] = mapping_at(f, _d[k - _size], 0);
        }
    }

    void push(int k) {
        all_apply(2 * k, _lz[k]);
        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k) / 2));
        _lz[k] = ActedMonoid::op_id();
    }

   public:
    // Constructs an empty dual segment tree.
    DualSegtree() : DualSegtree(0) {}

    // Constructs a dual segment tree of size `n`, initialized with the identity element.
    explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n, ActedMonoid::id())) {}

    // Constructs a dual segment tree from an existing vector.
    explicit DualSegtree(const std::vector<T>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(_size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) _d[i] = v[i];
    }
    explicit DualSegtree(std::vector<T>&& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(_size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) _d[i] = std::move(v[i]);
    }

    // Constructs a dual segment tree from a vector of a different type U.
    // It automatically adapts to the ActedMonoid's initialization requirements:
    // 1. ActedMonoid::make(val) if it exists.
    // 2. ActedMonoid::make(val, index) if the acted monoid requires global indices.
    // 3. static_cast<T>(val) as a fallback for simple value types.
    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { ActedMonoid::make(x); } ||
        requires(U x, int i) { ActedMonoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(_size, ActedMonoid::id());
        _lz.assign(_size, ActedMonoid::op_id());
        for (int i = 0; i < _n; i++) {
            if constexpr (requires(U x) { ActedMonoid::make(x); }) {
                _d[i] = ActedMonoid::make(v[i]);
            } else if constexpr (requires(U x, int idx) { ActedMonoid::make(x, idx); }) {
                _d[i] = ActedMonoid::make(v[i], i);
            } else {
                _d[i] = static_cast<T>(v[i]);
            }
        }
    }

    // Returns the number of elements.
    int size() const {
        return _n;
    }

    // Returns whether the tree is empty.
    bool empty() const {
        return _n == 0;
    }

    // Assigns x to the p-th element after applying pending updates on its path.
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _d[p - _size] = std::move(x);
    }

    // Returns the value of the p-th element after applying pending updates on its path.
    T get(int p) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        return _d[p - _size];
    }

    // Returns the value of the p-th element.
    T operator[](int p) {
        return get(p);
    }

    // Applies the operator f to the p-th element.
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _d[p - _size] = mapping_at(f, _d[p - _size], 0);
    }

    // Applies the operator f to all elements in the range [l, r).
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        int base_l = l;
        l += _size;
        r += _size;

        for (int i = _log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        while (l < r) {
            if (l & 1) {
                all_apply(l, shift_operator(f, node_left(l) - base_l));
                l++;
            }
            if (r & 1) {
                --r;
                all_apply(r, shift_operator(f, node_left(r) - base_l));
            }
            l >>= 1;
            r >>= 1;
        }
    }

    // Returns all elements as a vector after applying all pending updates.
    std::vector<T> to_vector() {
        for (int k = 1; k < _size; k++) push(k);
        std::vector<T> res;
        res.reserve(_n);
        for (int i = 0; i < _n; i++) res.push_back(_d[i]);
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
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DUAL_SEGTREE_HPP
