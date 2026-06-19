#ifndef M1UNE_SEQUENCE_LIS_HPP
#define M1UNE_SEQUENCE_LIS_HPP 1

#include <algorithm>
#include <iterator>
#include <vector>

namespace m1une {
namespace sequence {

// Returns the zero-based indices of a longest increasing subsequence.
// If `strict` is false, equal adjacent values are also allowed.
template <typename T>
std::vector<int> lis(const std::vector<T>& a, bool strict = true) {
    const int n = int(a.size());
    std::vector<T> tails;
    std::vector<int> tail_positions;
    std::vector<int> predecessor(n, -1);
    tails.reserve(n);
    tail_positions.reserve(n);

    for (int i = 0; i < n; ++i) {
        auto it = strict ? std::lower_bound(tails.begin(), tails.end(), a[i])
                         : std::upper_bound(tails.begin(), tails.end(), a[i]);
        const int length = int(std::distance(tails.begin(), it));

        if (it == tails.end()) {
            tails.push_back(a[i]);
            tail_positions.push_back(i);
        } else {
            *it = a[i];
            tail_positions[length] = i;
        }

        if (length > 0) {
            predecessor[i] = tail_positions[length - 1];
        }
    }

    if (tail_positions.empty()) return {};

    std::vector<int> result;
    result.reserve(tail_positions.size());
    int current = tail_positions.back();
    while (current != -1) {
        result.push_back(current);
        current = predecessor[current];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace sequence
}  // namespace m1une

#endif  // M1UNE_SEQUENCE_LIS_HPP
