#ifndef M1UNE_RUN_LENGTH_ENCODING_HPP
#define M1UNE_RUN_LENGTH_ENCODING_HPP 1

#include <iterator>
#include <utility>
#include <vector>

namespace m1une {
namespace utilities {

template <typename Container>
auto run_length_encoding(const Container& values) {
    using T = typename Container::value_type;
    std::vector<std::pair<T, long long>> result;

    auto it = std::begin(values);
    auto last = std::end(values);
    if (it == last) {
        return result;
    }

    T current = *it;
    long long count = 0;
    for (; it != last; ++it) {
        if (*it == current) {
            ++count;
        } else {
            result.emplace_back(current, count);
            current = *it;
            count = 1;
        }
    }
    result.emplace_back(current, count);
    return result;
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_RUN_LENGTH_ENCODING_HPP
