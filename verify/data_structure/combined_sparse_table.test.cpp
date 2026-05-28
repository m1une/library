// BEGIN: verify/data_structure/sparse_table.test.cpp
#line 1 "verify/data_structure/sparse_table.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

// BEGIN: data_structure/sparse_table.hpp
#line 3 "data_structure/sparse_table.hpp"

#include <vector>
#include <cassert>
#include <bit>
// BEGIN: monoid/concept.hpp
#line 3 "monoid/concept.hpp"

#include <concepts>

namespace m1une {
namespace monoid {

// Concept to check if a type satisfies the requirements of a Monoid.
// A Monoid must have a `value_type`, an identity element `id()`, and an associative binary operation `op()`.
template <typename M>
concept IsMonoid = requires(typename M::value_type a, typename M::value_type b) {
    // 1. Must define `value_type`
    typename M::value_type;
    
    // 2. Must have a static method `id()` returning `value_type`
    { M::id() } -> std::same_as<typename M::value_type>;
    
    // 3. Must have a static method `op(a, b)` returning `value_type`
    { M::op(a, b) } -> std::same_as<typename M::value_type>;
};

}  // namespace monoid
}  // namespace m1une

// END: monoid/concept.hpp
#line 8 "data_structure/sparse_table.hpp"

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

// END: data_structure/sparse_table.hpp
#line 4 "verify/data_structure/sparse_table.test.cpp"
// BEGIN: monoid/min.hpp
#line 3 "monoid/min.hpp"

#include <algorithm>
#include <limits>

namespace m1une {
namespace monoid {

// Monoid for minimum (Range Minimum).
// The identity element defaults to the maximum possible value of type T, but can be overridden.
template <typename T, T Id = std::numeric_limits<T>::max()>
struct Min {
    using value_type = T;

    // Returns the identity element for minimum.
    static constexpr T id() { return Id; }

    // Returns the minimum of a and b.
    static constexpr T op(const T& a, const T& b) { return std::min(a, b); }
};

}  // namespace monoid
}  // namespace m1une

// END: monoid/min.hpp
#line 5 "verify/data_structure/sparse_table.test.cpp"

#include <iostream>
#include <vector>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    int N, Q;
    std::cin >> N >> Q;

    std::vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    m1une::data_structure::SparseTable<m1une::monoid::Min<long long>> st(A);

    for (int q = 0; q < Q; ++q) {
        int l, r;
        std::cin >> l >> r;
        
        std::cout << st.prod(l, r) << "\n";
    }

    return 0;
}
// END: verify/data_structure/sparse_table.test.cpp
