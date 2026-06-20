#ifndef M1UNE_SPARSE_TABLE_HPP
#define M1UNE_SPARSE_TABLE_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

// A Sparse Table utilizing C++20 Concepts for type safety.
// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.
// [IMPORTANT] For O(1) range queries to work correctly, the monoid operation MUST be idempotent.
// i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max, GCD, Bitwise AND/OR).
template <m1une::monoid::IsMonoid Monoid>
struct SparseTable {
    using T = typename Monoid::value_type;

   private:
    int _n;
    std::vector<std::vector<T>> _st;

   public:
    // Constructs an empty sparse table.
    SparseTable() : _n(0) {}

    // Constructs a sparse table from an existing vector in O(N log N) time.
    explicit SparseTable(const std::vector<T>& v) : _n(int(v.size())) {
        if (_n == 0) return;

        // Compute the maximum power of 2 needed
        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n));

        // Initialize the base level
        for (int i = 0; i < _n; i++) {
            _st[0][i] = v[i];
        }

        // Build the sparse table
        for (int k = 1; k < max_log; k++) {
            for (int i = 0; i + (1 << k) <= _n; i++) {
                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    explicit SparseTable(std::vector<T>&& v) : _n(int(v.size())) {
        if (_n == 0) return;

        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n));

        for (int i = 0; i < _n; i++) {
            _st[0][i] = std::move(v[i]);
        }

        for (int k = 1; k < max_log; k++) {
            for (int i = 0; i + (1 << k) <= _n; i++) {
                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // Constructs a sparse table from a vector of a different type U.
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
    explicit SparseTable(const std::vector<U>& v) : _n(int(v.size())) {
        if (_n == 0) return;

        int max_log = std::bit_width((unsigned int)_n);
        _st.assign(max_log, std::vector<T>(_n));

        // Compile-time branching based on the available make() signature
        for (int i = 0; i < _n; i++) {
            if constexpr (requires(U x) { Monoid::make(x); }) {
                _st[0][i] = Monoid::make(v[i]);
            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx); }) {
                _st[0][i] = Monoid::make(v[i], i);
            } else {
                _st[0][i] = static_cast<T>(v[i]);
            }
        }
        for (int k = 1; k < max_log; k++) {
            for (int i = 0; i + (1 << k) <= _n; i++) {
                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // Returns the product (result of the monoid operation) in the range [l, r) in O(1) time.
    // Requires the monoid operation to be idempotent.
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return Monoid::id();

        // Calculate the largest power of 2 less than or equal to the interval length
        int k = std::bit_width((unsigned int)(r - l)) - 1;
        return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_SPARSE_TABLE_HPP
