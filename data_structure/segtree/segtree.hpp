#ifndef M1UNE_SEGTREE_HPP
#define M1UNE_SEGTREE_HPP 1

#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>

#include "utilities/bit_ceil.hpp"

namespace m1une {

template <typename Monoid>
struct segment_tree {
    using T = typename Monoid::value_type;

   private:
    int _n;
    int _size;
    std::vector<T> _data;

    void update(int k) {
        _data[k] = Monoid::op(_data[2 * k], _data[2 * k + 1]);
    }

   public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n) : segment_tree(std::vector<T>(n, Monoid::id())) {}
    explicit segment_tree(const std::vector<T>& v) : _n(v.size()) {
        _size = bit_ceil((unsigned int)_n);
        _data.assign(2 * _size, Monoid::id());
        for (int i = 0; i < _n; i++) {
            _data[_size + i] = v[i];
        }
        for (int i = _size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // Set value at position p
    void set(int p, T x) {
        p += _size;
        _data[p] = x;
        for (int i = 1; p >> i >= 1; i++) {
            update(p >> i);
        }
    }

    // Get value at position p
    T get(int p) const {
        return _data[p + _size];
    }

    // Product of range [l, r)
    T prod(int l, int r) const {
        T sml = Monoid::id(), smr = Monoid::id();
        l += _size;
        r += _size;
        while (l < r) {
            if (l & 1) sml = Monoid::op(sml, _data[l++]);
            if (r & 1) smr = Monoid::op(_data[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return Monoid::op(sml, smr);
    }

    // Product of the whole range
    T all_prod() const {
        return _data[1];
    }

    // Find max_right r such that f(prod([l, r))) is true
    int max_right(int l, auto f) const {
        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f), T>, bool>,
                      "f must be a callable that takes a Monoid::value_type and returns a boolean");
        if (l == _n) return _n;
        l += _size;
        T sm = Monoid::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(Monoid::op(sm, _data[l]))) {
                while (l < _size) {
                    l = (2 * l);
                    if (f(Monoid::op(sm, _data[l]))) {
                        sm = Monoid::op(sm, _data[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = Monoid::op(sm, _data[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Find min_left l such that f(prod([l, r))) is true
    int min_left(int r, auto f) const {
        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f), T>, bool>,
                      "f must be a callable that takes a Monoid::value_type and returns a boolean");
        if (r == 0) return 0;
        r += _size;
        T sm = Monoid::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(Monoid::op(_data[r], sm))) {
                while (r < _size) {
                    r = (2 * r + 1);
                    if (f(Monoid::op(_data[r], sm))) {
                        sm = Monoid::op(_data[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = Monoid::op(_data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

}  // namespace m1une

#endif  // M1UNE_SEGTREE_HPP
