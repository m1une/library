#ifndef M1UNE_SEQUENCE_INVERSION_COUNT_HPP
#define M1UNE_SEQUENCE_INVERSION_COUNT_HPP 1

#include <vector>

namespace m1une {
namespace sequence {

// Calculates the number of inversions in the array.
// Takes the vector by value because the merge sort process mutates it.
// If you don't need the original array, you can pass it with std::move().
template <typename T>
long long inversion_count(std::vector<T> a) {
    int n = a.size();
    std::vector<T> temp(n);

    // Recursive lambda for merge sort
    auto merge_sort = [&](auto& self, int l, int r) -> long long {
        if (r - l <= 1) return 0;
        
        int m = l + (r - l) / 2;
        long long inv = self(self, l, m) + self(self, m, r);
        
        int i = l, j = m, k = l;
        while (i < m && j < r) {
            if (a[i] <= a[j]) {
                temp[k++] = a[i++];
            } else {
                temp[k++] = a[j++];
                // All remaining elements in the left half are strictly greater than a[j]
                inv += m - i;
            }
        }
        
        while (i < m) temp[k++] = a[i++];
        while (j < r) temp[k++] = a[j++];
        
        for (int p = l; p < r; ++p) {
            a[p] = temp[p];
        }
        
        return inv;
    };

    return merge_sort(merge_sort, 0, n);
}

}  // namespace sequence
}  // namespace m1une

#endif  // M1UNE_SEQUENCE_INVERSION_COUNT_HPP
