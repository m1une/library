#ifndef M1UNE_MONOID_TOP_K_COUNT_HPP
#define M1UNE_MONOID_TOP_K_COUNT_HPP 1

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

namespace m1une {
namespace monoid {

// Monoid for finding the top K distinct elements and their frequencies in a range.
// The default Compare is std::greater<T> (descending order for Top K).
template <typename T, int K, typename Compare = std::greater<T>>
struct TopKCount {
    using value_type = std::vector<std::pair<T, int>>;

    static constexpr value_type id() {
        return value_type();
    }

    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res;
        res.reserve(std::min(K, (int)(a.size() + b.size())));

        int i = 0, j = 0;
        while (res.size() < (std::size_t)K && (i < (int)a.size() || j < (int)b.size())) {
            if (i == (int)a.size()) {
                res.push_back(b[j++]);
            } else if (j == (int)b.size()) {
                res.push_back(a[i++]);
            } else if (a[i].first == b[j].first) {
                // If the values are identical, merge their counts
                res.push_back({a[i].first, a[i].second + b[j].second});
                i++;
                j++;
            } else if (Compare()(a[i].first, b[j].first)) {
                res.push_back(a[i++]);
            } else {
                res.push_back(b[j++]);
            }
        }
        return res;
    }

    // Helper to securely create a leaf node from a single value.
    static constexpr value_type make(const T& val, int count = 1) {
        return value_type{std::pair<T, int>{val, count}};
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_TOP_K_COUNT_HPP
