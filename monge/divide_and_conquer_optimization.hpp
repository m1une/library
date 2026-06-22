#ifndef M1UNE_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP
#define M1UNE_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP 1

#include <type_traits>
#include <utility>
#include <vector>

#include "monotone_minima.hpp"

namespace m1une {
namespace monge {

template <class T>
struct DivideAndConquerDpResult {
    std::vector<T> value;
    std::vector<int> argmin;
};

template <class Value>
auto divide_and_conquer_dp(int state_count, int candidate_count, Value value)
    -> DivideAndConquerDpResult<
        std::decay_t<std::invoke_result_t<Value, int, int>>> {
    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;
    DivideAndConquerDpResult<T> result;
    result.argmin = monotone_row_argmin(state_count, candidate_count, value);
    result.value.resize(state_count);
    for (int state = 0; state < state_count; state++) {
        if (result.argmin[state] != -1) {
            result.value[state] = value(state, result.argmin[state]);
        }
    }
    return result;
}

template <class T, class Cost>
auto divide_and_conquer_transition(const std::vector<T>& previous, int state_count,
                                   Cost cost)
    -> DivideAndConquerDpResult<
        std::decay_t<decltype(std::declval<T>() + cost(0, 0))>> {
    using Result = std::decay_t<decltype(std::declval<T>() + cost(0, 0))>;
    return divide_and_conquer_dp(
        state_count, int(previous.size()),
        [&](int state, int candidate) -> Result {
            return previous[candidate] + cost(candidate, state);
        });
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_DIVIDE_AND_CONQUER_OPTIMIZATION_HPP
