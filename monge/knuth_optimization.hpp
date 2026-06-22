#ifndef M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP
#define M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP 1

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <vector>

namespace m1une {
namespace monge {

template <class T>
struct KnuthOptimizationResult {
    std::vector<std::vector<T>> value;
    std::vector<std::vector<int>> split;

    T optimum() const {
        return value[0].back();
    }
};

template <class IntervalCost>
auto knuth_optimization(int element_count, IntervalCost interval_cost)
    -> KnuthOptimizationResult<
        std::decay_t<std::invoke_result_t<IntervalCost, int, int>>> {
    assert(element_count >= 0);
    using T = std::decay_t<std::invoke_result_t<IntervalCost, int, int>>;

    KnuthOptimizationResult<T> result;
    result.value.assign(element_count + 1, std::vector<T>(element_count + 1, T()));
    result.split.assign(element_count + 1, std::vector<int>(element_count + 1, -1));

    for (int left = 0; left <= element_count; left++) result.split[left][left] = left;
    for (int left = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;

    for (int length = 2; length <= element_count; length++) {
        for (int left = 0; left + length <= element_count; left++) {
            int right = left + length;
            int first = std::max(left + 1, result.split[left][right - 1]);
            int last = std::min(right - 1, result.split[left + 1][right]);
            assert(first <= last);

            int best = first;
            T best_value = result.value[left][best] + result.value[best][right];
            for (int split = first + 1; split <= last; split++) {
                T candidate = result.value[left][split] + result.value[split][right];
                if (candidate < best_value) {
                    best = split;
                    best_value = candidate;
                }
            }
            result.value[left][right] = best_value + interval_cost(left, right);
            result.split[left][right] = best;
        }
    }
    return result;
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_KNUTH_OPTIMIZATION_HPP
