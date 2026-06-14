#ifndef M1UNE_SEGTREE_HPP
#define M1UNE_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"
#include "math/bit_ceil.hpp"

namespace m1une {
namespace data_structure {

// A generic Segment Tree utilizing C++20 Concepts for type safety.
// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.
template <m1une::monoid::IsMonoid Monoid>
struct Segtree {
    using T = typename Monoid::value_type;

   private:
    int _n, _size, _log;
    std::vector<T> _d;

    void update(int k) {
        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);
    }

   public:
    // Constructs an empty segment tree.
    Segtree() : Segtree(0) {}

    // Constructs a segment tree of size `n`, initialized with the identity element.
    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}

    // Constructs a segment tree from an existing vector.
    explicit Segtree(const std::vector<T>& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) _d[_size + i] = v[i];
        for (int i = _size - 1; i >= 1; i--) update(i);
    }
    explicit Segtree(std::vector<T>&& v) : _n(int(v.size())) {
        _size = m1une::math::bit_ceil((unsigned int)(_n));
        _log = 0;
        while ((1U << _log) < (unsigned int)(_size)) _log++;
        _d.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);
        for (int i = _size - 1; i >= 1; i--) update(i);
    }

    // Constructs a segment tree from a vector of a different type U.
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
    explicit Segtree(const std::vector<U>& v) : _n(int(v.size())) {
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

    // Sets the value of the element at index `p` to `x`.
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += _size;
        _d[p] = x;
        for (int i = 1; i <= _log; i++) update(p >> i);
    }

    // Returns the value of the element at index `p`.
    T get(int p) const {
        assert(0 <= p && p < _n);
        return _d[p + _size];
    }

    // Returns the value of the element at index `p`.
    T operator[](int p) const {
        return get(p);
    }

    // Returns the product (result of the monoid operation) in the range [l, r).
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        T sml = Monoid::id(), smr = Monoid::id();
        l += _size;
        r += _size;
        while (l < r) {
            if (l & 1) sml = Monoid::op(sml, _d[l++]);
            if (r & 1) smr = Monoid::op(_d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return Monoid::op(sml, smr);
    }

    // Returns the product of the entire array.
    T all_prod() const {
        return _d[1];
    }

    // Returns all elements as a vector.
    std::vector<T> to_vector() const {
        return to_vector(0, _n);
    }

    // Returns the elements in the range [l, r) as a vector.
    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        for (int i = l; i < r; i++) res.push_back(_d[_size + i]);
        return res;
    }

    // Finds the largest `r` such that `f(prod(l, r))` is true.
    // Uses a custom functor or lambda `f`.
    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(Monoid::id()));
        if (l == _n) return _n;
        l += _size;
        T sm = Monoid::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(Monoid::op(sm, _d[l]))) {
                while (l < _size) {
                    l = (2 * l);
                    if (f(Monoid::op(sm, _d[l]))) {
                        sm = Monoid::op(sm, _d[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = Monoid::op(sm, _d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Finds the smallest `l` such that `f(prod(l, r))` is true.
    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(Monoid::id()));
        if (r == 0) return 0;
        r += _size;
        T sm = Monoid::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(Monoid::op(_d[r], sm))) {
                while (r < _size) {
                    r = (2 * r + 1);
                    if (f(Monoid::op(_d[r], sm))) {
                        sm = Monoid::op(_d[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = Monoid::op(_d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_SEGTREE_HPP
