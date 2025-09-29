#ifndef M1UNE_LAZY_SEGTREE_HPP
#define M1UNE_LAZY_SEGTREE_HPP 1

#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>

#include "monoid/acted_monoid.hpp"
#include "utilities/bit_ceil.hpp"

namespace m1une {

template <ActedMonoid AM>
struct lazy_segment_tree {
    using S = typename AM::data_type;
    using F = typename AM::act_type;

   private:
    int _n;
    int _size;
    int _log;
    std::vector<S> _data;
    std::vector<F> _lazy;

    void update(int k) {
        _data[k] = AM::data_op(_data[2 * k], _data[2 * k + 1]);
    }

    void all_apply(int k, F f) {
        _data[k] = AM::apply(f, _data[k]);
        if (k < _size) {
            _lazy[k] = AM::act_op(_lazy[k], f);
        }
    }

    void push(int k) {
        all_apply(2 * k, _lazy[k]);
        all_apply(2 * k + 1, _lazy[k]);
        _lazy[k] = AM::act_id();
    }

   public:
    lazy_segment_tree() : lazy_segment_tree(0) {}
    explicit lazy_segment_tree(int n) : lazy_segment_tree(std::vector<S>(n, AM::data_id())) {}
    explicit lazy_segment_tree(const std::vector<S>& v) : _n(v.size()) {
        _size = bit_ceil((unsigned int)_n);
        _log = 0;
        while ((1U << _log) < (unsigned int)_size) _log++;
        _data.assign(2 * _size, AM::data_id());
        _lazy.assign(_size, AM::act_id());
        for (int i = 0; i < _n; i++) {
            _data[_size + i] = v[i];
        }
        for (int i = _size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _data[p] = x;
        for (int i = 1; i <= _log; i++) update(p >> i);
    }

    S get(int p) {
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        return _data[p];
    }

    S prod(int l, int r) {
        if (l == r) return AM::data_id();

        l += _size;
        r += _size;

        for (int i = _log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = AM::data_id(), smr = AM::data_id();
        while (l < r) {
            if (l & 1) sml = AM::data_op(sml, _data[l++]);
            if (r & 1) smr = AM::data_op(_data[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return AM::data_op(sml, smr);
    }

    S all_prod() {
        return _data[1];
    }

    void apply(int p, F f) {
        p += _size;
        for (int i = _log; i >= 1; i--) push(p >> i);
        _data[p] = AM::apply(f, _data[p]);
        for (int i = 1; i <= _log; i++) update(p >> i);
    }

    void apply(int l, int r, F f) {
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

    int max_right(int l, auto g) {
        if (l == _n) return _n;
        l += _size;
        for (int i = _log; i >= 1; i--) push(l >> i);
        S sm = AM::data_id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(AM::data_op(sm, _data[l]))) {
                while (l < _size) {
                    push(l);
                    l = (2 * l);
                    if (g(AM::data_op(sm, _data[l]))) {
                        sm = AM::data_op(sm, _data[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = AM::data_op(sm, _data[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    int min_left(int r, auto g) {
        if (r == 0) return 0;
        r += _size;
        for (int i = _log; i >= 1; i--) push((r - 1) >> i);
        S sm = AM::data_id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(AM::data_op(_data[r], sm))) {
                while (r < _size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(AM::data_op(_data[r], sm))) {
                        sm = AM::data_op(_data[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = AM::data_op(_data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

}  // namespace m1une

#endif  // M1UNE_LAZY_SEGTREE_HPP
