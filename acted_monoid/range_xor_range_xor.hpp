#ifndef M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP
#define M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP 1

namespace m1une {
namespace acted_monoid {

template <typename T>
struct RangeXorRangeXorNode {
    T val;
    long long size;
};

template <typename T>
struct RangeXorRangeXor {
    using value_type = RangeXorRangeXorNode<T>;
    using operator_type = T;

    static constexpr value_type id() {
        return {T(0), 0};
    }
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.val ^ b.val, a.size + b.size};
    }

    static constexpr operator_type op_id() {
        return T(0);
    }
    static constexpr operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f ^ g;
    }

    static constexpr value_type mapping(const operator_type& f, const value_type& x) {
        if (x.size % 2 == 1) {
            return {x.val ^ f, x.size};
        }
        return x;
    }

    static constexpr value_type make(const T& val) {
        return {val, 1};
    }
};

}  // namespace acted_monoid
}  // namespace m1une

#endif  // M1UNE_ACTED_MONOID_RANGE_XOR_RANGE_XOR_HPP
