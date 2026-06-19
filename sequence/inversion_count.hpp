#ifndef M1UNE_SEQUENCE_INVERSION_COUNT_HPP
#define M1UNE_SEQUENCE_INVERSION_COUNT_HPP 1

#include <vector>

namespace m1une {
namespace sequence {

// Returns the number of pairs (i, j) with i < j and a[i] > a[j].
// The vector is taken by value because merge sort rearranges it.
template <typename T>
long long inversion_count(std::vector<T> a) {
    const int n = int(a.size());
    std::vector<T> temp = a;

    auto merge_sort = [&](auto& self, int l, int r) -> long long {
        if (r - l <= 1) return 0;

        const int m = l + (r - l) / 2;
        long long inv = self(self, l, m) + self(self, m, r);

        int i = l;
        int j = m;
        int k = l;
        while (i < m && j < r) {
            if (!(a[j] < a[i])) {
                temp[k++] = a[i++];
            } else {
                temp[k++] = a[j++];
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
