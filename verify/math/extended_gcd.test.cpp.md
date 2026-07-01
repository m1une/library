---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
  bundledCode: "#line 1 \"verify/math/extended_gcd.test.cpp\"\n#define PROBLEM \"\
    https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n#line 1 \"math/number_theory.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace internal {\n\ninline long long safe_mod(long long x, long long mod)\
    \ {\n    x %= mod;\n    if (x < 0) x += mod;\n    return x;\n}\n\ninline unsigned\
    \ __int128 floor_sum_unsigned(unsigned long long n, unsigned long long mod, unsigned\
    \ long long a,\n                                            unsigned long long\
    \ b) {\n    unsigned __int128 answer = 0;\n    while (true) {\n        if (a >=\
    \ mod) {\n            answer += static_cast<unsigned __int128>(n) * (n - 1) /\
    \ 2 * (a / mod);\n            a %= mod;\n        }\n        if (b >= mod) {\n\
    \            answer += static_cast<unsigned __int128>(n) * (b / mod);\n      \
    \      b %= mod;\n        }\n\n        const unsigned __int128 y_max = static_cast<unsigned\
    \ __int128>(a) * n + b;\n        if (y_max < mod) break;\n        n = static_cast<unsigned\
    \ long long>(y_max / mod);\n        b = static_cast<unsigned long long>(y_max\
    \ % mod);\n        unsigned long long tmp = mod;\n        mod = a;\n        a\
    \ = tmp;\n    }\n    return answer;\n}\n\n}  // namespace internal\n\n// Returns\
    \ (g, x, y), where g = gcd(a, b) is nonnegative and\n// a * x + b * y = g. Returns\
    \ (0, 0, 0) when a = b = 0.\ninline std::tuple<long long, long long, long long>\
    \ extended_gcd(long long a,\n                                                \
    \               long long b) {\n    using i128 = __int128;\n    if (a == 0 &&\
    \ b == 0) return {0, 0, 0};\n\n    i128 old_remainder = a;\n    i128 remainder\
    \ = b;\n    if (old_remainder < 0) old_remainder = -old_remainder;\n    if (remainder\
    \ < 0) remainder = -remainder;\n    i128 old_x = 1;\n    i128 x = 0;\n    i128\
    \ old_y = 0;\n    i128 y = 1;\n\n    while (remainder != 0) {\n        i128 quotient\
    \ = old_remainder / remainder;\n\n        i128 next = old_remainder - quotient\
    \ * remainder;\n        old_remainder = remainder;\n        remainder = next;\n\
    \n        next = old_x - quotient * x;\n        old_x = x;\n        x = next;\n\
    \n        next = old_y - quotient * y;\n        old_y = y;\n        y = next;\n\
    \    }\n\n    if (a < 0) old_x = -old_x;\n    if (b < 0) old_y = -old_y;\n\n#ifndef\
    \ NDEBUG\n    const i128 minimum = std::numeric_limits<long long>::min();\n  \
    \  const i128 maximum = std::numeric_limits<long long>::max();\n    assert(old_remainder\
    \ <= maximum);\n    assert(minimum <= old_x && old_x <= maximum);\n    assert(minimum\
    \ <= old_y && old_y <= maximum);\n#endif\n    return {static_cast<long long>(old_remainder),\
    \ static_cast<long long>(old_x),\n            static_cast<long long>(old_y)};\n\
    }\n\ninline long long pow_mod(long long x, unsigned long long exponent, long long\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n\n    unsigned long\
    \ long base = static_cast<unsigned long long>(internal::safe_mod(x, mod));\n \
    \   unsigned long long result = 1;\n    const unsigned long long unsigned_mod\
    \ = static_cast<unsigned long long>(mod);\n    while (exponent > 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(result) * base % unsigned_mod);\n        }\n        base = static_cast<unsigned\
    \ long long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);\n  \
    \      exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n}\n\
    \n// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n//\
    \ modulo mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long\
    \ long, long long> inv_gcd(long long a, long long mod) {\n    assert(mod >= 1);\n\
    \    a = internal::safe_mod(a, mod);\n    if (a == 0) return {mod, 0};\n\n   \
    \ long long s = mod;\n    long long t = a;\n    long long m0 = 0;\n    long long\
    \ m1 = 1;\n    while (t > 0) {\n        const long long quotient = s / t;\n  \
    \      s -= t * quotient;\n        m0 -= m1 * quotient;\n\n        long long tmp\
    \ = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n\
    \        m1 = tmp;\n    }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n\
    }\n\ninline long long inv_mod(long long x, long long mod) {\n    const auto result\
    \ = inv_gcd(x, mod);\n    assert(result.first == 1);\n    return result.second;\n\
    }\n\n// Returns the smallest nonnegative solution and the least common multiple\
    \ of\n// the moduli. Returns {0, 0} when the system is inconsistent.\ninline std::pair<long\
    \ long, long long> crt(const std::vector<long long>& remainders,\n           \
    \                                const std::vector<long long>& moduli) {\n   \
    \ assert(remainders.size() == moduli.size());\n\n    long long r0 = 0;\n    long\
    \ long m0 = 1;\n    for (int i = 0; i < int(remainders.size()); i++) {\n     \
    \   assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
    \ moduli[i]);\n        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n \
    \           long long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n\
    \            tmp = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n\n        const auto inverse = inv_gcd(m0,\
    \ m1);\n        const long long gcd = inverse.first;\n        const long long\
    \ reduced_modulus = m1 / gcd;\n        const __int128 difference = static_cast<__int128>(r1)\
    \ - r0;\n        if (difference % gcd != 0) return {0, 0};\n\n        __int128\
    \ multiplier = difference / gcd % reduced_modulus;\n        multiplier = multiplier\
    \ * inverse.second % reduced_modulus;\n        if (multiplier < 0) multiplier\
    \ += reduced_modulus;\n\n        const __int128 new_modulus = static_cast<__int128>(m0)\
    \ * reduced_modulus;\n        assert(new_modulus <= std::numeric_limits<long long>::max());\n\
    \        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n\
    \        new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n#line 4 \"verify/math/extended_gcd.test.cpp\"\n\n#include\
    \ <algorithm>\n#include <array>\n#line 8 \"verify/math/extended_gcd.test.cpp\"\
    \n#include <cstdlib>\n#include <iostream>\n#line 11 \"verify/math/extended_gcd.test.cpp\"\
    \n#include <numeric>\n#line 13 \"verify/math/extended_gcd.test.cpp\"\n\nnamespace\
    \ {\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    for (long long a = -100;\
    \ a <= 100; a++) {\n        for (long long b = -100; b <= 100; b++) {\n      \
    \      const auto [gcd, x, y] = m1une::math::extended_gcd(a, b);\n           \
    \ assert(gcd == std::gcd(a, b));\n            assert(static_cast<__int128>(a)\
    \ * x + static_cast<__int128>(b) * y == gcd);\n        }\n    }\n\n    const auto\
    \ [gcd, x, y] = m1une::math::extended_gcd(\n        std::numeric_limits<long long>::min(),\
    \ std::numeric_limits<long long>::max());\n    assert(gcd == 1);\n    assert(static_cast<__int128>(std::numeric_limits<long\
    \ long>::min()) * x +\n               static_cast<__int128>(std::numeric_limits<long\
    \ long>::max()) * y ==\n           gcd);\n}\n#endif\n\n__int128 floor_div(__int128\
    \ numerator, __int128 denominator) {\n    __int128 quotient = numerator / denominator;\n\
    \    if (numerator % denominator < 0) quotient--;\n    return quotient;\n}\n\n\
    std::pair<long long, long long> normalize_for_aoj(long long a, long long b,\n\
    \                                                  long long gcd, long long x,\n\
    \                                                  long long y) {\n    __int128\
    \ x_step = b / gcd;\n    __int128 y_step = a / gcd;\n    __int128 first = floor_div(-static_cast<__int128>(x),\
    \ x_step);\n    __int128 second = floor_div(static_cast<__int128>(y), y_step);\n\
    \    std::array<__int128, 6> candidates = {first - 1, first, first + 1,\n    \
    \                                      second - 1, second, second + 1};\n\n  \
    \  __int128 best_score = -1;\n    __int128 best_x = 0;\n    __int128 best_y =\
    \ 0;\n    for (__int128 shift : candidates) {\n        __int128 candidate_x =\
    \ x + shift * x_step;\n        __int128 candidate_y = y - shift * y_step;\n  \
    \      __int128 score = (candidate_x < 0 ? -candidate_x : candidate_x) +\n   \
    \                      (candidate_y < 0 ? -candidate_y : candidate_y);\n     \
    \   bool candidate_ordered = candidate_x <= candidate_y;\n        bool best_ordered\
    \ = best_x <= best_y;\n        if (best_score == -1 || score < best_score ||\n\
    \            (score == best_score && candidate_ordered && !best_ordered) ||\n\
    \            (score == best_score && candidate_ordered == best_ordered &&\n  \
    \           candidate_x < best_x)) {\n            best_score = score;\n      \
    \      best_x = candidate_x;\n            best_y = candidate_y;\n        }\n \
    \   }\n    return {static_cast<long long>(best_x), static_cast<long long>(best_y)};\n\
    }\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    long long a, b;\n    std::cin >> a >> b;\n    const auto [gcd, x,\
    \ y] = m1une::math::extended_gcd(a, b);\n    const auto answer = normalize_for_aoj(a,\
    \ b, gcd, x, y);\n    std::cout << answer.first << ' ' << answer.second << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n\
    #include \"../../math/number_theory.hpp\"\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <cstdlib>\n#include <iostream>\n#include <limits>\n\
    #include <numeric>\n#include <tuple>\n\nnamespace {\n\n#ifndef NDEBUG\nvoid randomized_test()\
    \ {\n    for (long long a = -100; a <= 100; a++) {\n        for (long long b =\
    \ -100; b <= 100; b++) {\n            const auto [gcd, x, y] = m1une::math::extended_gcd(a,\
    \ b);\n            assert(gcd == std::gcd(a, b));\n            assert(static_cast<__int128>(a)\
    \ * x + static_cast<__int128>(b) * y == gcd);\n        }\n    }\n\n    const auto\
    \ [gcd, x, y] = m1une::math::extended_gcd(\n        std::numeric_limits<long long>::min(),\
    \ std::numeric_limits<long long>::max());\n    assert(gcd == 1);\n    assert(static_cast<__int128>(std::numeric_limits<long\
    \ long>::min()) * x +\n               static_cast<__int128>(std::numeric_limits<long\
    \ long>::max()) * y ==\n           gcd);\n}\n#endif\n\n__int128 floor_div(__int128\
    \ numerator, __int128 denominator) {\n    __int128 quotient = numerator / denominator;\n\
    \    if (numerator % denominator < 0) quotient--;\n    return quotient;\n}\n\n\
    std::pair<long long, long long> normalize_for_aoj(long long a, long long b,\n\
    \                                                  long long gcd, long long x,\n\
    \                                                  long long y) {\n    __int128\
    \ x_step = b / gcd;\n    __int128 y_step = a / gcd;\n    __int128 first = floor_div(-static_cast<__int128>(x),\
    \ x_step);\n    __int128 second = floor_div(static_cast<__int128>(y), y_step);\n\
    \    std::array<__int128, 6> candidates = {first - 1, first, first + 1,\n    \
    \                                      second - 1, second, second + 1};\n\n  \
    \  __int128 best_score = -1;\n    __int128 best_x = 0;\n    __int128 best_y =\
    \ 0;\n    for (__int128 shift : candidates) {\n        __int128 candidate_x =\
    \ x + shift * x_step;\n        __int128 candidate_y = y - shift * y_step;\n  \
    \      __int128 score = (candidate_x < 0 ? -candidate_x : candidate_x) +\n   \
    \                      (candidate_y < 0 ? -candidate_y : candidate_y);\n     \
    \   bool candidate_ordered = candidate_x <= candidate_y;\n        bool best_ordered\
    \ = best_x <= best_y;\n        if (best_score == -1 || score < best_score ||\n\
    \            (score == best_score && candidate_ordered && !best_ordered) ||\n\
    \            (score == best_score && candidate_ordered == best_ordered &&\n  \
    \           candidate_x < best_x)) {\n            best_score = score;\n      \
    \      best_x = candidate_x;\n            best_y = candidate_y;\n        }\n \
    \   }\n    return {static_cast<long long>(best_x), static_cast<long long>(best_y)};\n\
    }\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    randomized_test();\n\
    #endif\n\n    long long a, b;\n    std::cin >> a >> b;\n    const auto [gcd, x,\
    \ y] = m1une::math::extended_gcd(a, b);\n    const auto answer = normalize_for_aoj(a,\
    \ b, gcd, x, y);\n    std::cout << answer.first << ' ' << answer.second << '\\\
    n';\n}\n"
  dependsOn:
  - math/number_theory.hpp
  isVerificationFile: true
  path: verify/math/extended_gcd.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 22:14:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/extended_gcd.test.cpp
layout: document
redirect_from:
- /verify/verify/math/extended_gcd.test.cpp
- /verify/verify/math/extended_gcd.test.cpp.html
title: verify/math/extended_gcd.test.cpp
---
