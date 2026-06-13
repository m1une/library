#ifndef M1UNE_MONOID_STRICT_MIN2_HPP
#define M1UNE_MONOID_STRICT_MIN2_HPP 1

#include <functional>
#include <limits>

namespace m1une {
namespace monoid {

template <typename T>
struct StrictOpt2Node {
    T opt1;  // The strictly best value
    T opt2;  // The strictly second-best value
};

// Monoid for finding the strictly 1st and 2nd optimal (minimum by default) values in a range.
template <typename T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>
struct StrictMin2 {
    using value_type = StrictOpt2Node<T>;

    // The identity element has both values set to Id.
    static constexpr value_type id() {
        return {Id, Id};
    }

    // Merges two elements, preserving the top 2 strictly unique values.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        auto update = [](T& m1, T& m2, T val) {
            if (val == Id || val == m1 || val == m2) return;
            if (m1 == Id || Compare()(val, m1)) {
                m2 = m1;
                m1 = val;
            } else if (m2 == Id || Compare()(val, m2)) {
                m2 = val;
            }
        };

        T m1 = Id, m2 = Id;
        update(m1, m2, a.opt1);
        update(m1, m2, a.opt2);
        update(m1, m2, b.opt1);
        update(m1, m2, b.opt2);

        return {m1, m2};
    }

    // Helper to securely create a leaf node.
    static constexpr value_type make(const T& val) {
        return {val, Id};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_STRICT_MIN2_HPP
