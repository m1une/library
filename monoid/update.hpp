#ifndef M1UNE_MONOID_UPDATE_HPP
#define M1UNE_MONOID_UPDATE_HPP 1

#include <optional>

namespace m1une {
namespace monoid {

// Monoid for range updates/assignments.
// Uses std::optional to represent the presence of an assignment.
template <typename T>
struct Update {
    using value_type = std::optional<T>;

    // The identity element represents "no operation".
    static constexpr value_type id() { 
        return std::nullopt; 
    }

    // Composes two updates. The newer operation 'a' overwrites the older 'b'.
    // If 'a' does not exist, it falls back to 'b'.
    static constexpr value_type op(const value_type& a, const value_type& b) { 
        return a.has_value() ? a : b; 
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_UPDATE_HPP
