#ifndef M1UNE_FPS_FLOATING_POINT_CONVOLUTION_HPP
#define M1UNE_FPS_FLOATING_POINT_CONVOLUTION_HPP 1

#include <algorithm>
#include <bit>
#include <cmath>
#include <complex>
#include <concepts>
#include <numbers>
#include <type_traits>
#include <vector>

namespace m1une {
namespace fps {

namespace floating_point_convolution_detail {

template <std::floating_point Real>
void fft(std::vector<std::complex<Real>>& values, bool inverse) {
    int size = int(values.size());
    for (int index = 1, reversed = 0; index < size; ++index) {
        int bit = size >> 1;
        while (reversed & bit) {
            reversed ^= bit;
            bit >>= 1;
        }
        reversed ^= bit;
        if (index < reversed) std::swap(values[index], values[reversed]);
    }

    for (int length = 2; length <= size; length <<= 1) {
        Real angle = Real(2) * std::numbers::pi_v<Real> / Real(length);
        if (inverse) angle = -angle;
        std::complex<Real> step(std::cos(angle), std::sin(angle));
        int half = length >> 1;
        for (int offset = 0; offset < size; offset += length) {
            std::complex<Real> root(1, 0);
            for (int index = 0; index < half; ++index) {
                std::complex<Real> even = values[offset + index];
                std::complex<Real> odd = values[offset + index + half] * root;
                values[offset + index] = even + odd;
                values[offset + index + half] = even - odd;
                root *= step;
            }
        }
    }

    if (inverse) {
        Real inverse_size = Real(1) / Real(size);
        for (auto& value : values) value *= inverse_size;
    }
}

template <std::floating_point Real>
std::vector<std::complex<Real>> complex_convolution(const std::vector<std::complex<Real>>& first,
                                                    const std::vector<std::complex<Real>>& second) {
    if (first.empty() || second.empty()) return {};
    std::size_t result_size = first.size() + second.size() - 1;
    std::size_t size = std::bit_ceil(result_size);
    std::vector<std::complex<Real>> transformed_first(size);
    std::vector<std::complex<Real>> transformed_second(size);
    std::copy(first.begin(), first.end(), transformed_first.begin());
    std::copy(second.begin(), second.end(), transformed_second.begin());

    fft(transformed_first, false);
    fft(transformed_second, false);
    for (std::size_t index = 0; index < size; ++index) {
        transformed_first[index] *= transformed_second[index];
    }
    fft(transformed_first, true);
    transformed_first.resize(result_size);
    return transformed_first;
}

}  // namespace floating_point_convolution_detail

// Convolution of complex floating-point coefficients.
template <std::floating_point Real>
std::vector<std::complex<Real>> convolution_fft(const std::vector<std::complex<Real>>& first,
                                                const std::vector<std::complex<Real>>& second) {
    return floating_point_convolution_detail::complex_convolution(first, second);
}

// Convolution of real floating-point coefficients.
template <std::floating_point Real>
std::vector<Real> convolution_fft(const std::vector<Real>& first, const std::vector<Real>& second) {
    if (first.empty() || second.empty()) return {};
    std::vector<std::complex<Real>> complex_first(first.size());
    std::vector<std::complex<Real>> complex_second(second.size());
    for (std::size_t index = 0; index < first.size(); ++index) {
        complex_first[index] = std::complex<Real>(first[index], 0);
    }
    for (std::size_t index = 0; index < second.size(); ++index) {
        complex_second[index] = std::complex<Real>(second[index], 0);
    }
    auto result = floating_point_convolution_detail::complex_convolution(complex_first, complex_second);
    std::vector<Real> real_result(result.size());
    for (std::size_t index = 0; index < result.size(); ++index) {
        real_result[index] = result[index].real();
    }
    return real_result;
}

// Uses long-double FFT and rounds each coefficient to the nearest integer.
template <std::integral Integer>
std::vector<Integer> convolution_round(const std::vector<Integer>& first, const std::vector<Integer>& second) {
    if (first.empty() || second.empty()) return {};
    std::vector<long double> real_first(first.begin(), first.end());
    std::vector<long double> real_second(second.begin(), second.end());
    std::vector<long double> real_result = convolution_fft(real_first, real_second);
    std::vector<Integer> result(real_result.size());
    for (std::size_t index = 0; index < result.size(); ++index) {
        result[index] = static_cast<Integer>(std::round(real_result[index]));
    }
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_FLOATING_POINT_CONVOLUTION_HPP
