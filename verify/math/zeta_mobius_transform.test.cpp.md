---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
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
  bundledCode: "#line 1 \"verify/math/zeta_mobius_transform.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/zeta_mobius_transform.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline\
    \ bool is_power_of_two(std::size_t size) noexcept {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 4 \"verify/math/zeta_mobius_transform.test.cpp\"\n\n#line 7 \"verify/math/zeta_mobius_transform.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 10 \"verify/math/zeta_mobius_transform.test.cpp\"\
    \n\nnamespace {\n\nvoid test_subset_transforms() {\n    const std::vector<long\
    \ long> original{3, -1, 4, 1, 5, -9, 2, 6};\n\n    std::vector<long long> values\
    \ = original;\n    m1une::math::subset_zeta_transform(values);\n    const std::vector<long\
    \ long> expected_subset{\n        3, 2, 7, 7, 8, -2, 14, 11\n    };\n    assert(values\
    \ == expected_subset);\n    m1une::math::subset_mobius_transform(values);\n  \
    \  assert(values == original);\n\n    values = original;\n    m1une::math::superset_zeta_transform(values);\n\
    \    const std::vector<long long> expected_superset{\n        11, -3, 13, 7, 4,\
    \ -3, 8, 6\n    };\n    assert(values == expected_superset);\n    m1une::math::superset_mobius_transform(values);\n\
    \    assert(values == original);\n}\n\nstd::vector<long long> naive_divisor_zeta(\n\
    \    const std::vector<long long>& values\n) {\n    std::vector<long long> result\
    \ = values;\n    for (std::size_t value = 1; value < values.size(); ++value) {\n\
    \        result[value] = 0;\n        for (std::size_t divisor = 1; divisor <=\
    \ value; ++divisor) {\n            if (value % divisor == 0) result[value] +=\
    \ values[divisor];\n        }\n    }\n    return result;\n}\n\nstd::vector<long\
    \ long> naive_multiple_zeta(\n    const std::vector<long long>& values\n) {\n\
    \    std::vector<long long> result = values;\n    for (std::size_t value = 1;\
    \ value < values.size(); ++value) {\n        result[value] = 0;\n        for (\n\
    \            std::size_t multiple = value;\n            multiple < values.size();\n\
    \            multiple += value\n        ) {\n            result[value] += values[multiple];\n\
    \        }\n    }\n    return result;\n}\n\nvoid check(const std::vector<long\
    \ long>& original) {\n    std::vector<long long> values = original;\n    m1une::math::divisor_zeta_transform(values);\n\
    \    assert(values == naive_divisor_zeta(original));\n    m1une::math::divisor_mobius_transform(values);\n\
    \    assert(values == original);\n\n    values = original;\n    m1une::math::multiple_zeta_transform(values);\n\
    \    assert(values == naive_multiple_zeta(original));\n    m1une::math::multiple_mobius_transform(values);\n\
    \    assert(values == original);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 0x6a09e667f3bcc909ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1000; ++trial) {\n        const std::size_t\
    \ size = random() % 80;\n        std::vector<long long> values(size);\n      \
    \  for (long long& value : values) {\n            value = static_cast<long long>(random()\
    \ % 101) - 50;\n        }\n        check(values);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_subset_transforms();\n    check(std::vector<long long>());\n\
    \    check(std::vector<long long>{7});\n    check(std::vector<long long>{7, -3});\n\
    \    check(std::vector<long long>{11, 1, 2, 3, 4, 5, 6});\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/zeta_mobius_transform.hpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nnamespace {\n\n\
    void test_subset_transforms() {\n    const std::vector<long long> original{3,\
    \ -1, 4, 1, 5, -9, 2, 6};\n\n    std::vector<long long> values = original;\n \
    \   m1une::math::subset_zeta_transform(values);\n    const std::vector<long long>\
    \ expected_subset{\n        3, 2, 7, 7, 8, -2, 14, 11\n    };\n    assert(values\
    \ == expected_subset);\n    m1une::math::subset_mobius_transform(values);\n  \
    \  assert(values == original);\n\n    values = original;\n    m1une::math::superset_zeta_transform(values);\n\
    \    const std::vector<long long> expected_superset{\n        11, -3, 13, 7, 4,\
    \ -3, 8, 6\n    };\n    assert(values == expected_superset);\n    m1une::math::superset_mobius_transform(values);\n\
    \    assert(values == original);\n}\n\nstd::vector<long long> naive_divisor_zeta(\n\
    \    const std::vector<long long>& values\n) {\n    std::vector<long long> result\
    \ = values;\n    for (std::size_t value = 1; value < values.size(); ++value) {\n\
    \        result[value] = 0;\n        for (std::size_t divisor = 1; divisor <=\
    \ value; ++divisor) {\n            if (value % divisor == 0) result[value] +=\
    \ values[divisor];\n        }\n    }\n    return result;\n}\n\nstd::vector<long\
    \ long> naive_multiple_zeta(\n    const std::vector<long long>& values\n) {\n\
    \    std::vector<long long> result = values;\n    for (std::size_t value = 1;\
    \ value < values.size(); ++value) {\n        result[value] = 0;\n        for (\n\
    \            std::size_t multiple = value;\n            multiple < values.size();\n\
    \            multiple += value\n        ) {\n            result[value] += values[multiple];\n\
    \        }\n    }\n    return result;\n}\n\nvoid check(const std::vector<long\
    \ long>& original) {\n    std::vector<long long> values = original;\n    m1une::math::divisor_zeta_transform(values);\n\
    \    assert(values == naive_divisor_zeta(original));\n    m1une::math::divisor_mobius_transform(values);\n\
    \    assert(values == original);\n\n    values = original;\n    m1une::math::multiple_zeta_transform(values);\n\
    \    assert(values == naive_multiple_zeta(original));\n    m1une::math::multiple_mobius_transform(values);\n\
    \    assert(values == original);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 0x6a09e667f3bcc909ULL;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 1000; ++trial) {\n        const std::size_t\
    \ size = random() % 80;\n        std::vector<long long> values(size);\n      \
    \  for (long long& value : values) {\n            value = static_cast<long long>(random()\
    \ % 101) - 50;\n        }\n        check(values);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_subset_transforms();\n    check(std::vector<long long>());\n\
    \    check(std::vector<long long>{7});\n    check(std::vector<long long>{7, -3});\n\
    \    check(std::vector<long long>{11, 1, 2, 3, 4, 5, 6});\n    test_randomized();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/zeta_mobius_transform.hpp
  isVerificationFile: true
  path: verify/math/zeta_mobius_transform.test.cpp
  requiredBy: []
  timestamp: '2026-06-22 22:56:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/zeta_mobius_transform.test.cpp
layout: document
redirect_from:
- /verify/verify/math/zeta_mobius_transform.test.cpp
- /verify/verify/math/zeta_mobius_transform.test.cpp.html
title: verify/math/zeta_mobius_transform.test.cpp
---
