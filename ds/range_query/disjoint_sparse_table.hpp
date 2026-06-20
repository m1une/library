#ifndef M1UNE_DISJOINT_SPARSE_TABLE_HPP
#define M1UNE_DISJOINT_SPARSE_TABLE_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

// A Disjoint Sparse Table for static range queries.
// It supports any associative monoid, including non-idempotent and non-commutative ones.
template <m1une::monoid::IsMonoid Monoid>
struct DisjointSparseTable {
    using T = typename Monoid::value_type;

   private:
    int _n;
    std::vector<std::vector<T>> _st;

    void build() {
        if (_n == 0) return;

        for (int k = 0; k < int(_st.size()); k++) {
            int half = 1 << k;
            int block = half << 1;
            for (int start = 0; start < _n; start += block) {
                int mid = std::min(start + half, _n);
                int end = std::min(start + block, _n);

                _st[k][mid - 1] = _st[0][mid - 1];
                for (int i = mid - 2; i >= start; i--) {
                    _st[k][i] = Monoid::op(_st[0][i], _st[k][i + 1]);
                }

                if (mid == end) continue;
                _st[k][mid] = _st[0][mid];
                for (int i = mid + 1; i < end; i++) {
                    _st[k][i] = Monoid::op(_st[k][i - 1], _st[0][i]);
                }
            }
        }
    }

   public:
    // Constructs an empty disjoint sparse table.
    DisjointSparseTable() : _n(0) {}

    // Constructs a disjoint sparse table from an existing vector in O(N log N) time.
    explicit DisjointSparseTable(const std::vector<T>& v) : _n(int(v.size())) {
        if (_n == 0) return;

        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n, Monoid::id()));
        for (int i = 0; i < _n; i++) {
            _st[0][i] = v[i];
        }
        build();
    }
    explicit DisjointSparseTable(std::vector<T>&& v) : _n(int(v.size())) {
        if (_n == 0) return;

        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n, Monoid::id()));
        for (int i = 0; i < _n; i++) {
            _st[0][i] = std::move(v[i]);
        }
        build();
    }

    // Constructs a disjoint sparse table from a vector of a different type U.
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
    explicit DisjointSparseTable(const std::vector<U>& v) : _n(int(v.size())) {
        if (_n == 0) return;

        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n, Monoid::id()));
        for (int i = 0; i < _n; i++) {
            if constexpr (requires(U x) { Monoid::make(x); }) {
                _st[0][i] = Monoid::make(v[i]);
            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx); }) {
                _st[0][i] = Monoid::make(v[i], i);
            } else {
                _st[0][i] = static_cast<T>(v[i]);
            }
        }
        build();
    }

    // Returns the product (result of the monoid operation) in the range [l, r) in O(1) time.
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return Monoid::id();

        r--;
        if (l == r) return _st[0][l];

        int k = std::bit_width((unsigned int)(l ^ r)) - 1;
        return Monoid::op(_st[k][l], _st[k][r]);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DISJOINT_SPARSE_TABLE_HPP
