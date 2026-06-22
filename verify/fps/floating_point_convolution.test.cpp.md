---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/fps/floating_point_convolution.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"fps/floating_point_convolution.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cmath>\n#include <complex>\n\
    #include <concepts>\n#include <numbers>\n#include <type_traits>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace fps {\n\nnamespace floating_point_convolution_detail\
    \ {\n\ntemplate <std::floating_point Real>\nvoid fft(std::vector<std::complex<Real>>&\
    \ values, bool inverse) {\n    int size = int(values.size());\n    for (int index\
    \ = 1, reversed = 0; index < size; ++index) {\n        int bit = size >> 1;\n\
    \        while (reversed & bit) {\n            reversed ^= bit;\n            bit\
    \ >>= 1;\n        }\n        reversed ^= bit;\n        if (index < reversed) std::swap(values[index],\
    \ values[reversed]);\n    }\n\n    for (int length = 2; length <= size; length\
    \ <<= 1) {\n        Real angle = Real(2) * std::numbers::pi_v<Real> / Real(length);\n\
    \        if (inverse) angle = -angle;\n        std::complex<Real> step(std::cos(angle),\
    \ std::sin(angle));\n        int half = length >> 1;\n        for (int offset\
    \ = 0; offset < size; offset += length) {\n            std::complex<Real> root(1,\
    \ 0);\n            for (int index = 0; index < half; ++index) {\n            \
    \    std::complex<Real> even = values[offset + index];\n                std::complex<Real>\
    \ odd = values[offset + index + half] * root;\n                values[offset +\
    \ index] = even + odd;\n                values[offset + index + half] = even -\
    \ odd;\n                root *= step;\n            }\n        }\n    }\n\n   \
    \ if (inverse) {\n        Real inverse_size = Real(1) / Real(size);\n        for\
    \ (auto& value : values) value *= inverse_size;\n    }\n}\n\ntemplate <std::floating_point\
    \ Real>\nstd::vector<std::complex<Real>> complex_convolution(const std::vector<std::complex<Real>>&\
    \ first,\n                                                    const std::vector<std::complex<Real>>&\
    \ second) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ result_size = first.size() + second.size() - 1;\n    std::size_t size = std::bit_ceil(result_size);\n\
    \    std::vector<std::complex<Real>> transformed_first(size);\n    std::vector<std::complex<Real>>\
    \ transformed_second(size);\n    std::copy(first.begin(), first.end(), transformed_first.begin());\n\
    \    std::copy(second.begin(), second.end(), transformed_second.begin());\n\n\
    \    fft(transformed_first, false);\n    fft(transformed_second, false);\n   \
    \ for (std::size_t index = 0; index < size; ++index) {\n        transformed_first[index]\
    \ *= transformed_second[index];\n    }\n    fft(transformed_first, true);\n  \
    \  transformed_first.resize(result_size);\n    return transformed_first;\n}\n\n\
    }  // namespace floating_point_convolution_detail\n\n// Convolution of complex\
    \ floating-point coefficients.\ntemplate <std::floating_point Real>\nstd::vector<std::complex<Real>>\
    \ convolution_fft(const std::vector<std::complex<Real>>& first,\n            \
    \                                    const std::vector<std::complex<Real>>& second)\
    \ {\n    return floating_point_convolution_detail::complex_convolution(first,\
    \ second);\n}\n\n// Convolution of real floating-point coefficients.\ntemplate\
    \ <std::floating_point Real>\nstd::vector<Real> convolution_fft(const std::vector<Real>&\
    \ first, const std::vector<Real>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<std::complex<Real>> complex_first(first.size());\n\
    \    std::vector<std::complex<Real>> complex_second(second.size());\n    for (std::size_t\
    \ index = 0; index < first.size(); ++index) {\n        complex_first[index] =\
    \ std::complex<Real>(first[index], 0);\n    }\n    for (std::size_t index = 0;\
    \ index < second.size(); ++index) {\n        complex_second[index] = std::complex<Real>(second[index],\
    \ 0);\n    }\n    auto result = floating_point_convolution_detail::complex_convolution(complex_first,\
    \ complex_second);\n    std::vector<Real> real_result(result.size());\n    for\
    \ (std::size_t index = 0; index < result.size(); ++index) {\n        real_result[index]\
    \ = result[index].real();\n    }\n    return real_result;\n}\n\n// Uses long-double\
    \ FFT and rounds each coefficient to the nearest integer.\ntemplate <std::integral\
    \ Integer>\nstd::vector<Integer> convolution_round(const std::vector<Integer>&\
    \ first, const std::vector<Integer>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<long double> real_first(first.begin(), first.end());\n\
    \    std::vector<long double> real_second(second.begin(), second.end());\n   \
    \ std::vector<long double> real_result = convolution_fft(real_first, real_second);\n\
    \    std::vector<Integer> result(real_result.size());\n    for (std::size_t index\
    \ = 0; index < result.size(); ++index) {\n        result[index] = static_cast<Integer>(std::round(real_result[index]));\n\
    \    }\n    return result;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\
    \n#line 4 \"verify/fps/floating_point_convolution.test.cpp\"\n\n#line 6 \"verify/fps/floating_point_convolution.test.cpp\"\
    \n#include <cassert>\n#line 9 \"verify/fps/floating_point_convolution.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 12 \"verify/fps/floating_point_convolution.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class T>\nstd::vector<T> naive(\n    const std::vector<T>&\
    \ first,\n    const std::vector<T>& second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<T> result(first.size() + second.size() - 1);\n \
    \   for (std::size_t i = 0; i < first.size(); ++i) {\n        for (std::size_t\
    \ j = 0; j < second.size(); ++j) {\n            result[i + j] += first[i] * second[j];\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_fixed() {\n    std::vector<double>\
    \ first = {1.5, 2.0};\n    std::vector<double> second = {3.0, -1.0};\n    auto\
    \ result = m1une::fps::convolution_fft(first, second);\n    assert(std::fabs(result[0]\
    \ - 4.5) < 1e-12);\n    assert(std::fabs(result[1] - 4.5) < 1e-12);\n    assert(std::fabs(result[2]\
    \ + 2.0) < 1e-12);\n\n    std::vector<std::complex<double>> complex_first;\n \
    \   complex_first.emplace_back(1, 2);\n    complex_first.emplace_back(3, -1);\n\
    \    std::vector<std::complex<double>> complex_second;\n    complex_second.emplace_back(-2,\
    \ 1);\n    complex_second.emplace_back(0, 4);\n    auto complex_result =\n   \
    \     m1une::fps::convolution_fft(complex_first, complex_second);\n    auto complex_expected\
    \ = naive(complex_first, complex_second);\n    for (std::size_t index = 0; index\
    \ < complex_result.size(); ++index) {\n        assert(std::abs(complex_result[index]\
    \ - complex_expected[index]) < 1e-11);\n    }\n\n    std::vector<long long> integers\
    \ = {1, -2, 3, 4};\n    assert(\n        m1une::fps::convolution_round(integers,\
    \ integers)\n        == naive(integers, integers)\n    );\n    assert(\n     \
    \   m1une::fps::convolution_fft(\n            std::vector<double>(),\n       \
    \     std::vector<double>{1}\n        ).empty()\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1409;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; ++trial) {\n        int first_size\
    \ = int(random() % 100);\n        int second_size = int(random() % 100);\n   \
    \     std::vector<long double> first(first_size);\n        std::vector<long double>\
    \ second(second_size);\n        for (long double& value : first) {\n         \
    \   value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        for (long double& value : second) {\n        \
    \    value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        auto actual = m1une::fps::convolution_fft(first,\
    \ second);\n        auto expected = naive(first, second);\n        for (std::size_t\
    \ index = 0; index < actual.size(); ++index) {\n            long double magnitude\
    \ = 0;\n            for (std::size_t first_index = 0; first_index < first.size();\
    \ ++first_index) {\n                if (index < first_index) continue;\n     \
    \           std::size_t second_index = index - first_index;\n                if\
    \ (second_index < second.size()) {\n                    magnitude += std::fabs(\n\
    \                        first[first_index] * second[second_index]\n         \
    \           );\n                }\n            }\n            [[maybe_unused]]\
    \ long double tolerance =\n                1e-12L * std::max(1.0L, magnitude);\n\
    \            assert(std::fabs(actual[index] - expected[index]) <= tolerance);\n\
    \        }\n\n        std::vector<long long> integer_first(first_size);\n    \
    \    std::vector<long long> integer_second(second_size);\n        for (long long&\
    \ value : integer_first) {\n            value = static_cast<long long>(random()\
    \ % 2001) - 1000;\n        }\n        for (long long& value : integer_second)\
    \ {\n            value = static_cast<long long>(random() % 2001) - 1000;\n   \
    \     }\n        assert(\n            m1une::fps::convolution_round(integer_first,\
    \ integer_second)\n            == naive(integer_first, integer_second)\n     \
    \   );\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../fps/floating_point_convolution.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cmath>\n#include <complex>\n#include <cstdint>\n#include <iostream>\n\
    #include <vector>\n\nnamespace {\n\ntemplate <class T>\nstd::vector<T> naive(\n\
    \    const std::vector<T>& first,\n    const std::vector<T>& second\n) {\n   \
    \ if (first.empty() || second.empty()) return {};\n    std::vector<T> result(first.size()\
    \ + second.size() - 1);\n    for (std::size_t i = 0; i < first.size(); ++i) {\n\
    \        for (std::size_t j = 0; j < second.size(); ++j) {\n            result[i\
    \ + j] += first[i] * second[j];\n        }\n    }\n    return result;\n}\n\nvoid\
    \ test_fixed() {\n    std::vector<double> first = {1.5, 2.0};\n    std::vector<double>\
    \ second = {3.0, -1.0};\n    auto result = m1une::fps::convolution_fft(first,\
    \ second);\n    assert(std::fabs(result[0] - 4.5) < 1e-12);\n    assert(std::fabs(result[1]\
    \ - 4.5) < 1e-12);\n    assert(std::fabs(result[2] + 2.0) < 1e-12);\n\n    std::vector<std::complex<double>>\
    \ complex_first;\n    complex_first.emplace_back(1, 2);\n    complex_first.emplace_back(3,\
    \ -1);\n    std::vector<std::complex<double>> complex_second;\n    complex_second.emplace_back(-2,\
    \ 1);\n    complex_second.emplace_back(0, 4);\n    auto complex_result =\n   \
    \     m1une::fps::convolution_fft(complex_first, complex_second);\n    auto complex_expected\
    \ = naive(complex_first, complex_second);\n    for (std::size_t index = 0; index\
    \ < complex_result.size(); ++index) {\n        assert(std::abs(complex_result[index]\
    \ - complex_expected[index]) < 1e-11);\n    }\n\n    std::vector<long long> integers\
    \ = {1, -2, 3, 4};\n    assert(\n        m1une::fps::convolution_round(integers,\
    \ integers)\n        == naive(integers, integers)\n    );\n    assert(\n     \
    \   m1une::fps::convolution_fft(\n            std::vector<double>(),\n       \
    \     std::vector<double>{1}\n        ).empty()\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1409;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; ++trial) {\n        int first_size\
    \ = int(random() % 100);\n        int second_size = int(random() % 100);\n   \
    \     std::vector<long double> first(first_size);\n        std::vector<long double>\
    \ second(second_size);\n        for (long double& value : first) {\n         \
    \   value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        for (long double& value : second) {\n        \
    \    value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        auto actual = m1une::fps::convolution_fft(first,\
    \ second);\n        auto expected = naive(first, second);\n        for (std::size_t\
    \ index = 0; index < actual.size(); ++index) {\n            long double magnitude\
    \ = 0;\n            for (std::size_t first_index = 0; first_index < first.size();\
    \ ++first_index) {\n                if (index < first_index) continue;\n     \
    \           std::size_t second_index = index - first_index;\n                if\
    \ (second_index < second.size()) {\n                    magnitude += std::fabs(\n\
    \                        first[first_index] * second[second_index]\n         \
    \           );\n                }\n            }\n            [[maybe_unused]]\
    \ long double tolerance =\n                1e-12L * std::max(1.0L, magnitude);\n\
    \            assert(std::fabs(actual[index] - expected[index]) <= tolerance);\n\
    \        }\n\n        std::vector<long long> integer_first(first_size);\n    \
    \    std::vector<long long> integer_second(second_size);\n        for (long long&\
    \ value : integer_first) {\n            value = static_cast<long long>(random()\
    \ % 2001) - 1000;\n        }\n        for (long long& value : integer_second)\
    \ {\n            value = static_cast<long long>(random() % 2001) - 1000;\n   \
    \     }\n        assert(\n            m1une::fps::convolution_round(integer_first,\
    \ integer_second)\n            == naive(integer_first, integer_second)\n     \
    \   );\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - fps/floating_point_convolution.hpp
  isVerificationFile: true
  path: verify/fps/floating_point_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 03:05:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/fps/floating_point_convolution.test.cpp
layout: document
redirect_from:
- /verify/verify/fps/floating_point_convolution.test.cpp
- /verify/verify/fps/floating_point_convolution.test.cpp.html
title: verify/fps/floating_point_convolution.test.cpp
---
