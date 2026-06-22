#ifndef M1UNE_OPTIMIZATION_ALIEN_TRICK_HPP
#define M1UNE_OPTIMIZATION_ALIEN_TRICK_HPP 1

#include <cassert>
#include <concepts>
#include <numeric>
#include <type_traits>
#include <utility>

namespace m1une {
namespace optimization {

namespace detail {

template <std::integral Penalty, std::integral Count, class Oracle>
Penalty alien_trick_penalty(Penalty lower, Penalty upper, Count target_count, Oracle& oracle) {
    assert(lower <= upper);
    assert(oracle(lower).second >= target_count);
    assert(oracle(upper).second <= target_count);

    while (lower < upper) {
        Penalty middle = std::midpoint(lower, upper);
        if (middle == lower) ++middle;
        if (oracle(middle).second >= target_count) {
            lower = middle;
        } else {
            upper = middle - 1;
        }
    }
    return lower;
}

}  // namespace detail

// Recovers the minimum value among solutions using exactly `target_count`
// items. The oracle minimizes value + penalty * count and breaks ties in favor
// of the larger count.
template <std::integral Penalty, std::integral Count, class Oracle>
auto alien_trick_minimize(Penalty lower, Penalty upper, Count target_count, Oracle oracle) {
    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count, oracle);
    auto result = oracle(penalty);
    using Value = std::remove_cvref_t<decltype(result.first)>;
    return result.first - static_cast<Value>(penalty) * static_cast<Value>(target_count);
}

// Recovers the maximum value among solutions using exactly `target_count`
// items. The oracle maximizes value - penalty * count and breaks ties in favor
// of the larger count.
template <std::integral Penalty, std::integral Count, class Oracle>
auto alien_trick_maximize(Penalty lower, Penalty upper, Count target_count, Oracle oracle) {
    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count, oracle);
    auto result = oracle(penalty);
    using Value = std::remove_cvref_t<decltype(result.first)>;
    return result.first + static_cast<Value>(penalty) * static_cast<Value>(target_count);
}

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_ALIEN_TRICK_HPP
