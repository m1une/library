#ifndef M1UNE_MATH_BITWISE_CONVOLUTION_HPP
#define M1UNE_MATH_BITWISE_CONVOLUTION_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "zeta_mobius_transform.hpp"

namespace m1une {
namespace math {

namespace bitwise_convolution_detail {

inline std::size_t common_size(
    std::size_t first_size,
    std::size_t second_size
) {
    std::size_t required = first_size > second_size
        ? first_size
        : second_size;
    std::size_t size = 1;
    while (size < required) size <<= 1;
    return size;
}

template <typename T>
std::vector<T> pointwise_product(
    std::vector<T> first,
    const std::vector<T>& second
) {
    assert(first.size() == second.size());
    for (std::size_t index = 0; index < first.size(); ++index) {
        first[index] *= second[index];
    }
    return first;
}

}  // namespace bitwise_convolution_detail

template <typename T>
void walsh_hadamard_transform(
    std::vector<T>& values,
    bool inverse = false
) {
    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));
    for (std::size_t length = 1; length < values.size(); length <<= 1) {
        for (
            std::size_t block = 0;
            block < values.size();
            block += length << 1
        ) {
            for (std::size_t offset = 0; offset < length; ++offset) {
                T first = values[block + offset];
                T second = values[block + offset + length];
                values[block + offset] = first + second;
                values[block + offset + length] = first - second;
            }
        }
    }
    if (inverse) {
        T size = T(static_cast<long long>(values.size()));
        for (T& value : values) value /= size;
    }
}

template <typename T>
std::vector<T> bitwise_or_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    if (first.empty() || second.empty()) return {};
    std::size_t size = bitwise_convolution_detail::common_size(
        first.size(),
        second.size()
    );
    first.resize(size);
    second.resize(size);
    subset_zeta_transform(first);
    subset_zeta_transform(second);
    first = bitwise_convolution_detail::pointwise_product(
        std::move(first),
        second
    );
    subset_mobius_transform(first);
    return first;
}

template <typename T>
std::vector<T> bitwise_and_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    if (first.empty() || second.empty()) return {};
    std::size_t size = bitwise_convolution_detail::common_size(
        first.size(),
        second.size()
    );
    first.resize(size);
    second.resize(size);
    superset_zeta_transform(first);
    superset_zeta_transform(second);
    first = bitwise_convolution_detail::pointwise_product(
        std::move(first),
        second
    );
    superset_mobius_transform(first);
    return first;
}

template <typename T>
std::vector<T> bitwise_xor_convolution(
    std::vector<T> first,
    std::vector<T> second
) {
    if (first.empty() || second.empty()) return {};
    std::size_t size = bitwise_convolution_detail::common_size(
        first.size(),
        second.size()
    );
    first.resize(size);
    second.resize(size);
    walsh_hadamard_transform(first);
    walsh_hadamard_transform(second);
    first = bitwise_convolution_detail::pointwise_product(
        std::move(first),
        second
    );
    walsh_hadamard_transform(first, true);
    return first;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_BITWISE_CONVOLUTION_HPP
