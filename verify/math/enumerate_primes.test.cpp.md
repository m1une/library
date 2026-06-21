---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime_sieve.hpp
    title: Prime Sieve
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_primes
    links:
    - https://judge.yosupo.jp/problem/enumerate_primes
  bundledCode: "#line 1 \"verify/math/enumerate_primes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n#include <iostream>\n\
    #include <vector>\n\n#line 1 \"math/prime_sieve.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#line 8 \"math/prime_sieve.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nstruct PrimeSieve {\n   private:\n    int _limit;\n\
    \    std::vector<int> _min_prime_factor;\n    std::vector<int> _primes;\n\n  \
    \ public:\n    explicit PrimeSieve(int limit = 0) : _limit(0) {\n        assert(limit\
    \ >= 0);\n        _limit = limit;\n        _min_prime_factor.assign(limit + 1,\
    \ 0);\n        if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int value\
    \ = 2; value <= limit; value++) {\n            if (_min_prime_factor[value] ==\
    \ 0) {\n                _min_prime_factor[value] = value;\n                _primes.push_back(value);\n\
    \            }\n            for (int prime : _primes) {\n                if (prime\
    \ > _min_prime_factor[value] || value > limit / prime) break;\n              \
    \  _min_prime_factor[value * prime] = prime;\n            }\n        }\n    }\n\
    \n    int limit() const {\n        return _limit;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    const std::vector<int>&\
    \ min_prime_factors() const {\n        return _min_prime_factor;\n    }\n\n  \
    \  bool is_prime(int value) const {\n        assert(0 <= value && value <= _limit);\n\
    \        return value >= 2 && _min_prime_factor[value] == value;\n    }\n\n  \
    \  int min_prime_factor(int value) const {\n        assert(2 <= value && value\
    \ <= _limit);\n        return _min_prime_factor[value];\n    }\n\n    std::vector<std::pair<int,\
    \ int>> factorize(int value) const {\n        assert(1 <= value && value <= _limit);\n\
    \        std::vector<std::pair<int, int>> result;\n        while (value > 1) {\n\
    \            const int prime = _min_prime_factor[value];\n            int exponent\
    \ = 0;\n            do {\n                value /= prime;\n                exponent++;\n\
    \            } while (value > 1 && _min_prime_factor[value] == prime);\n     \
    \       result.emplace_back(prime, exponent);\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> divisors(int value) const {\n        std::vector<int>\
    \ result = {1};\n        for (const auto& factor : factorize(value)) {\n     \
    \       const int current_size = int(result.size());\n            int power =\
    \ 1;\n            for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n                power *= factor.first;\n                for (int i = 0; i\
    \ < current_size; i++) {\n                    result.push_back(result[i] * power);\n\
    \                }\n            }\n        }\n        std::sort(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    int totient(int value)\
    \ const {\n        assert(1 <= value && value <= _limit);\n        int result\
    \ = value;\n        for (const auto& factor : factorize(value)) {\n          \
    \  result = result / factor.first * (factor.first - 1);\n        }\n        return\
    \ result;\n    }\n\n    int mobius(int value) const {\n        assert(1 <= value\
    \ && value <= _limit);\n        int result = 1;\n        for (const auto& factor\
    \ : factorize(value)) {\n            if (factor.second >= 2) return 0;\n     \
    \       result = -result;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ totient_table() const {\n        std::vector<int> result(_limit + 1);\n    \
    \    if (_limit >= 1) result[1] = 1;\n        for (int value = 2; value <= _limit;\
    \ value++) {\n            const int prime = _min_prime_factor[value];\n      \
    \      const int reduced = value / prime;\n            result[value] = reduced\
    \ % prime == 0 ? result[reduced] * prime : result[reduced] * (prime - 1);\n  \
    \      }\n        return result;\n    }\n\n    std::vector<int> mobius_table()\
    \ const {\n        std::vector<int> result(_limit + 1);\n        if (_limit >=\
    \ 1) result[1] = 1;\n        for (int value = 2; value <= _limit; value++) {\n\
    \            const int prime = _min_prime_factor[value];\n            const int\
    \ reduced = value / prime;\n            result[value] = reduced % prime == 0 ?\
    \ 0 : -result[reduced];\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 7 \"verify/math/enumerate_primes.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, step, offset;\n    std::cin >> n >> step >> offset;\n    m1une::math::PrimeSieve\
    \ sieve(n);\n    const std::vector<int>& primes = sieve.primes();\n\n    int selected_count\
    \ = 0;\n    if (offset < int(primes.size())) {\n        selected_count = (int(primes.size())\
    \ - 1 - offset) / step + 1;\n    }\n    std::cout << primes.size() << ' ' << selected_count\
    \ << '\\n';\n    for (int i = offset; i < int(primes.size()); i += step) {\n \
    \       if (i != offset) std::cout << ' ';\n        std::cout << primes[i];\n\
    \    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../math/prime_sieve.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int n, step, offset;\n    std::cin >> n >> step >> offset;\n    m1une::math::PrimeSieve\
    \ sieve(n);\n    const std::vector<int>& primes = sieve.primes();\n\n    int selected_count\
    \ = 0;\n    if (offset < int(primes.size())) {\n        selected_count = (int(primes.size())\
    \ - 1 - offset) / step + 1;\n    }\n    std::cout << primes.size() << ' ' << selected_count\
    \ << '\\n';\n    for (int i = offset; i < int(primes.size()); i += step) {\n \
    \       if (i != offset) std::cout << ' ';\n        std::cout << primes[i];\n\
    \    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - math/prime_sieve.hpp
  isVerificationFile: true
  path: verify/math/enumerate_primes.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/enumerate_primes.test.cpp
layout: document
redirect_from:
- /verify/verify/math/enumerate_primes.test.cpp
- /verify/verify/math/enumerate_primes.test.cpp.html
title: verify/math/enumerate_primes.test.cpp
---
