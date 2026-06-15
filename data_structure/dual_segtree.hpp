#ifndef M1UNE_DUAL_SEGTREE_HPP
#define M1UNE_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "math/bit_ceil.hpp"
#include "monoid/concept.hpp"

namespace m1une {
namespace data_structure {

// A generic Dual Segment Tree for range monoid updates and point queries.
template <m1une::monoid::IsMonoid Monoid>
struct DualSegtree {
    using T = typename Monoid::value_type;

   private:
    int _n, _size, _log;
    std::vector<T> _d;

    void all_apply(int k, const T& x) {
        _d[k] = Monoid::op(x, _d[k]);
    }

    void push(int k) {
        all_apply(2 * k, _d[k]);
        all_apply(2 * k + 1, _d[k]);
        _d[k] = Monoid::id();
    }

   public:
    // Constructs an empty dual segment tree.
    DualSegtree() : DualSegtree(0) {}

    // Constructs a dual segment tree of size `n`, initialized with the identity element.
    explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n, Monoid::id())) {}

    // Constructs a dual segment tree from an existing vector.
    explicit DualSegtree(const std::vector<T>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];
    }
    explicit DualSegtree(std::vector<T>&& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);
    }

    // Constructs a dual segment tree from a vector of a different type U.
    // It automatically adapts to the Monoid's initialization requirements:
    // 1. Monoid::make(val) if it exists.
    // 2. Monoid::make(val, index) if the monoid requires global indices.
    // 3. static_cast<T>(val) as a fallback for simple monoids.
    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Monoid::make(x); } ||
        requires(U x, int i) { Monoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) {
            if constexpr (requires(U x) { Monoid::make(x); }) {
                _d[_size + i] = Monoid::make(v[i]);
            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx); }) {
                _d[_size + i] = Monoid::make(v[i], i);
            } else {
                _d[_size + i] = static_cast<T>(v[i]);
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
        _d[p] = std::move(x);
    }

    // Returns the value of the p-th element after applying pending updates on its path.
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

    // Applies x to the p-th element.
    void apply(int p, T x) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        all_apply(p, x);
    }

    // Applies x to all elements in the range [l, r).
    void apply(int l, int r, T x) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += _size;
        r += _size;

        for (int i = _log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        while (l < r) {
            if (l & 1) all_apply(l++, x);
            if (r & 1) all_apply(--r, x);
            l >>= 1;
            r >>= 1;
        }
    }

    // Returns all elements as a vector after applying all pending updates.
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
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DUAL_SEGTREE_HPP
