#ifndef M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
#define M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP 1

#include <functional>
#include <vector>

namespace m1une {
namespace monge {

namespace convolution_detail {

template <class T, class Compare>
std::vector<T> structured_convolution(const std::vector<T>& arbitrary,
                                      const std::vector<T>& structured,
                                      Compare compare) {
    if (arbitrary.empty() || structured.empty()) return {};

    int first_size = int(arbitrary.size());
    int second_size = int(structured.size());
    int result_size = first_size + second_size - 1;
    std::vector<T> result(result_size);

    auto solve = [&](auto self, int result_left, int result_right, int candidate_left,
                     int candidate_right) -> void {
        if (result_left == result_right) return;
        int index = (result_left + result_right) / 2;
        int left = candidate_left > index - second_size + 1 ? candidate_left
                                                            : index - second_size + 1;
        int right = candidate_right < index + 1 ? candidate_right : index + 1;

        int best = left;
        T best_value = arbitrary[best] + structured[index - best];
        for (int candidate = left + 1; candidate < right; candidate++) {
            T current = arbitrary[candidate] + structured[index - candidate];
            if (compare(current, best_value)) {
                best = candidate;
                best_value = current;
            }
        }
        result[index] = best_value;
        self(self, result_left, index, candidate_left, best + 1);
        self(self, index + 1, result_right, best, candidate_right);
    };

    solve(solve, 0, result_size, 0, first_size);
    return result;
}

}  // namespace convolution_detail

template <class T>
bool is_convex_sequence(const std::vector<T>& sequence) {
    for (int i = 1; i + 1 < int(sequence.size()); i++) {
        if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence) {
    for (int i = 1; i + 1 < int(sequence.size()); i++) {
        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,
                                           const std::vector<T>& convex) {
    return convolution_detail::structured_convolution(arbitrary, convex, std::less<>());
}

template <class T>
std::vector<T> max_plus_convolution_concave(const std::vector<T>& arbitrary,
                                            const std::vector<T>& concave) {
    return convolution_detail::structured_convolution(arbitrary, concave, std::greater<>());
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_MIN_PLUS_CONVOLUTION_HPP
