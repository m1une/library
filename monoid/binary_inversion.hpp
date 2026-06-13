#ifndef M1UNE_MONOID_BINARY_INVERSION_HPP
#define M1UNE_MONOID_BINARY_INVERSION_HPP 1

namespace m1une {
namespace monoid {

template <typename T = long long>
struct BinaryInversionNode {
    long long zeros;
    long long ones;
    T inversions;
};

// Monoid for counting zeros, ones, and inversions (1s before 0s) in a binary array.
template <typename T = long long>
struct BinaryInversion {
    using value_type = BinaryInversionNode<T>;

    // The identity element has 0 zeros, 0 ones, and 0 inversions.
    static constexpr value_type id() {
        return {0, 0, 0};
    }

    // Merges two segments and calculates the new inversions.
    // New inversions = left inversions + right inversions + (ones in left * zeros in right)
    static constexpr value_type op(const value_type& a, const value_type& b) {
        return {a.zeros + b.zeros, a.ones + b.ones, a.inversions + b.inversions + a.ones * b.zeros};
    }

    // Helper to securely create a leaf node from a value (0 or 1).
    static constexpr value_type make(int val) {
        if (val == 0) return {1, 0, 0};
        return {0, 1, 0};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_BINARY_INVERSION_HPP
