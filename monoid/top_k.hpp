#ifndef M1UNE_MONOID_TOP_K_HPP
#define M1UNE_MONOID_TOP_K_HPP 1

#include <vector>
#include <algorithm>

namespace m1une {
namespace monoid {

// Monoid for finding the top K elements in a range.
// The elements must be stored in descending order.
template <typename T, int K>
struct TopK {
    using value_type = std::vector<T>;

    // The identity element is an empty vector.
    static constexpr value_type id() { 
        return std::vector<T>(); 
    }

    // Merges two sorted vectors and keeps only the top K elements.
    static constexpr value_type op(const value_type& a, const value_type& b) {
        value_type res;
        res.reserve(std::min(K, (int)(a.size() + b.size())));
        
        int i = 0, j = 0;
        while (res.size() < K && (i < (int)a.size() || j < (int)b.size())) {
            if (i == (int)a.size()) {
                res.push_back(b[j++]);
            } else if (j == (int)b.size()) {
                res.push_back(a[i++]);
            } else if (a[i] > b[j]) { // Assuming we want the largest elements
                res.push_back(a[i++]);
            } else {
                res.push_back(b[j++]);
            }
        }
        return res;
    }
};

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_TOP_K_HPP
