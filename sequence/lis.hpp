#ifndef M1UNE_SEQUENCE_LIS_HPP
#define M1UNE_SEQUENCE_LIS_HPP 1

#include <vector>
#include <algorithm>

namespace m1une {
namespace sequence {

// Returns the 0-indexed positions (indices) of the longest increasing subsequence.
// If 'strict' is true, it finds a strictly increasing subsequence (a[i] < a[j]).
// If 'strict' is false, it finds a non-decreasing subsequence (a[i] <= a[j]).
template <typename T>
std::vector<int> lis(const std::vector<T>& a, bool strict = true) {
    int n = a.size();
    std::vector<T> dp;
    std::vector<int> pos;
    std::vector<int> prev(n, -1);

    for (int i = 0; i < n; ++i) {
        auto it = strict ? std::lower_bound(dp.begin(), dp.end(), a[i])
                         : std::upper_bound(dp.begin(), dp.end(), a[i]);
        int d = std::distance(dp.begin(), it);
        
        if (it == dp.end()) {
            dp.push_back(a[i]);
            pos.push_back(i);
        } else {
            *it = a[i];
            pos[d] = i;
        }
        
        if (d > 0) {
            prev[i] = pos[d - 1];
        }
    }

    if (pos.empty()) return {};

    // Reconstruct the indices of the sequence
    std::vector<int> res;
    int curr = pos.back();
    while (curr != -1) {
        res.push_back(curr);
        curr = prev[curr];
    }
    std::reverse(res.begin(), res.end());
    
    return res;
}

}  // namespace sequence
}  // namespace m1une

#endif  // M1UNE_SEQUENCE_LIS_HPP
