#ifndef M1UNE_SPARSE_TABLE_HPP
#define M1UNE_SPARSE_TABLE_HPP 1

#include <vector>
#include <cassert>
#include <bit>
#include "monoid/concept.hpp"

namespace m1une {
namespace data_structure {

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

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_SPARSE_TABLE_HPP
