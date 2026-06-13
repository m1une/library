#ifndef M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP
#define M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP 1

#include <array>

namespace m1une {
namespace acted_monoid {

template <typename T, int BITS = 30>
struct RangeXorRangeSumNode {
    T sum;
    std::array<int, BITS> bit_count;
    long long size;
};

// Acted Monoid for Range XOR updates and Range Sum queries.
// BITS defines the maximum bit length (default 30 for standard integers, use 60 for long long).
template <typename T, int BITS = 30>
struct RangeXorRangeSum {
    using value_type = RangeXorRangeSumNode<T, BITS>;
    using operator_type = T;

    static constexpr value_type id() {
        value_type res;
        res.sum = T(0);
        res.bit_count.fill(0);
        res.size = 0;
        return res;
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res;
        res.sum = a.sum + b.sum;
        res.size = a.size + b.size;
        for (int i = 0; i < BITS; ++i) {
            res.bit_count[i] = a.bit_count[i] + b.bit_count[i];
        }
        return res;
    }

    static constexpr operator_type op_id() {
        return T(0);
    }

    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f ^ g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (f == T(0) || x.size == 0) return x;
        value_type res = x;
        res.sum = T(0);
        for (int i = 0; i < BITS; ++i) {
            if ((f >> i) & 1) {
                res.bit_count[i] = x.size - x.bit_count[i];
            }
            res.sum += static_cast<T>(res.bit_count[i]) * (T(1) << i);
        }
        return res;
    }

    static constexpr value_type make(const T& val) {
        value_type res;
        res.sum = val;
        res.size = 1;
        for (int i = 0; i < BITS; ++i) {
            res.bit_count[i] = ((val >> i) & 1) ? 1 : 0;
        }
        return res;
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_SUM_HPP
