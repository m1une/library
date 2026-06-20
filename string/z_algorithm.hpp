#ifndef M1UNE_STRING_Z_ALGORITHM_HPP
#define M1UNE_STRING_Z_ALGORITHM_HPP 1

#include <algorithm>
#include <vector>

namespace m1une {
namespace string {

// Returns z[i] = LCP(sequence, sequence[i..]).
template <class Sequence>
std::vector<int> z_algorithm(const Sequence& sequence) {
    int n = int(sequence.size());
    if (n == 0) return {};

    std::vector<int> z(n);
    z[0] = n;
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; i++) {
        if (i < right) z[i] = std::min(right - i, z[i - left]);
        while (i + z[i] < n && sequence[z[i]] == sequence[i + z[i]]) {
            z[i]++;
        }
        if (right < i + z[i]) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_Z_ALGORITHM_HPP
