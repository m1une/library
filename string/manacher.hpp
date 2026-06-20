#ifndef M1UNE_STRING_MANACHER_HPP
#define M1UNE_STRING_MANACHER_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace string {

struct ManacherResult {
    // odd[i] is the radius including center i.
    // The palindrome is [i - odd[i] + 1, i + odd[i]).
    std::vector<int> odd;

    // even[i] is the radius centered between i - 1 and i.
    // The palindrome is [i - even[i], i + even[i]).
    std::vector<int> even;

    int size() const {
        return int(odd.size());
    }

    bool empty() const {
        return odd.empty();
    }

    bool is_palindrome(int left, int right) const {
        int n = size();
        assert(0 <= left && left <= right && right <= n);
        int length = right - left;
        if (length == 0) return true;
        if (length & 1) {
            int center = (left + right) / 2;
            return length / 2 + 1 <= odd[center];
        }
        int center = (left + right) / 2;
        return length / 2 <= even[center];
    }

    int longest_length() const {
        int result = 0;
        for (int radius : odd) result = std::max(result, 2 * radius - 1);
        for (int radius : even) result = std::max(result, 2 * radius);
        return result;
    }
};

template <class Sequence>
ManacherResult manacher(const Sequence& sequence) {
    int n = int(sequence.size());
    ManacherResult result;
    result.odd.assign(n, 0);
    result.even.assign(n, 0);

    int left = 0;
    int right = -1;
    for (int i = 0; i < n; i++) {
        int radius = i > right ? 1 : std::min(result.odd[left + right - i], right - i + 1);
        while (
            0 <= i - radius &&
            i + radius < n &&
            sequence[i - radius] == sequence[i + radius]
        ) {
            radius++;
        }
        result.odd[i] = radius;
        if (right < i + radius - 1) {
            left = i - radius + 1;
            right = i + radius - 1;
        }
    }

    left = 0;
    right = -1;
    for (int i = 0; i < n; i++) {
        int radius = i > right ? 0 : std::min(result.even[left + right - i + 1], right - i + 1);
        while (
            0 <= i - radius - 1 &&
            i + radius < n &&
            sequence[i - radius - 1] == sequence[i + radius]
        ) {
            radius++;
        }
        result.even[i] = radius;
        if (right < i + radius - 1) {
            left = i - radius;
            right = i + radius - 1;
        }
    }
    return result;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_MANACHER_HPP
