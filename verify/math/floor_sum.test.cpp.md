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
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
    links:
    - https://judge.yosupo.jp/problem/sum_of_floor_of_linear
  bundledCode: "#line 1 \"verify/math/floor_sum.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n\n#include <iostream>\n\n#line 1 \"math/number_theory.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal {\n\n\
    inline long long safe_mod(long long x, long long mod) {\n    x %= mod;\n    if\
    \ (x < 0) x += mod;\n    return x;\n}\n\ninline unsigned __int128 floor_sum_unsigned(\n\
    \    unsigned long long n,\n    unsigned long long mod,\n    unsigned long long\
    \ a,\n    unsigned long long b\n) {\n    unsigned __int128 answer = 0;\n    while\
    \ (true) {\n        if (a >= mod) {\n            answer += static_cast<unsigned\
    \ __int128>(n) * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n\
    \        if (b >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (b / mod);\n            b %= mod;\n        }\n\n        const unsigned __int128\
    \ y_max = static_cast<unsigned __int128>(a) * n + b;\n        if (y_max < mod)\
    \ break;\n        n = static_cast<unsigned long long>(y_max / mod);\n        b\
    \ = static_cast<unsigned long long>(y_max % mod);\n        unsigned long long\
    \ tmp = mod;\n        mod = a;\n        a = tmp;\n    }\n    return answer;\n\
    }\n\n}  // namespace internal\n\ninline long long pow_mod(long long x, unsigned\
    \ long long exponent, long long mod) {\n    assert(mod >= 1);\n    if (mod ==\
    \ 1) return 0;\n\n    unsigned long long base = static_cast<unsigned long long>(internal::safe_mod(x,\
    \ mod));\n    unsigned long long result = 1;\n    const unsigned long long unsigned_mod\
    \ = static_cast<unsigned long long>(mod);\n    while (exponent > 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<unsigned long long>(\n\
    \                static_cast<unsigned __int128>(result) * base % unsigned_mod\n\
    \            );\n        }\n        base = static_cast<unsigned long long>(\n\
    \            static_cast<unsigned __int128>(base) * base % unsigned_mod\n    \
    \    );\n        exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n\
    }\n\n// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n\
    // modulo mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long\
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
    \ long, long long> crt(\n    const std::vector<long long>& remainders,\n    const\
    \ std::vector<long long>& moduli\n) {\n    assert(remainders.size() == moduli.size());\n\
    \n    long long r0 = 0;\n    long long m0 = 1;\n    for (int i = 0; i < int(remainders.size());\
    \ i++) {\n        assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
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
    \ answer =\n        (static_cast<__int128>(a) - normalized_a) / mod * n * (n -\
    \ 1) / 2;\n    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n\
    \    answer += internal::floor_sum_unsigned(\n        static_cast<unsigned long\
    \ long>(n),\n        static_cast<unsigned long long>(mod),\n        static_cast<unsigned\
    \ long long>(normalized_a),\n        static_cast<unsigned long long>(normalized_b)\n\
    \    );\n\n    assert(answer >= std::numeric_limits<long long>::min());\n    assert(answer\
    \ <= std::numeric_limits<long long>::max());\n    return static_cast<long long>(answer);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 6 \"verify/math/floor_sum.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int query_count;\n    std::cin >> query_count;\n    while (query_count--)\
    \ {\n        long long n, mod, a, b;\n        std::cin >> n >> mod >> a >> b;\n\
    \        std::cout << m1une::math::floor_sum(n, mod, a, b) << '\\n';\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n\n#include <iostream>\n\n#include \"math/number_theory.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ query_count;\n    std::cin >> query_count;\n    while (query_count--) {\n  \
    \      long long n, mod, a, b;\n        std::cin >> n >> mod >> a >> b;\n    \
    \    std::cout << m1une::math::floor_sum(n, mod, a, b) << '\\n';\n    }\n}\n"
  dependsOn:
  - math/number_theory.hpp
  isVerificationFile: true
  path: verify/math/floor_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 09:06:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/floor_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/math/floor_sum.test.cpp
- /verify/verify/math/floor_sum.test.cpp.html
title: verify/math/floor_sum.test.cpp
---
